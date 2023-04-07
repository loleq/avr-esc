/*
 * main.c
 *
 *  Created on: 25 mar 2023
 *      Author: bpierzy
 */

#include "esc.h"
#include "uart.h"
#include "comm.h"
#include <stdio.h>
#include <avr/interrupt.h>

void init(void) {
	TIMER_t1_init();
	UART_init();
	COMM_init();
	ESC_init();

	GPIO_pin_config(GPIO_PIN_C0, GPIO_DIR_OUT, GPIO_STATE_LOW);
}

uint32_t tick;
int main(void) {
	init();
	sei(); /* Enable interrupts */
	while (1) {
		GPIO_pin_set_high(GPIO_PIN_C0);
		tick = sys_time_100us;

		COMM_main();
		ESC_main();

		GPIO_pin_set_low(GPIO_PIN_C0);
		while(tick == sys_time_100us) {};
	}
	return 0;
}
