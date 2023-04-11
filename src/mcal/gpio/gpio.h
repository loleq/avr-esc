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


#define GPIO_REGS_START_ADDR (__SFR_OFFSET + 0x03)

#define PIN_REG_OFFSET (0)
#define DDR_REG_OFFSET (1)
#define GPIO_REG_OFFSET (2)

#define GPIO_OFFSET (3)

#define GPIO_B (0u)
#define GPIO_C (1u)
#define GPIO_D (2u)

typedef union {
	uint8_t byte;
	struct {
		uint8_t pin  : 3;
		uint8_t port : 2;
	} map;
} pin_t;


#define _PIN_STRUCT_PIN_OFFSET 0U
#define _PIN_STRUCT_GPIO_OFFSET 3U
#define _PIN_STRUCT_BUILD(port, pin) ((pin_t)((uint8_t)(((uint8_t)(port << _PIN_STRUCT_GPIO_OFFSET)) | ((uint8_t)(pin << _PIN_STRUCT_PIN_OFFSET)))))

#define GPIO_PIN_B0 _PIN_STRUCT_BUILD(GPIO_B, 0)
#define GPIO_PIN_B1 _PIN_STRUCT_BUILD(GPIO_B, 1)
#define GPIO_PIN_B2 _PIN_STRUCT_BUILD(GPIO_B, 2)
#define GPIO_PIN_B3 _PIN_STRUCT_BUILD(GPIO_B, 3)
#define GPIO_PIN_B4 _PIN_STRUCT_BUILD(GPIO_B, 4)
#define GPIO_PIN_B5 _PIN_STRUCT_BUILD(GPIO_B, 5)
#define GPIO_PIN_B6 _PIN_STRUCT_BUILD(GPIO_B, 6)
#define GPIO_PIN_B7 _PIN_STRUCT_BUILD(GPIO_B, 7)
#define GPIO_PIN_C0 _PIN_STRUCT_BUILD(GPIO_C, 0)
#define GPIO_PIN_C1 _PIN_STRUCT_BUILD(GPIO_C, 1)
#define GPIO_PIN_C2 _PIN_STRUCT_BUILD(GPIO_C, 2)
#define GPIO_PIN_C3 _PIN_STRUCT_BUILD(GPIO_C, 3)
#define GPIO_PIN_C4 _PIN_STRUCT_BUILD(GPIO_C, 4)
#define GPIO_PIN_C5 _PIN_STRUCT_BUILD(GPIO_C, 5)
#define GPIO_PIN_C6 _PIN_STRUCT_BUILD(GPIO_C, 6)
#define GPIO_PIN_C7 _PIN_STRUCT_BUILD(GPIO_C, 7)
#define GPIO_PIN_D0 _PIN_STRUCT_BUILD(GPIO_D, 0)
#define GPIO_PIN_D1 _PIN_STRUCT_BUILD(GPIO_D, 1)
#define GPIO_PIN_D2 _PIN_STRUCT_BUILD(GPIO_D, 2)
#define GPIO_PIN_D3 _PIN_STRUCT_BUILD(GPIO_D, 3)
#define GPIO_PIN_D4 _PIN_STRUCT_BUILD(GPIO_D, 4)
#define GPIO_PIN_D5 _PIN_STRUCT_BUILD(GPIO_D, 5)
#define GPIO_PIN_D6 _PIN_STRUCT_BUILD(GPIO_D, 6)
#define GPIO_PIN_D7 _PIN_STRUCT_BUILD(GPIO_D, 7)


/* PIN alternate functions */
#define GPIO_PIN_PCINT0   GPIO_PIN_B0
#define GPIO_PIN_CLKO     GPIO_PIN_B0
#define GPIO_PIN_ICP1     GPIO_PIN_B0

#define GPIO_PIN_PCINT1   GPIO_PIN_B1
#define GPIO_PIN_OC1A     GPIO_PIN_B1

#define GPIO_PIN_PCINT2   GPIO_PIN_B2
#define GPIO_PIN_OC1B     GPIO_PIN_B2
#define GPIO_PIN_SS       GPIO_PIN_B2

