/*
 * port.h
 *
 *  Created on: 30 mar 2023
 *      Author: pierba1
 */

#ifndef _GPIO_H_
#define _GPIO_H_

#include "common.h"
#include "avr/io.h"

typedef struct port_group_registers {
	union {
		reg8_t byte;
		reg8_bits_t bits;
	} reg_PIN;
	union {
		reg8_t byte;
		reg8_bits_t bits;
	} reg_DDR;
	union {
		reg8_t byte;
		reg8_bits_t bits;
	} reg_PORT;
} port_group_registers_t;

typedef struct port_registers {
	port_group_registers_t port[3];
} port_registers_t;


#define PORT_REGS_START_ADDR (p_reg8_t)(__SFR_OFFSET + 0x03)

#define PIN_REG_OFFSET (0)
#define DDR_REG_OFFSET (1)
#define PORT_REG_OFFSET (2)

#define PORT_OFFSET (3)

#define PORT_B (0u)
#define PORT_C (1u)
#define PORT_D (2u)

typedef union {
	uint8_t byte;
	struct {
		uint8_t pin  : 3;
		uint8_t port : 2;
	} map;
} pin_t;


#define _PIN_STRUCT_PIN_OFFSET 0U
#define _PIN_STRUCT_PORT_OFFSET 3U
#define _PIN_STRUCT_BUILD(port, pin) ((pin_t)(((uint8_t)(port << _PIN_STRUCT_PORT_OFFSET)) | ((uint8_t)(pin << _PIN_STRUCT_PIN_OFFSET))))

#define PIN_B0 _PIN_STRUCT_BUILD(PORT_B, 0)
#define PIN_B1 _PIN_STRUCT_BUILD(PORT_B, 1)
#define PIN_B2 _PIN_STRUCT_BUILD(PORT_B, 2)
#define PIN_B3 _PIN_STRUCT_BUILD(PORT_B, 3)
#define PIN_B4 _PIN_STRUCT_BUILD(PORT_B, 4)
#define PIN_B5 _PIN_STRUCT_BUILD(PORT_B, 5)
#define PIN_B6 _PIN_STRUCT_BUILD(PORT_B, 6)
#define PIN_B7 _PIN_STRUCT_BUILD(PORT_B, 7)
#define PIN_C0 _PIN_STRUCT_BUILD(PORT_C, 0)
#define PIN_C1 _PIN_STRUCT_BUILD(PORT_C, 1)
#define PIN_C2 _PIN_STRUCT_BUILD(PORT_C, 2)
#define PIN_C3 _PIN_STRUCT_BUILD(PORT_C, 3)
#define PIN_C4 _PIN_STRUCT_BUILD(PORT_C, 4)
#define PIN_C5 _PIN_STRUCT_BUILD(PORT_C, 5)
#define PIN_C6 _PIN_STRUCT_BUILD(PORT_C, 6)
#define PIN_C7 _PIN_STRUCT_BUILD(PORT_C, 7)
#define PIN_D0 _PIN_STRUCT_BUILD(PORT_D, 0)
#define PIN_D1 _PIN_STRUCT_BUILD(PORT_D, 1)
#define PIN_D2 _PIN_STRUCT_BUILD(PORT_D, 2)
#define PIN_D3 _PIN_STRUCT_BUILD(PORT_D, 3)
#define PIN_D4 _PIN_STRUCT_BUILD(PORT_D, 4)
#define PIN_D5 _PIN_STRUCT_BUILD(PORT_D, 5)
#define PIN_D6 _PIN_STRUCT_BUILD(PORT_D, 6)
#define PIN_D7 _PIN_STRUCT_BUILD(PORT_D, 7)

/* PIN works as output */
#define PORT_STATE_HIGH 1U
#define PORT_STATE_LOW 0U
/* PIN works as input */
#define PORT_STATE_PULL_UP 1U
#define PORT_STATE_HIGH_Z 0U


extern port_group_registers_t * ports;

extern void PORT_pin_set_high(pin_t pin);
extern void PORT_pin_set_low(pin_t pin);
extern void PORT_pin_toggle(pin_t pin);
extern void PORT_pin_config(pin_t pin, uint8_t dir, uint8_t state);

#endif /* _GPIO_H_ */
