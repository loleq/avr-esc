/*
 * port.c
 *
 *  Created on: 31 mar 2023
 *      Author: pierba1
 */

#include "gpio.h"

port_registers_t * gpio = PORT_REGS_START_ADDR;



void PORT_pin_set_high(pin_t pin) {
	p_reg8_t reg = (p_reg8_t) &gpio->port[pin.map.port].reg_PORT;
	reg8_set_bit_high(reg, pin.map.pin);
}

void PORT_pin_set_low(pin_t pin) {
	p_reg8_t reg = (p_reg8_t) &gpio->port[pin.map.port].reg_PORT;
	reg8_set_bit_low(reg, pin.map.pin);
}

void PORT_pin_toggle(pin_t pin) {
	p_reg8_t reg = (p_reg8_t) &gpio->port[pin.map.port].reg_PIN;
	reg8_set_bit_high(reg, pin.map.pin);
}

void PORT_pin_set_output(pin_t pin) {
	p_reg8_t reg = (p_reg8_t) &gpio->port[pin.map.port].reg_DDR;
	reg8_set_bit_high(reg, pin.map.pin);
}

void PORT_pin_set_input(pin_t pin) {
	p_reg8_t reg = (p_reg8_t) &gpio->port[pin.map.port].reg_DDR;
	reg8_set_bit_low(reg, pin.map.pin);
}

void PORT_pin_config(pin_t pin, uint8_t dir, uint8_t state) {

}
