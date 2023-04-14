/*
 * interrupt.c
 *
 *  Created on: 5 kwi 2023
 *      Author: pierba1
 */

#include "interrupt.h"
#include "gpio.h"
#include <avr/interrupt.h>
#include <util/atomic.h>

int_registers_t * interrupts = (int_registers_t *) INT_REGS_START_ADDR;


static pcint_cb_t callbacks[24] = {0};
static uint8_t last[3] = {0};

void INTERRUPT_init(void) {
	INTERRUPT_enable_PCINT_GROUP(PCINT_G0);
	INTERRUPT_enable_PCINT_GROUP(PCINT_G1);
	INTERRUPT_enable_PCINT_GROUP(PCINT_G2);
}

void INTERRUPT_enable_PCINT_GROUP(uint8_t group) {
	reg8_set_bit(
		(uint8_t *)(&interrupts->reg_PCICR),
		(1 << group), 1
	);
}

void INTERRUPT_set_PCINT(pcint_t pcint, pcint_cb_t cb) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		callbacks[8 * pcint.map.group + pcint.map.pin] = cb;
		last[pcint.map.group] |= (GPIO_pin_read((pin_t)pcint.byte) << pcint.map.pin);

		reg8_set_bit(
			(uint8_t *)(&interrupts->reg_PCMSK0) + pcint.map.group,
			(1 << pcint.map.group),	BIT_HIGH
		);
	}
}

void INTERRUPT_unset_PCINT(pcint_t pcint) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		callbacks[8 * pcint.map.group + pcint.map.pin] = NULL;
		last[pcint.map.group] &= ~(1 << pcint.map.pin);

		reg8_set_bit(
			(uint8_t *)(&interrupts->reg_PCMSK0) + pcint.map.group,
			(1 << pcint.map.group),	BIT_LOW
		);
	}
}


ISR(PCINT0_vect) {
	uint8_t pcmsk = (uint8_t)interrupts->reg_PCMSK0.byte;
	uint8_t port  = GPIO_port_read(GPIO_B);
	uint8_t changed = pcmsk & (port ^ last[PCINT_G0]);
	for(uint8_t i = 0; i < 8; i++) {
		if(changed & 0x01) {
			uint8_t state = port & (1 << i);
			last[PCINT_G0] ^= port;
			callbacks[8*PCINT_G0 + i](state >> i);
		}
		changed = changed >> 1;
	}
}

ISR(PCINT1_vect) {
	uint8_t pcmsk = (uint8_t)interrupts->reg_PCMSK1.byte;
	uint8_t port  = GPIO_port_read(GPIO_C);
	uint8_t changed = pcmsk & (port ^ last[PCINT_G1]);
	for(uint8_t i = 0; i < 8; i++) {
		if(changed & 0x01) {
			uint8_t state = port & (1 << i);
			last[PCINT_G1] ^= port;
			callbacks[8*PCINT_G1 + i](state >> i);
		}
		changed = changed >> 1;
	}
}

ISR(PCINT2_vect) {
	uint8_t pcmsk = (uint8_t)interrupts->reg_PCMSK2.byte;
	uint8_t port  = GPIO_port_read(GPIO_D);
	uint8_t changed = pcmsk & (port ^ last[PCINT_G2]);
	for(uint8_t i = 0; i < 8; i++) {
		if(changed & 0x01) {
			uint8_t state = port & (1 << i);
			last[PCINT_G2] ^= port;
			callbacks[8*PCINT_G2 + i](state >> i);
		}
		changed = changed >> 1;
	}
}
