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
#include <util/atomic.h>
#include <string.h>


#define MIN_PAUSE_TIME_100US (10UL*1000UL*5UL)

#define MEAN_TIME_DIVIDE_POW 3U
#define MEAN_TIME_SAMPLES (1 << MEAN_TIME_DIVIDE_POW)

volatile uint8_t current_step = 0;
uint8_t last_step = 0;
uint32_t stop_time_100us = 0;
volatile uint32_t zc_times_100us[MEAN_TIME_SAMPLES] = {0};
volatile uint8_t zc_times_idx = 0;
uint32_t zc_time_mean;

#ifdef STEP_MODE
bool_t ESC_commute;
#endif

uint8_t cold_start_cnt = 0;
uint32_t cold_start_next_commute_time;

#define COLD_START_CNT_MAX (6U*3U)


static esc_state_t last_state = INVALID;
static esc_state_t current_state = INVALID;
static esc_state_t new_state = INVALID;
//static esc_state_t requested_state = INVALID;

void zc_phase0_cb (uint8_t state) {
	if (state == GPIO_STATE_HIGH) {
		current_step = 0;
		zc_times_100us[zc_times_idx++] = sys_time_100us;
		if (zc_times_idx == MEAN_TIME_SAMPLES) {
			zc_times_idx = 0;
		}
	} else {
		current_step = 3;
	}

}

void zc_phase1_cb (uint8_t state) {
	if (state == GPIO_STATE_HIGH) {
		current_step = 4;
	} else {
		current_step = 1;
	}
}

void zc_phase2_cb (uint8_t state) {
	if (state == GPIO_STATE_HIGH) {
		current_step = 2;
	} else {
		current_step = 5;
	}
}

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

	GPIO_pin_config((pin_t)phase0_zc_pin.byte, GPIO_DIR_IN, GPIO_STATE_HIGH_Z);
	GPIO_pin_config((pin_t)phase1_zc_pin.byte, GPIO_DIR_IN, GPIO_STATE_HIGH_Z);
	GPIO_pin_config((pin_t)phase2_zc_pin.byte, GPIO_DIR_IN, GPIO_STATE_HIGH_Z);

//	INTERRUPT_set_PCINT(phase0_zc_pin, zc_phase0_cb);
//	INTERRUPT_set_PCINT(phase1_zc_pin, zc_phase1_cb);
//	INTERRUPT_set_PCINT(phase2_zc_pin, zc_phase2_cb);

	new_state = STOP;
}

void esc_step_0(void) {
	esc_phase_1_inactive();
	esc_phase_2_active_low();
	esc_phase_0_active_high();
#if defined(DEBUG) && (DEBUG == ON)
	UART_send_P(str_step0);
#endif
}

void esc_step_1(void) {
	esc_phase_2_inactive();
	esc_phase_1_active_low();
	esc_phase_0_active_high();
#if defined(DEBUG) && (DEBUG == ON)
	UART_send_P(str_step1);
#endif
}

void esc_step_2(void) {
	esc_phase_0_inactive();
	esc_phase_1_active_low();
	esc_phase_2_active_high();

#if defined(DEBUG) && (DEBUG == ON)
	UART_send_P(str_step2);
#endif
}

void esc_step_3(void) {
	esc_phase_1_inactive();
	esc_phase_0_active_low();
	esc_phase_2_active_high();

#if defined(DEBUG) && (DEBUG == ON)
	UART_send_P(str_step3);
#endif
}

void esc_step_4(void) {
	esc_phase_2_inactive();
	esc_phase_0_active_low();
	esc_phase_1_active_high();
#if defined(DEBUG) && (DEBUG == ON)
	UART_send_P(str_step4);
#endif
}

void esc_step_5(void) {
	esc_phase_0_inactive();
	esc_phase_2_active_low();
	esc_phase_1_active_high();


#if defined(DEBUG) && (DEBUG == ON)
	UART_send_P(str_step5);
#endif
}

