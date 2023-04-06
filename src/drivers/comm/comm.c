/*
 * comm.c
 *
 *  Created on: 6 kwi 2023
 *      Author: pierba1
 */
#include "comm.h"
#include "uart.h"

static FILE _stdout = FDEV_SETUP_STREAM(UART_putchar, NULL, _FDEV_SETUP_WRITE);


#define RX_SIZE 128
char receive_buffer[RX_SIZE] = {0};
uint8_t fill = 0;

void clr_buffer(void) {
	fill = 0;
}

void parse_cmd(void) {
	char * ch = receive_buffer;
	int ret;
	while(UART_busy()){}; printf("fill = %d\r\n", fill);
	while(UART_busy()){}; printf("%s\r\n", ret);

//	while (ch) {
//		printf("0x%02x\r\n",*ch);
//	}
//	for(uint8_t i = 0; i < fill; i++) {
//		UART_putchar(receive_buffer[i], NULL);
//		UART_putchar('\r', NULL);
//		UART_putchar('\n', NULL);
//		int ret = 0;
//		while(UART_busy()){}; ret = printf("0x%02x\r\n", receive_buffer[i]);
//		while(UART_busy()){}; printf("ret = %i\r\n", ret);

//	}
}

void COMM_init(void) {
	stdout = &_stdout;
}


void COMM_main(void) {
	uint8_t len = UART_receive(receive_buffer + fill, RX_SIZE - 1 - fill);
	if (len) {
		fill += len;
		receive_buffer[fill] = 0;
		char last_char = receive_buffer[fill - 1];
		if ((last_char == '\n') || (last_char == '\r')) {
			parse_cmd();
			clr_buffer();
		}
		if (fill >= RX_SIZE) {
			clr_buffer();
		}
	}
}