#define GPIO_PIN_PCINT3   GPIO_PIN_B3
#define GPIO_PIN_OC2A     GPIO_PIN_B3
#define GPIO_PIN_MOSI     GPIO_PIN_B3

#define GPIO_PIN_PCINT4   GPIO_PIN_B4
#define GPIO_PIN_MISO     GPIO_PIN_B4

#define GPIO_PIN_PCINT5   GPIO_PIN_B5
#define GPIO_PIN_SCK      GPIO_PIN_B5

#define GPIO_PIN_PCINT6   GPIO_PIN_B6
#define GPIO_PIN_TOSC1    GPIO_PIN_B6
#define GPIO_PIN_XTAL1    GPIO_PIN_B6

#define GPIO_PIN_PCINT7   GPIO_PIN_B7
#define GPIO_PIN_TOSC2    GPIO_PIN_B7
#define GPIO_PIN_XTAL2    GPIO_PIN_B7

#define GPIO_PIN_PCINT8   GPIO_PIN_C0
#define GPIO_PIN_ADC0     GPIO_PIN_C0

#define GPIO_PIN_PCINT9   GPIO_PIN_C1
#define GPIO_PIN_ADC1     GPIO_PIN_C1

#define GPIO_PIN_PCINT10  GPIO_PIN_C2
#define GPIO_PIN_ADC2     GPIO_PIN_C2

#define GPIO_PIN_PCINT11  GPIO_PIN_C3
#define GPIO_PIN_ADC3     GPIO_PIN_C3

#define GPIO_PIN_PCINT12  GPIO_PIN_C4
#define GPIO_PIN_SDA      GPIO_PIN_C4
#define GPIO_PIN_ADC4     GPIO_PIN_C4

#define GPIO_PIN_PCINT13  GPIO_PIN_C5
#define GPIO_PIN_SCL      GPIO_PIN_C5
#define GPIO_PIN_ADC5     GPIO_PIN_C5

#define GPIO_PIN_PCINT14  GPIO_PIN_C6
#define GPIO_PIN_RESET    GPIO_PIN_C6

#define GPIO_PIN_PCINT16  GPIO_PIN_D0
#define GPIO_PIN_RXD      GPIO_PIN_D0

#define GPIO_PIN_PCINT17  GPIO_PIN_D1
#define GPIO_PIN_TXD      GPIO_PIN_D1

#define GPIO_PIN_PCINT18  GPIO_PIN_D2
#define GPIO_PIN_INT0     GPIO_PIN_D2

#define GPIO_PIN_PCINT19  GPIO_PIN_D3
#define GPIO_PIN_OC2B     GPIO_PIN_D3
#define GPIO_PIN_INT1     GPIO_PIN_D3

#define GPIO_PIN_PCINT20  GPIO_PIN_D4
#define GPIO_PIN_T0       GPIO_PIN_D4
#define GPIO_PIN_XCK      GPIO_PIN_D4

#define GPIO_PIN_PCINT21  GPIO_PIN_D5
#define GPIO_PIN_OC0B     GPIO_PIN_D5
#define GPIO_PIN_T1       GPIO_PIN_D5

#define GPIO_PIN_PCINT22  GPIO_PIN_D6
#define GPIO_PIN_OC0A     GPIO_PIN_D6
#define GPIO_PIN_AIN0     GPIO_PIN_D6

#define GPIO_PIN_PCINT23  GPIO_PIN_D7
#define GPIO_PIN_AIN1     GPIO_PIN_D7



#define GPIO_DIR_IN 0U
#define GPIO_DIR_OUT 1U

/* PIN works as output */
#define GPIO_STATE_HIGH 1U
#define GPIO_STATE_LOW 0U
/* PIN works as input */
#define GPIO_STATE_PULL_UP 1U
#define GPIO_STATE_HIGH_Z 0U


extern port_group_registers_t * ports;

extern void GPIO_pin_set_high(pin_t pin);
extern void GPIO_pin_set_low(pin_t pin);
extern void GPIO_pin_toggle(pin_t pin);
extern void GPIO_pin_config(pin_t pin, uint8_t dir, uint8_t state);
extern uint8_t GPIO_pin_read(pin_t pin);
extern uint8_t GPIO_port_read(uint8_t group);

#endif /* _GPIO_H_ */