void ESC_set_power(uint8_t duty) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		TIMER_t02_set_OCRA(TIMER0, duty);
		TIMER_t02_set_OCRB(TIMER0, duty);
		TIMER_t02_set_OCRB(TIMER2, duty);
	}
	UART_send_P(str_power);
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

void calc_zc_time_mean(void) {
	uint32_t sum = 0;
	for (uint8_t i = 0U; i < MEAN_TIME_SAMPLES; i++) {
		sum += zc_times_100us[i];
	}
	zc_time_mean = (sum >> MEAN_TIME_DIVIDE_POW);
}

uint8_t ESC_change_request(esc_state_t new) {

	switch (new) {
	case INIT:
		if (current_state == STOP || current_state == INVALID) {
			new_state = INIT;
		}
		break;

	case START:
		if (current_state == STOP) {
			new_state = START;
		}
		break;

	case COLD_START:
		if ((current_state == START)) /* && (delta_stop() >= MIN_PAUSE_TIME_100US))*/ {
			new_state = COLD_START;
		}
		break;

	case WORK:
		if (current_state == COLD_START) {
			new_state = WORK;
		}
		break;

	case STALL:
		if ((current_state == WORK) && (zc_times_100us[zc_times_idx] >= zc_time_mean * 3)) {
			new_state = STALL;
		}
		break;

	case STOP:
		if (current_state != INVALID) {
			new_state = STOP;
		}
		break;

	case INVALID:
		/* fallthrough */

	default:
		break;
	}

	UART_send_P(str_chreq);
	while(!UART_putchar((char)new_state + '0'));
	UART_send_P(str_crlf);

	return 0U;
}

#define COMMUTE_TIME (50UL)
void cold_start(void) {
#ifndef STEP_MODE
	if (sys_time_100us >= cold_start_next_commute_time) {
		cold_start_next_commute_time = sys_time_100us + COMMUTE_TIME;
#else
	if (ESC_commute) {
		ESC_commute = false;
#endif

		steps[current_step++]();
		if (current_step == 6) {
			current_step = 0;
		}
#ifndef STEP_MODE
		if ((cold_start_cnt++) == COLD_START_CNT_MAX) {
			last_step = current_step;
			ESC_change_request(WORK);
		}
#endif
	}
}

void ESC_main(void) {
	current_state = new_state;
	switch (current_state) {
	case INIT:
		ESC_init();
		break;

	case START:
		ESC_change_request(COLD_START);
		break;

	case COLD_START:
		/* commutation driven by fixed time */
		if(last_state != COLD_START) {
			cold_start_next_commute_time = sys_time_100us + COMMUTE_TIME;
			cold_start_cnt = 0;
		}

		cold_start();
		break;

	case WORK:
		/* commutation driven by zero cross detection */
		if(last_step != current_step) {
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
				INTERRUPT_set_PCINT(phase0_zc_pin, zc_phase0_cb);
				INTERRUPT_set_PCINT(phase1_zc_pin, zc_phase1_cb);
				INTERRUPT_set_PCINT(phase2_zc_pin, zc_phase2_cb);
			}

			steps[current_step]();
			last_step = current_step;
		}
		break;

	case STOP:
		if (last_state != STOP) {
			stop_time_100us = sys_time_100us;


			ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
				TIMER_t02_set_OCRA(TIMER0, 0);
				TIMER_t02_set_OCRB(TIMER0, 0);
				TIMER_t02_set_OCRB(TIMER2, 0);

				INTERRUPT_unset_PCINT(phase0_zc_pin);
				INTERRUPT_unset_PCINT(phase1_zc_pin);
				INTERRUPT_unset_PCINT(phase2_zc_pin);

				esc_phase_0_inactive();
				esc_phase_1_inactive();
				esc_phase_2_inactive();
			}
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
	last_state = current_state;
}


