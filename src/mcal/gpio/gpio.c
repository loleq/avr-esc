/*
 * port.c
 *
 *  Created on: 31 mar 2023
 *      Author: pierba1
 */

#include "gpio.h"

port_registers_t * gpio = (port_registers_t *)GPIO_REGS_START_ADDR;


void GPIO_pin_set_high(pin_t pin) {
	p_reg8_t reg = (p_reg8_t) &gpio->port[pin.map.port].reg_PORT;
	reg8_set_bit_high(reg, pin.map.pin);
}

void GPIO_pin_set_low(pin_t pin) {
	p_reg8_t reg = (p_reg8_t) &gpio->port[pin.map.port].reg_PORT;
	reg8_set_bit_low(reg, pin.map.pin);
}

void GPIO_pin_toggle(pin_t pin) {
	p_reg8_t reg = (p_reg8_t) &gpio->port[pin.map.port].reg_PIN;
	reg8_set_bit_high(reg, pin.map.pin);
}

void GPIO_pin_set_dir_out(pin_t pin) {
	p_reg8_t reg = (p_reg8_t) &gpio->port[pin.map.port].reg_DDR;
	reg8_set_bit_high(reg, pin.map.pin);
}

void GPIO_pin_set_dir_in(pin_t pin) {
	p_reg8_t reg = (p_reg8_t) &gpio->port[pin.map.port].reg_DDR;
	reg8_set_bit_low(reg, pin.map.pin);
}

void GPIO_pin_config(pin_t pin, uint8_t dir, uint8_t state) {
	p_reg8_t reg = (p_reg8_t) &gpio->port[pin.map.port].reg_DDR;
	reg8_set_bit(reg, pin.map.pin, dir);
	reg++; /* switch to reg_PORT */
	reg8_set_bit(reg, pin.map.pin, state);
}

uint8_t GPIO_pin_read(pin_t pin) {
	p_reg8_t reg = (p_reg8_t) &gpio->port[pin.map.port].reg_PORT;
	return reg8_get_bit(reg, pin.map.pin);
}

uint8_t GPIO_port_read(uint8_t group) {
	return (uint8_t) gpio->port[group].reg_PORT.byte;
}
