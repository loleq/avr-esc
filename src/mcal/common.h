/*
 * common.h
 *
 *  Created on: 30 mar 2023
 *      Author: pierba1
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#include "stdint.h"
#define NULL ((void*)0)
#define false (0 == 1)
#define true (!false)
typedef uint8_t bool_t;

typedef volatile uint8_t reg8_t;
typedef reg8_t * p_reg8_t;
typedef struct reg8_bits {
	reg8_t bit0 : 1;
	reg8_t bit1 : 1;
	reg8_t bit2 : 1;
	reg8_t bit3 : 1;
	reg8_t bit4 : 1;
	reg8_t bit5 : 1;
	reg8_t bit6 : 1;
	reg8_t bit7 : 1;
} reg8_bits_t;

typedef volatile uint16_t reg16_t;
typedef reg16_t * p_reg16_t;

typedef struct reg16_bits {
	reg8_t bit0  : 1;
	reg8_t bit1  : 1;
	reg8_t bit2  : 1;
	reg8_t bit3  : 1;
	reg8_t bit4  : 1;
	reg8_t bit5  : 1;
	reg8_t bit6  : 1;
	reg8_t bit7  : 1;
	reg8_t bit8  : 1;
	reg8_t bit9  : 1;
	reg8_t bit10 : 1;
	reg8_t bit11 : 1;
	reg8_t bit12 : 1;
	reg8_t bit13 : 1;
	reg8_t bit14 : 1;
	reg8_t bit15 : 1;
} reg16_bits_t;

#define BIT_HIGH 1U
#define BIT_LOW 0U

inline void reg8_set_bits(volatile uint8_t * addr, uint8_t mask, uint8_t val) {
	*addr = (*addr & (~mask)) | val;
}

inline uint8_t reg8_get_bits(volatile uint8_t * addr, uint8_t mask) {
	return (*addr & (~mask));
}

inline void reg8_set_bit(volatile uint8_t * addr, uint8_t bit, uint8_t val) {
	reg8_set_bits(addr, (1 << bit), (val << bit));
}

inline void reg8_set_bit_high(volatile uint8_t * addr, uint8_t bit) {
	reg8_set_bit(addr, bit, BIT_HIGH);
}

inline void reg8_set_bit_low(volatile uint8_t * addr, uint8_t bit) {
	reg8_set_bit(addr, bit, BIT_LOW);
}

inline uint8_t reg8_get_bit(volatile uint8_t * addr, uint8_t bit) {
	return reg8_get_bits(addr, (1 << bit));
}

#endif /* _COMMON_H_ */
