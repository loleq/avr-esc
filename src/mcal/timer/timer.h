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

//#define TIMER0  ((uint8_t)(1 << 0))
//#define TIMER1A ((uint8_t)(1 << 1))
//#define TIMER1B ((uint8_t)(1 << 2))
//#define TIMER1  ((uint8_t)(TIMER1A | TIMER1B))
//#define TIMER2  ((uint8_t)(1 << 3))

#define TIMER0 0U
#define TIMER1 1U
#define TIMER2 2U

//+------+-------+-------+-------+---------------------------------+------+-------------------+-------------------+
//| Mode | WGM02 | WGM01 | WGM00 | Timer/Counter Mode of Operation | TOP  | Update of OCRx at | TOV1 Flag Set on  |
//+------+-------+-------+-------+---------------------------------+------+-------------------+-------------------+
//| 0    | 0     | 0     | 0     | Normal                          | 0xFF | Immediate         | MAX               |
//| 1    | 0     | 0     | 1     | PWM, Phase Correct              | 0xFF | TOP               | BOTTOM            |
//| 2    | 0     | 1     | 0     | CTC                             | OCRA | Immediate         | MAX               |
//| 3    | 0     | 1     | 1     | Fast PWM                        | 0xFF | BOTTOM            | MAX               |
//| 4    | 1     | 0     | 0     | Reserved                        | –    | –                 | –                 |
//| 5    | 1     | 0     | 1     | PWM, Phase Correct              | OCRA | TOP               | BOTTOM            |
//| 6    | 1     | 1     | 0     | Reserved                        | –    | –                 | –                 |
//| 7    | 1     | 1     | 1     | Fast PWM                        | OCRA | BOTTOM            | TOP               |
//+------+-------+-------+-------+---------------------------------+------+-------------------+-------------------+
#define T02_WGM_NORMAL        0x00
#define T02_WGM_PWM_PC_FF     0x01
#define T02_WGM_CTC           0x02
#define T02_WGM_PWM_FAST      0x03
#define T02_WGM_PWM_PC_OCRA   0x05
#define T02_WGM_PWM_FAST_OCRA 0x07



//+------+------+------+----------------------------------------------------------+
//| CS02 | CS01 | CS00 | Description                                              |
//+------+------+------+----------------------------------------------------------+
//| 0    | 0    | 0    | No clock source (Timer/Counter stopped)                  |
//| 0    | 0    | 1    | clkI/O/(No prescaling)                                   |
//| 0    | 1    | 0    | clkI/O/8 (From prescaler)                                |
//| 0    | 1    | 1    | clkI/O/64 (From prescaler)                               |
//| 1    | 0    | 0    | clkI/O/256 (From prescaler)                              |
//| 1    | 0    | 1    | clkI/O/1024 (From prescaler)                             |
//| 1    | 1    | 0    | External clock source on T0 pin. Clock on falling edge.  |
//| 1    | 1    | 1    | External clock source on T0 pin. Clock on rising edge.   |
//+------+------+------+----------------------------------------------------------+
#define CS_CLK_OFF      0x00
#define CS_CLK_FULL     0x01
#define CS_CLK_DIV8     0x02
#define CS_CLK_DIV64    0x03
#define CS_CLK_DIV256   0x04
#define CS_CLK_DIV1024  0x05
#define CS_CLK_EXT_FALL 0x06
#define CS_CLK_EXT_RISE 0x07

#define FOC_ON 1U
#define FOC_OFF 0U



// Compare Output Mode, non-PWM Mode
//+--------+--------+-------------------------------------------+
//| COM0A1 | COM0A0 | Description                               |
//+--------+--------+-------------------------------------------+
//| 0      | 0      | Normal port operation, OC0A disconnected. |
//| 0      | 1      | Toggle OC0A on Compare Match              |
//| 1      | 0      | Clear OC0A on Compare Match               |
//| 1      | 1      | Set OC0A on Compare Match                 |
//+--------+--------+-------------------------------------------+

