/*
 * uart.c
 *
 *  Created on: 5 kwi 2023
 *      Author: pierba1
 */
#include "uart.h"
#include <avr/interrupt.h>
#include <util/atomic.h>

uart_registers_t * uart = (uart_registers_t *) UART_REGS_START_ADDR;

//#define TX_SIZE 32U
//uint8_t tx_buffer[TX_SIZE];
//uint8_t tx_start = 0;
//uint8_t tx_end = 0;

#define RX_SIZE 32U
static volatile uint8_t rx_buffer[RX_SIZE];
static volatile uint8_t rx_head = 0;
static volatile uint8_t rx_tail = 0;
#define USETXBUF
#ifdef USETXBUF
#define TX_SIZE 32U
static char tx_buffer[TX_SIZE];
static volatile uint8_t tx_head = 0;
static volatile uint8_t tx_tail = 0;
#else
char tx_buffer;
#endif

static volatile bool_t rx_full = true;

void UART_init(void) {
	uart->reg_UBRRxL.byte = (reg8_t)BAUD_PRESCALE;
	uart->reg_UBRRxH.grouped.g_UBRRxH = (reg8_t)(BAUD_PRESCALE >> 8);

	//uart->reg_UCSRxA.byte = (reg8_t)0x00;
	uart->reg_UCSRxB.grouped.g_RXENx = (reg8_t)0x01;
	uart->reg_UCSRxB.grouped.g_TXENx = (reg8_t)0x01;
	uart->reg_UCSRxB.grouped.g_RXCIEx = (reg8_t)0x01;
	//uart->reg_UCSRxB.grouped.g_TXCIEx = (reg8_t)0x01;
	uart->reg_UCSRxB.grouped.g_UDRIEx = (reg8_t)0x00;
	uart->reg_UCSRxB.grouped.g_UCSZxb2 = (reg8_t)(UCSZ_8 >> 2);

	uart->reg_UCSRxC.grouped.g_UMSELx = (reg8_t)UMSEL_ASYNC;
	uart->reg_UCSRxC.grouped.g_UPMx = (reg8_t)UPM_DISABLED;
	uart->reg_UCSRxC.grouped.g_USBSx = (reg8_t)USBS_2;
	uart->reg_UCSRxC.grouped.g_UCSZxb01 = (reg8_t)UCSZ_8;
}

#define XON  0x11
#define XOFF 0x13
ISR(USART_RX_vect) {
	char ch = uart->reg_UDRx.byte;
	uint8_t rx_head_new = rx_head + 1;

	if(rx_head_new == RX_SIZE) {
		rx_head_new = 0;
	}
	if(rx_head_new == rx_tail) {
		UART_putchar(XOFF, NULL);
		rx_full = 1;
	} else {
		rx_buffer[rx_head] = ch;
		rx_head = rx_head_new;
	}
}

ISR(USART_UDRE_vect) {
#ifdef USETXBUF
	if (tx_head != tx_tail) {
		uart->reg_UDRx.byte = (reg8_t)tx_buffer[tx_tail++];
		if (tx_tail == TX_SIZE) {
			tx_tail = 0;
		}
	} else {
		uart->reg_UCSRxB.grouped.g_UDRIEx = (reg8_t)0x00;
	}
#else
	uart->reg_UDRx.byte = tx_buffer;
#endif
}

int UART_putchar(char c, FILE * stream) {
	(void)stream;
#ifdef USETXBUF
	int ret = 0;

	uint8_t tx_head_new = tx_head + 1;

	if(tx_head_new == TX_SIZE) {
		tx_head_new = 0;
	}
	if(tx_head_new == tx_tail) {
		ret = -1;
	} else {
		tx_buffer[tx_head] = c;
		tx_head = tx_head_new;
		uart->reg_UCSRxB.grouped.g_UDRIEx = (reg8_t)0x01;
	}
	return ret;
#else
	while ( ! uart->reg_UCSRxA.grouped.g_UDREx ) {};
	/* Put data into buffer, sends the data */
	uart->reg_UDRx.byte = (reg8_t)c;
	return -1;
#endif
}

uint8_t UART_busy(void) {
	return uart->reg_UCSRxB.grouped.g_UDRIEx;
}

uint8_t UART_receive(char * buf, uint8_t size) {
	uint8_t len = 0;
	while (rx_head != rx_tail && size) {
		*buf++ = rx_buffer[rx_tail++];
		len++; size--;
		if(rx_tail == RX_SIZE) {
			rx_tail = 0;
		}
	}
	if(rx_full && len) {
		rx_full = false;
		UART_putchar(XON, NULL);
	}
	return len;
}

void clear_rx(void) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		rx_head = 0;
		rx_tail = 0;
	};
}

void UART_critical(char * msg) {
	clear_rx();
	printf(msg);
}


