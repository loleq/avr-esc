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
#define TX_SIZE 32U
static char tx_buffer[TX_SIZE];
static volatile uint8_t tx_head = 0;
static volatile uint8_t tx_tail = 0;


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

	if (rx_head_new == RX_SIZE) {
		rx_head_new = 0;
	}
	if (rx_head_new != rx_tail) {
		rx_buffer[rx_head] = ch;
		rx_head = rx_head_new;
	} else {
		if (!rx_full) {
			UART_putchar(XOFF);
			rx_full = true;
		}
	}
}

ISR(USART_UDRE_vect) {
	if (tx_head != tx_tail) {
		uart->reg_UDRx.byte = (reg8_t)tx_buffer[tx_tail++];
		if (tx_tail == TX_SIZE) {
			tx_tail = 0;
		}
	} else {
		uart->reg_UCSRxB.grouped.g_UDRIEx = (reg8_t)0x00;
	}
}

uint8_t UART_send(char const * const data, const uint8_t len, const bool_t block) {
	uint8_t sent = 0;
	while (sent != len) {
		int ret = UART_putchar(data[sent]);
		if (ret) { /* ok, inc counter and push next char */
			sent++;
		} else { /* buffer is full */
			if (!block) {
				break; /* skip rest and return */
			}
		}
	}
	return sent;
}

uint8_t UART_putchar(char c) {
	uint8_t tx_head_new = tx_head + 1;
	if(tx_head_new == TX_SIZE) {
		tx_head_new = 0;
	}
	if(tx_head_new == tx_tail) {
		return 0U;
	}
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		tx_buffer[tx_head] = c;
		tx_head = tx_head_new;
		uart->reg_UCSRxB.grouped.g_UDRIEx = (reg8_t)0x01;
	}
	return 1U;
}

uint8_t UART_busy(void) {
	return uart->reg_UCSRxB.grouped.g_UDRIEx;
}

uint8_t UART_receive(char * buf, uint8_t size) {
	uint8_t len = 0;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		while (rx_head != rx_tail && size) {
			*buf++ = rx_buffer[rx_tail];
			len++; size--;
			if(++rx_tail == RX_SIZE) {
				rx_tail = 0;
			}
		}
	}
	if(rx_full && len) {
		rx_full = false;
		UART_putchar(XON);
	}
	return len;
}

void clear_rx(void) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		rx_head = 0;
		rx_tail = 0;
	};
}