// Compare Output Mode, Fast PWM Mode
//+--------+--------+-----------------------------------------------------------------------------------------------+
//| COM0A1 | COM0A0 | Description                                                                                   |
//+--------+--------+-----------------------------------------------------------------------------------------------+
//| 0      | 0      | Normal port operation, OC0A disconnected.                                                     |
//| 0      | 1      | WGM02 = 0: Normal Port Operation, OC0A Disconnected.WGM02 = 1: Toggle OC0A on Compare Match.  |
//| 1      | 0      | Clear OC0A on Compare Match, set OC0A at BOTTOM,(non-inverting mode).                         |
//| 1      | 1      | Set OC0A on Compare Match, clear OC0A at BOTTOM,(inverting mode)                              |
//+--------+--------+-----------------------------------------------------------------------------------------------+

// Compare Output Mode, Phase Correct PWM Mode
//+--------+--------+------------------------------------------------------------------------------------------------+
//| COM0A1 | COM0A0 | Description                                                                                    |
//+--------+--------+------------------------------------------------------------------------------------------------+
//| 0      | 0      | Normal port operation, OC0A disconnected.                                                      |
//| 0      | 1      | WGM02 = 0: Normal Port Operation, OC0A Disconnected. WGM02 = 1: Toggle OC0A on Compare Match.  |
//| 1      | 0      | Clear OC0A on Compare Match when up-counting. Set OC0A on Compare Match when down-counting.    |
//| 1      | 1      | Set OC0A on Compare Match when up-counting. Clear OC0A on Compare Match when down-counting.    |
//+--------+--------+------------------------------------------------------------------------------------------------+

// Compare Output Mode, non-PWM Mode
//+--------+--------+--------------------------------------------+
//| COM0B1 | COM0B0 | Description                                |
//+--------+--------+--------------------------------------------+
//| 0      | 0      | Normal port operation, OC0B disconnected.  |
//| 0      | 1      | Toggle OC0B on Compare Match               |
//| 1      | 0      | Clear OC0B on Compare Match                |
//| 1      | 1      | Set OC0B on Compare Match                  |
//+--------+--------+--------------------------------------------+

// Compare Output Mode, Fast PWM Mode
//+--------+--------+------------------------------------------------------------------------+
//| COM0B1 | COM0B0 | Description                                                            |
//+--------+--------+------------------------------------------------------------------------+
//| 0      | 0      | Normal port operation, OC0B disconnected.                              |
//| 0      | 1      | Reserved                                                               |
//| 1      | 0      | Clear OC0B on Compare Match, set OC0B at BOTTOM, (non-inverting mode)  |
//| 1      | 1      | Set OC0B on Compare Match, clear OC0B at BOTTOM, (inverting mode).     |
//+--------+--------+------------------------------------------------------------------------+

// Compare Output Mode, Phase Correct PWM Mode
//+--------+--------+----------------------------------------------------------------------------------------------+
//| COM0B1 | COM0B0 | Description                                                                                  |
//+--------+--------+----------------------------------------------------------------------------------------------+
//| 0      | 0      | Normal port operation, OC0B disconnected.                                                    |
//| 0      | 1      | Reserved                                                                                     |
//| 1      | 0      | Clear OC0B on Compare Match when up-counting. Set OC0B on Compare Match when down-counting.  |
//| 1      | 1      | Set OC0B on Compare Match when up-counting. Clear OC0B on Compare Match when down-counting.  |
//+--------+--------+----------------------------------------------------------------------------------------------+


#define COM_NORMAL        0x00
#define COM_TOGGLE_ON_OCR 0x01
#define COM_CLEAR_ON_OCR  0x02
#define COM_SET_ON_OCR    0x03

extern void TIMER_t02_set_WGM(uint8_t timer, uint8_t wgm);
extern void TIMER_t02_set_CS(uint8_t timer, uint8_t cs);
extern void TIMER_t02_set_FOCA(uint8_t timer, uint8_t foca);
extern void TIMER_t02_set_FOCB(uint8_t timer, uint8_t focb);
extern void TIMER_t02_set_COMA(uint8_t timer, uint8_t coma);
extern void TIMER_t02_set_COMB(uint8_t timer, uint8_t comb);
extern void TIMER_t02_set_OCRA(uint8_t timer, uint8_t ocra);
extern void TIMER_t02_set_OCRB(uint8_t timer, uint8_t ocrb);
extern void TIMER_t02_set_TCN(uint8_t timer, uint8_t tcnt);

#endif /* _TIMER_H_ */
