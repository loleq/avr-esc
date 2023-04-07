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

const char newline[2] = {'\r', '\n'};
const char space[1] = {' '};
void parse_cmd(void) {
//	char tmp[3];
//	uint8_t len = snprintf(tmp, 3, "%d", fill);
//	(void)UART_send(receive_buffer, fill, true);
//	(void)UART_send(space, 1, true);
//	(void)UART_send(tmp, len, true);
//	(void)UART_send(newline, 2, true);

	switch(rx_buffer[0]) {
		case 't': /* star[t] */
		case 'p': /* sto[p] */
		case 'm': /* pw[m] */
		case 'r': /* di[r] */
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
