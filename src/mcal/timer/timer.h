/*
 * timer.h
 *
 *  Created on: 30 mar 2023
 *      Author: pierba1
 */

#ifndef _TIMER_H_
#define _TIMER_H_

#include "common.h"

#define TIMER0_REGS_START_ADDR (0x44)
#define TIMER1_REGS_START_ADDR (0x80)
#define TIMER2_REGS_START_ADDR (0xB0)

typedef struct timer_t02_registers {
	union {
		reg8_t byte;
		reg8_bits_t bits;
		struct {
			reg8_t g_WGM_b01 : 2;
			reg8_t g_unused  : 2;
			reg8_t g_COMB    : 2;
			reg8_t g_COMA    : 2;
		} grouped;
	} reg_TCCRA;
	union {
		reg8_t byte;
		reg8_bits_t bits;
		struct {
			reg8_t g_CS     : 3;
			reg8_t g_WGM_b2 : 1;
			reg8_t g_unused : 2;
			reg8_t g_FOCB   : 1;
			reg8_t g_FOCA   : 1;
		} grouped;
	} reg_TCCRB;
	union {
		reg8_t byte;
		reg8_bits_t bits;

	} reg_TCNT;
	union {
		reg8_t byte;
		reg8_bits_t bits;
	} reg_OCRA;
	union {
		reg8_t byte;
		reg8_bits_t bits;
	} reg_OCRB;
} timer_t02_registers_t;

typedef struct timer_t1_registers {
	union {
		reg8_t byte;
		reg8_bits_t bits;
		struct {
			reg8_t g_WGM_b01 :2;
			reg8_t g_unused  :2;
			reg8_t g_COMB    :2;
			reg8_t g_COMA    :2;
		} grouped;
	} reg_TCCRA;
	union {
		reg8_t byte;
		reg8_bits_t bits;
		struct {
			reg8_t g_CS      : 3;
			reg8_t g_WGM_b23 : 2;
			reg8_t g_unused  : 1;
			reg8_t g_ICES    : 1;
			reg8_t g_ICNC    : 1;
		} grouped;
	} reg_TCCRB;
	union {
		reg8_t byte;
		reg8_bits_t bits;
		struct {
			reg8_t g_unused : 6;
			reg8_t g_FOCB   : 1;
			reg8_t g_FOCA   : 1;
		} grouped;
	} reg_TCCRC;
	reg8_t reg_Reserved;
	union {
		reg16_t word;
		reg16_bits_t bits;
		union {
			reg8_t byte;
			reg8_bits_t bits;
		} reg_TCNTL;
		union {
			reg8_t byte;
			reg8_bits_t bits;
		} reg_TCNTH;
	} reg_TCNT;
	union {
		reg16_t word;
		reg16_bits_t bits;
		union {
			reg8_t byte;
			reg8_bits_t bits;
		} reg_ICRL;
		union {
			reg8_t byte;
			reg8_bits_t bits;
		} reg_ICRH;
	} reg_ICR;
	union {
		reg16_t word;
		reg16_bits_t bits;
		union {
			reg8_t byte;
			reg8_bits_t bits;
		} reg_OCRAL;
		union {
			reg8_t byte;
			reg8_bits_t bits;
		} reg_OCRAH;
	} reg_OCRA;
	union {
		reg16_t word;
		reg16_bits_t bits;
		union {
			reg8_t byte;
			reg8_bits_t bits;
		} reg_OCRBL;
		union {
			reg8_t byte;
			reg8_bits_t bits;
		} reg_OCRBH;
	} reg_OCRB;
} timer_t1_registers_t;

extern timer_t02_registers_t * timer0;
extern timer_t02_registers_t * timer2;
extern timer_t1_registers_t * timer1;


#endif /* _TIMER_H_ */
