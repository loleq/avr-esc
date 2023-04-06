/*
 * esc.c
 *
 *  Created on: 25 mar 2023
 *      Author: bpierzy
 */

#include "common.h"
#include "esc.h"




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

void ESC_set_dir(uint8_t dir) {
	/* ToDo: implement rotation direction switch */
}

extern void ESC_stop(void) {
	/* ToDo: implement disabling the ESC functionality:
	 * 1. switch off interrupts from comparators.
	 * 2. set pins in safe state.
	 * 3. disable timers (PWMs).
	 */
}


