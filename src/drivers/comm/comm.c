/*
 * comm.c
 *
 *  Created on: 6 kwi 2023
 *      Author: pierba1
 */
#include "comm.h"
#include "uart.h"
#include "esc.h"

#define RX_SIZE 64
static char rx_buffer[RX_SIZE] = {0};
uint8_t fill = 0;

void clr_buffer(void) {
	fill = 0;
}

#include <stdlib.h>
uint8_t parse_power() {
	uint8_t ret = 0;
	char * p = &rx_buffer[1];
	char d = *p;
	while ((d >= '0') && (d <= '9')) {
		ret = 10 * ret + d - '0';
		d = *(++p);
	}
	return ret;
}

void parse_cmd(void) {
	switch(rx_buffer[0]) {
		case 't': /* star[t] */
			ESC_change_request(START);
			break;
		case 'p': /* sto[p] */
			ESC_change_request(STOP);
			break;
		case 'm': { /* pw[m] */
			uint8_t power = parse_power();
			ESC_set_power(power);
		}
			break;
		case 'r': /* di[r] */
			break;
#ifdef STEP_MODE
		case 'c': /* commute */
			ESC_commute = true;
#endif
		default:
			break;
	}
}


void COMM_init(void) {

}


void COMM_main(void) {
	uint8_t len = UART_receive(rx_buffer + fill, RX_SIZE - fill);
	if (len) {
		fill += len;
		rx_buffer[fill] = 0;
		char last_char = rx_buffer[fill - 1];
		if ((last_char == '\n') || (last_char == '\r')) {
			fill--;
			parse_cmd();
			clr_buffer();
		}
		if (fill >= RX_SIZE) {
			clr_buffer();
		}
	}
}
