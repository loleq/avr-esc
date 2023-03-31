/*
 * timer.c
 *
 *  Created on: 31 mar 2023
 *      Author: pierba1
 */

#include "timer.h"

timer_t02_registers_t * timer0 = (timer_t02_registers_t *) TIMER0_REGS_START_ADDR;
timer_t02_registers_t * timer2  = (timer_t02_registers_t *) TIMER2_REGS_START_ADDR;
timer_t1_registers_t * timer1 = (timer_t1_registers_t *) TIMER1_REGS_START_ADDR;
