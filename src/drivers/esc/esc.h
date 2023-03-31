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


typedef struct phase_config {
	pin_t pin_sd;
	pin_t pin_in;
	uint8_t timer;
} esc_phase_config_t;

typedef struct esc_config {
	esc_phase_config_t phase[3];
} esc_config_t;





#endif /* _ESC_H_ */
