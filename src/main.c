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
	UART_init();
	COMM_init();
	ESC_init();

}

int main(void) {
	init();
	sei(); /* Enable interrupts */

	while (1) {
		COMM_main();
	}
	return 0;
}
