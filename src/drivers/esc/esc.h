/*
 * esc.h
 *
 *  Created on: 28 mar 2023
 *      Author: bpierzy
 */

#ifndef _ESC_H_
#define _ESC_H_

#include "common.h"
#include "gpio.h"
#include "timer.h"


extern void ESC_init(void);
extern void ESC_set_power(uint8_t duty);
extern void ESC_set_dir(uint8_t dir);
//extern void ESC_start();
extern void ESC_stop(void);


//#define phase0_pwm_pin GPIO_PIN_OC1A  // --> GPIO_PIN_B1
//#define phase1_pwm_pin GPIO_PIN_OC1B  // --> GPIO_PIN_B2
//#define phase2_pwm_pin GPIO_PIN_OC2A  // --> GPIO_PIN_B3

#define phase0_pwm_pin GPIO_PIN_OC2B  // --> GPIO_PIN_D3
#define phase1_pwm_pin GPIO_PIN_OC0B  // --> GPIO_PIN_D5
#define phase2_pwm_pin GPIO_PIN_OC0A  // --> GPIO_PIN_D6

#define phase0_in_pin  GPIO_PIN_D2
#define phase1_in_pin  GPIO_PIN_D4
#define phase2_in_pin  GPIO_PIN_D7



//#define esc_phase_0_enabled()      TIMER_t02_set_COMB(TIMER2, COM_CLEAR_ON_OCR)
#define esc_phase_0_inactive()     do { \
	TIMER_t02_set_COMB(TIMER2, COM_NORMAL); \
	GPIO_pin_set_low(phase0_pwm_pin); \
} while(0)
#define esc_phase_0_active_low()   do { \
	TIMER_t02_set_COMB(TIMER2, COM_NORMAL); \
	GPIO_pin_set_high(phase0_pwm_pin); \
	GPIO_pin_set_low(phase0_in_pin); \
} while(0)
#define esc_phase_0_active_high()  do { \
	GPIO_pin_set_high(phase0_in_pin); \
	TIMER_t02_set_COMB(TIMER2, COM_CLEAR_ON_OCR); \
} while(0)
#define esc_phase_0_pwm()          TIMER_t02_set_OCRB(TIMER2, val)

//#define esc_phase_1_enabled()      TIMER_t02_set_COMB(TIMER0, COM_CLEAR_ON_OCR)
#define esc_phase_1_inactive()     do { \
		TIMER_t02_set_COMB(TIMER0, COM_NORMAL); \
	GPIO_pin_set_low(phase1_pwm_pin); \
} while(0)
#define esc_phase_1_active_low()   do { \
		TIMER_t02_set_COMB(TIMER0, COM_NORMAL); \
	GPIO_pin_set_high(phase1_pwm_pin); \
	GPIO_pin_set_low(phase1_in_pin); \
} while(0)
#define esc_phase_1_active_high()  do { \
	GPIO_pin_set_high(phase1_in_pin); \
	TIMER_t02_set_COMB(TIMER0, COM_CLEAR_ON_OCR); \
} while(0)
#define esc_phase_1_pwm()          TIMER_t02_set_OCRB(TIMER0, val)

//#define esc_phase_2_enabled()      TIMER_t02_set_COMA(TIMER0, COM_CLEAR_ON_OCR)
#define esc_phase_2_inactive()     do { \
		TIMER_t02_set_COMA(TIMER0, COM_NORMAL); \
	GPIO_pin_set_low(phase1_pwm_pin); \
} while(0)
#define esc_phase_2_active_low()   do { \
		TIMER_t02_set_COMA(TIMER0, COM_NORMAL); \
	GPIO_pin_set_high(phase1_pwm_pin); \
	GPIO_pin_set_low(phase1_in_pin); \
} while(0)
#define esc_phase_2_active_high()  do { \
	GPIO_pin_set_high(phase1_in_pin); \
	TIMER_t02_set_COMA(TIMER0, COM_CLEAR_ON_OCR); \
} while(0)
#define esc_phase_2_pwm()          TIMER_t02_set_OCRA(TIMER0, val)

//#define esc_phase_1_enabled()      TIMER_t02_set_COMB(TIMER0, COM_CLEAR_ON_OCR)
//#define esc_phase_1_disabled()     TIMER_t02_set_COMB(TIMER0, COM_NORMAL)
//#define esc_phase_1_active_low()   GPIO_pin_set_low (phase1_in_pin)
//#define esc_phase_1_active_high()  GPIO_pin_set_high(phase1_in_pin)
//#define esc_phase_1_pwm()          TIMER_t02_set_OCRB(TIMER0, val)
//
//#define esc_phase_2_enabled()      TIMER_t02_set_COMA(TIMER0, COM_CLEAR_ON_OCR)
//#define esc_phase_2_disabled()     TIMER_t02_set_COMA(TIMER0, COM_NORMAL)
//#define esc_phase_2_active_low()   GPIO_pin_set_low (phase2_in_pin)
//#define esc_phase_2_active_high()  GPIO_pin_set_high(phase2_in_pin)
//#define esc_phase_2_pwm(val)       TIMER_t02_set_OCRA(TIMER0, val)




#endif /* _ESC_H_ */
