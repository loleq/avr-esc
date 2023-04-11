/*
 * esc.c
 *
 *  Created on: 25 mar 2023
 *      Author: bpierzy
 */

#include "common.h"
#include "esc.h"
#include "uart.h"
#include "interrupt.h"

#define MIN_PAUSE_TIME_100US (10UL*1000UL*5UL)

#define MEAN_TIME_DIVIDE_POW 3U
#define MEAN_TIME_SAMPLES (1 << MEAN_TIME_DIVIDE_POW)

uint8_t current_step = 0;
uint32_t stop_time_100us = 0;
uint32_t zerocross_times_100us[MEAN_TIME_SAMPLES] = {0};
uint8_t zerocross_times_idx = 0;
uint32_t zerocross_time_mean;


static esc_state_t last_state = INVALID;
static esc_state_t current_state = INVALID;
static esc_state_t requested_state = INVALID;


void ESC_init(void) {

//	for(uint8_t i = 0; i < 3; i++) {
//		GPIO_pin_config(esc_cfg->phase[i].pin_sd, GPIO_DIR_OUT, GPIO_STATE_LOW);
//		GPIO_pin_config(esc_cfg->phase[i].pin_in, GPIO_DIR_OUT, GPIO_STATE_LOW);
//	}

	GPIO_pin_config(phase0_pwm_pin, GPIO_DIR_OUT, GPIO_STATE_LOW);
	GPIO_pin_config(phase1_pwm_pin, GPIO_DIR_OUT, GPIO_STATE_LOW);
	GPIO_pin_config(phase2_pwm_pin, GPIO_DIR_OUT, GPIO_STATE_LOW);

	GPIO_pin_config(phase0_in_pin, GPIO_DIR_OUT, GPIO_STATE_LOW);
	GPIO_pin_config(phase1_in_pin, GPIO_DIR_OUT, GPIO_STATE_LOW);
	GPIO_pin_config(phase2_in_pin, GPIO_DIR_OUT, GPIO_STATE_LOW);

	TIMER_t02_set_WGM (TIMER0, T02_WGM_PWM_PC_FF); /* Phase correct PWM with counting to 0xFF */
	TIMER_t02_set_CS  (TIMER0, CS_CLK_FULL);       /* Use internal clock with full speed */
	TIMER_t02_set_COMA(TIMER0, COM_CLEAR_ON_OCR);  /* Clear OC0A on Compare Match when up-counting. Set OC0A on Compare Match when down-counting.*/
	TIMER_t02_set_COMB(TIMER0, COM_CLEAR_ON_OCR);  /* Clear OC0B on Compare Match when up-counting. Set OC0B on Compare Match when down-counting.*/
	TIMER_t02_set_OCRA(TIMER0, 0);                 /* Set PWM to 0 - off */
	TIMER_t02_set_OCRB(TIMER0, 0);                 /* Set PWM to 0 - off */

	TIMER_t02_set_WGM (TIMER2, T02_WGM_PWM_PC_FF); /* Phase correct PWM with counting to 0xFF */
	TIMER_t02_set_CS  (TIMER2, CS_CLK_FULL);       /* Use internal clock with full speed */
	//TIMER_t02_set_COMA(TIMER2, COM_CLEAR_ON_OCR); /* Clear OC2A on Compare Match when up-counting. Set OC2A on Compare Match when down-counting.*/
	TIMER_t02_set_COMB(TIMER2, COM_CLEAR_ON_OCR);  /* Clear OC2B on Compare Match when up-counting. Set OC2B on Compare Match when down-counting.*/
	//TIMER_t02_set_OCRA(TIMER2, 0);                /* Set PWM to 0 - off */
	TIMER_t02_set_OCRB(TIMER2, 0);                 /* Set PWM to 0 - off */

	GPIO_pin_config(phase0_zerocross_pin, GPIO_DIR_IN, GPIO_STATE_HIGH_Z);
	GPIO_pin_config(phase1_zerocross_pin, GPIO_DIR_IN, GPIO_STATE_HIGH_Z);
	GPIO_pin_config(phase2_zerocross_pin, GPIO_DIR_IN, GPIO_STATE_HIGH_Z);
	requested_state = STOP;
}


