/*
 * extint.h
 *
 *  Created on: 4 kwi 2023
 *      Author: pierba1
 */

#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "common.h"

typedef union {
	uint8_t byte;
	struct {
		uint8_t pin  : 3;
		uint8_t group : 2;
	} map;
} pcint_t;

#define INT_REGS_START_ADDR (0x68)

typedef struct int_registers {
	union {
		reg8_t byte;
		reg8_bits_t bits;
		struct {
			reg8_t g_PCIE0 : 1;
			reg8_t g_PCIE1 : 1;
			reg8_t g_PCIE2 : 1;
			reg8_t g_unused : 5;
		} grouped;
	} reg_PCICR;
	union {
		reg8_t byte;
		reg8_bits_t bits;
		struct {
			reg8_t g_ISC0 : 2;
			reg8_t g_ISC1 : 2;
			reg8_t g_unused : 4;
		} grouped;
	} reg_EICRA;
	reg8_t reserved;
	union {
		reg8_t byte;
		reg8_bits_t bits;
		struct {
			reg8_t g_PCINT0 : 1;
			reg8_t g_PCINT1 : 1;
			reg8_t g_PCINT2 : 1;
			reg8_t g_PCINT3 : 1;
			reg8_t g_PCINT4 : 1;
			reg8_t g_PCINT5 : 1;
			reg8_t g_PCINT6 : 1;
			reg8_t g_PCINT7 : 1;
		} grouped;
	} reg_PCMSK0;
	union {
		reg8_t byte;
		reg8_bits_t bits;
		struct {
			reg8_t g_PCINT8  : 1;
			reg8_t g_PCINT9  : 1;
			reg8_t g_PCINT10 : 1;
			reg8_t g_PCINT11 : 1;
			reg8_t g_PCINT12 : 1;
			reg8_t g_PCINT13 : 1;
			reg8_t g_PCINT14 : 1;
			reg8_t g_unused : 1;
		} grouped;
	} reg_PCMSK1;
	union {
		reg8_t byte;
		reg8_bits_t bits;
		struct {
			reg8_t g_PCINT16 : 1;
			reg8_t g_PCINT17 : 1;
			reg8_t g_PCINT18 : 1;
			reg8_t g_PCINT19 : 1;
			reg8_t g_PCINT20 : 1;
			reg8_t g_PCINT21 : 1;
			reg8_t g_PCINT22 : 1;
			reg8_t g_PCINT23 : 1;
		} grouped;
	} reg_PCMSK2;
	union {
		reg8_t byte;
		reg8_bits_t bits;
		struct {
			reg8_t g_TOIE0  : 1;
			reg8_t g_OCIE0A : 1;
			reg8_t g_OCIE0B : 1;
			reg8_t g_unused : 5;
		} grouped;
	} reg_TIMSK0;
	union {
		reg8_t byte;
		reg8_bits_t bits;
		struct {
			reg8_t g_TOIE1   : 1;
			reg8_t g_OCIE1A  : 1;
			reg8_t g_OCIE1B  : 1;
			reg8_t g_unused  : 2;
			reg8_t g_ICIE1   : 1;
			reg8_t g_unused2 : 2;
		} grouped;
	} reg_TIMSK1;
	union {
		reg8_t byte;
		reg8_bits_t bits;
		struct {
			reg8_t g_TOIE2  : 1;
			reg8_t g_OCIE2A : 1;
			reg8_t g_OCIE2B : 1;
			reg8_t g_unused : 5;
		} grouped;
	} reg_TIMSK2;
} int_registers_t;



#define _PCINT_STRUCT_PIN_OFFSET 0U
#define _PCINT_STRUCT_PCMSK_OFFSET 3U
#define _PCINT_STRUCT_BUILD(port, pin) ((pin_t)((uint8_t)(((uint8_t)(port << _PCINT_STRUCT_PCMSK_OFFSET)) | ((uint8_t)(pin << _PCINT_STRUCT_PIN_OFFSET)))))

#define MSK_0 0U
#define MSK_1 1U
#define MSK_2 2U

#define PCINT00 _PCINT_STRUCT_BUILD(MSK_0, 0)
#define PCINT01 _PCINT_STRUCT_BUILD(MSK_0, 1)
#define PCINT02 _PCINT_STRUCT_BUILD(MSK_0, 2)
#define PCINT03 _PCINT_STRUCT_BUILD(MSK_0, 3)
#define PCINT04 _PCINT_STRUCT_BUILD(MSK_0, 4)
#define PCINT05 _PCINT_STRUCT_BUILD(MSK_0, 5)
#define PCINT06 _PCINT_STRUCT_BUILD(MSK_0, 6)
#define PCINT07 _PCINT_STRUCT_BUILD(MSK_0, 7)
#define PCINT08 _PCINT_STRUCT_BUILD(MSK_1, 0)
#define PCINT09 _PCINT_STRUCT_BUILD(MSK_1, 1)
#define PCINT10 _PCINT_STRUCT_BUILD(MSK_1, 2)
#define PCINT11 _PCINT_STRUCT_BUILD(MSK_1, 3)
#define PCINT12 _PCINT_STRUCT_BUILD(MSK_1, 4)
#define PCINT13 _PCINT_STRUCT_BUILD(MSK_1, 5)
#define PCINT14 _PCINT_STRUCT_BUILD(MSK_1, 6)
#define PCINT15 _PCINT_STRUCT_BUILD(MSK_1, 7)
#define PCINT16 _PCINT_STRUCT_BUILD(MSK_2, 0)
#define PCINT17 _PCINT_STRUCT_BUILD(MSK_2, 1)
#define PCINT18 _PCINT_STRUCT_BUILD(MSK_2, 2)
#define PCINT19 _PCINT_STRUCT_BUILD(MSK_2, 3)
#define PCINT20 _PCINT_STRUCT_BUILD(MSK_2, 4)
#define PCINT21 _PCINT_STRUCT_BUILD(MSK_2, 5)
#define PCINT22 _PCINT_STRUCT_BUILD(MSK_2, 6)
#define PCINT23 _PCINT_STRUCT_BUILD(MSK_2, 7)

typedef void (*pcint_cb_t) (uint8_t state);
extern void INTERRUPT_set_PCINT(pcint_t pcint, pcint_cb_t cb);



#endif /* _INTERRUPT_H_ */
