/*
 * timer.c
 *
 *  Created on: 31 mar 2023
 *      Author: pierba1
 */

#include "timer.h"

timer_t02_registers_t * timer0 = (timer_t02_registers_t *) TIMER0_REGS_START_ADDR;
timer_t02_registers_t * timer2 = (timer_t02_registers_t *) TIMER2_REGS_START_ADDR;
timer_t1_registers_t  * timer1 = (timer_t1_registers_t *)  TIMER1_REGS_START_ADDR;


void TIMER_t02_set_WGM(uint8_t timer, uint8_t wgm) {
	timer_t02_registers_t * t = timer == TIMER0 ? timer0 : timer2;
	t->reg_TCCRA.grouped.g_WGM_b01 = (wgm & 0x03);
	t->reg_TCCRB.grouped.g_WGM_b2  = (wgm & 0x04);
}

void TIMER_t02_set_CS(uint8_t timer, uint8_t cs) {
	timer_t02_registers_t * t = timer == TIMER0 ? timer0 : timer2;
	t->reg_TCCRB.grouped.g_CS = cs;
}

void TIMER_t02_set_FOCA(uint8_t timer, uint8_t foca) {
	timer_t02_registers_t * t = timer == TIMER0 ? timer0 : timer2;
	t->reg_TCCRB.grouped.g_FOCA = foca;
}

void TIMER_t02_set_FOCB(uint8_t timer, uint8_t focb) {
	timer_t02_registers_t * t = timer == TIMER0 ? timer0 : timer2;
	t->reg_TCCRB.grouped.g_FOCB = focb;
}

void TIMER_t02_set_COMA(uint8_t timer, uint8_t coma) {
	timer_t02_registers_t * t = timer == TIMER0 ? timer0 : timer2;
	t->reg_TCCRA.grouped.g_COMA = coma;
}

void TIMER_t02_set_COMB(uint8_t timer, uint8_t comb) {
	timer_t02_registers_t * t = timer == TIMER0 ? timer0 : timer2;
	t->reg_TCCRA.grouped.g_COMB = comb;
}

void TIMER_t02_set_OCRA(uint8_t timer, uint8_t ocra) {
	timer_t02_registers_t * t = timer == TIMER0 ? timer0 : timer2;
	t->reg_OCRA.byte = ocra;
}

void TIMER_t02_set_OCRB(uint8_t timer, uint8_t ocrb) {
	timer_t02_registers_t * t = timer == TIMER0 ? timer0 : timer2;
	t->reg_OCRB.byte = ocrb;
}

void TIMER_t02_set_TCN(uint8_t timer, uint8_t tcnt) {
	timer_t02_registers_t * t = timer == TIMER0 ? timer0 : timer2;
	t->reg_TCNT.byte = tcnt;
}