void esc_step_0(void) {
	esc_phase_2_inactive();
	esc_phase_1_active_low();
	esc_phase_0_active_high();
}

void esc_step_1(void) {
	esc_phase_1_inactive();
	esc_phase_2_active_low();
	esc_phase_0_active_high();
}

void esc_step_2(void) {
	esc_phase_0_inactive();
	esc_phase_2_active_low();
	esc_phase_1_active_high();
}

void esc_step_3(void) {
	esc_phase_2_inactive();
	esc_phase_0_active_low();
	esc_phase_1_active_high();
}

void esc_step_4(void) {
	esc_phase_1_inactive();
	esc_phase_0_active_low();
	esc_phase_2_active_high();
}

void esc_step_5(void) {
	esc_phase_0_inactive();
	esc_phase_1_active_low();
	esc_phase_2_active_high();
}

void ESC_set_power(uint8_t duty) {
	TIMER_t02_set_OCRA(TIMER0, duty);
	TIMER_t02_set_OCRB(TIMER0, duty);
	TIMER_t02_set_OCRB(TIMER2, duty);
}

typedef void (*esc_step_t)(void);
esc_step_t steps[6] = {
	esc_step_0,
	esc_step_1,
	esc_step_2,
	esc_step_3,
	esc_step_4,
	esc_step_5,
};

void ESC_cmd_set_dir(uint8_t dir) {
	/* ToDo: implement rotation direction switch */
}

void ESC_cmd_stop(void) {
	/* ToDo: implement disabling the ESC functionality:
	 * 1. switch off interrupts from comparators.
	 * 2. set pins in safe state.
	 * 3. disable timers (PWMs).
	 */
	current_state = STOP;
}

uint32_t delta_stop(void) {
	return sys_time_100us - stop_time_100us;
}

void calc_zerocross_time_mean(void) {
	uint32_t sum = 0;
	for (uint8_t i = 0U; i < MEAN_TIME_SAMPLES; i++) {
		sum += zerocross_times_100us[i];
	}
	zerocross_time_mean = (sum >> MEAN_TIME_DIVIDE_POW);
}

#include <string.h>
char * msg = "Ack. Change request ";
uint8_t ESC_change_request(esc_state_t new) {
	uint8_t len = strlen(msg);

	switch (new) {
	case INIT:
		if (current_state == STOP || current_state == INVALID) {
			current_state = INIT;
		}
		break;

	case START:
		if (current_state == STOP) {
			current_state = START;
		}
		break;

	case COLD_START:
		if ((current_state == START)) /* && (delta_stop() >= MIN_PAUSE_TIME_100US))*/ {
			current_state = COLD_START;
		}
		break;

	case WORK:
		if (current_state == COLD_START) {
			current_state = WORK;
		}
		break;

	case STALL:
		if ((current_state == WORK) && (zerocross_times_100us[zerocross_times_idx] >= zerocross_time_mean * 3)) {
			current_state = STALL;
		}
		break;

	case STOP:
		if (last_state != INVALID) {
			current_state = STOP;
		}
		break;

	case INVALID:
		/* fallthrough */

	default:
		break;
	}
	UART_send(msg, len, true);
	UART_putchar(current_state + 0x30);
	UART_send("\r\n", 2, true);
	return 0U;
}



void ESC_main(void) {
	switch (current_state) {
	case INIT:
		ESC_init();
		break;

	case START:
//		if () {
			ESC_change_request(COLD_START);
//		} else {
//			ESC_change_request(WORK);
//		}
		break;

	case COLD_START:
		break;
	case WORK:
		break;
	case STOP:
		if (last_state != STOP) {
			stop_time_100us = sys_time_100us;
		}
		break;

	case STALL:
		if ((current_state == WORK)) {
			current_state = STALL;
		}
		break;

	case INVALID:
		/* fallthrough */
	default:
		break;
	}

}


