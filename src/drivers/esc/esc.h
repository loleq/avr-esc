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


/* MOSFET drivers pin configuration */
#define ESC_PIN_PHASE_A_SD (PB1)
#define ESC_PIN_PHASE_B_SD (PB2)
#define ESC_PIN_PHASE_C_SD (PB3)
#define ESC_PORT_SD        (PORTB)
#define ESC_DDR_SD         (DDRB)


#define ESC_PIN_PHASE_A_IN (PD5)
#define ESC_PIN_PHASE_B_IN (PD4)
#define ESC_PIN_PHASE_C_IN (PD3)
#define ESC_PORT_IN        (PORTD)
#define ESC_DDR_IN         (DDRD)


#define REG8_SET(reg, val) reg = (uint8_t)val;
#define REG8_SET_MASKED(reg, val, mask) reg |= (uint8_t)(val & mask)

#define BIT8_SET(reg, pos) reg |= _BV(pos)
#define BIT8_CLR(reg, pos) reg &= ~_BV(pos)

#define ESC_PHASE_A_OFF BIT8_CLR()


typedef struct esc_phase_config {
	pin_t pin_sd;
	pin_t pin_in;
	uint8_t timer;
} esc_phase_config_t;

typedef struct esc_config {
	esc_phase_config_t phase[3];
} esc_config_t;

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

#define esc_phase_0_sd_low()   GPIO_pin_set_low (phase0_pwm_pin)
#define esc_phase_0_sd_high()  GPIO_pin_set_high(phase0_pwm_pin)
#define esc_phase_0_in_low()   GPIO_pin_set_low (phase0_in_pin)
#define esc_phase_0_in_high()  GPIO_pin_set_high(phase0_in_pin)
#define esc_phase_0_pwm()      TIMER_t02_set_OCRB(TIMER2, val)

#define esc_phase_1_sd_low()   GPIO_pin_set_low (phase1_pwm_pin)
#define esc_phase_1_sd_high()  GPIO_pin_set_high(phase1_pwm_pin)
#define esc_phase_1_in_low()   GPIO_pin_set_low (phase1_in_pin)
#define esc_phase_1_in_high()  GPIO_pin_set_high(phase1_in_pin)
#define esc_phase_1_pwm()      TIMER_t02_set_OCRB(TIMER0, val)

#define esc_phase_2_sd_low()   GPIO_pin_set_low (phase2_pwm_pin)
#define esc_phase_2_sd_high()  GPIO_pin_set_high(phase2_pwm_pin)
#define esc_phase_2_in_low()   GPIO_pin_set_low (phase2_in_pin)
#define esc_phase_2_in_high()  GPIO_pin_set_high(phase2_in_pin)
#define esc_phase_2_pwm(val)   TIMER_t02_set_OCRA(TIMER0, val)

#endif /* _ESC_H_ */
