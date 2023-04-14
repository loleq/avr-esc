/*
 * uart.h
 *
 *  Created on: 5 kwi 2023
 *      Author: pierba1
 */

#ifndef _UART_H_
#define _UART_H_

#include "common.h"
#include "stdio.h"

#define UART_REGS_START_ADDR (0xC0)

typedef struct uart_registers {
	union {
		reg8_t byte;
		reg8_bits_t bits;
		struct {
			reg8_t g_MPCMx : 1;
			reg8_t g_U2Xx  : 1;
			reg8_t g_UPEx  : 1;
			reg8_t g_DORx  : 1;
			reg8_t g_FEx   : 1;
			reg8_t g_UDREx : 1;
			reg8_t g_TXCx  : 1;
			reg8_t g_RXCx  : 1;
		} grouped;
	} reg_UCSRxA;
	union {
		reg8_t byte;
		reg8_bits_t bits;
		struct {
			reg8_t g_TXB8x   : 1;
			reg8_t g_RXB8x   : 1;
			reg8_t g_UCSZxb2 : 1;
			reg8_t g_TXENx   : 1;
			reg8_t g_RXENx   : 1;
			reg8_t g_UDRIEx  : 1;
			reg8_t g_TXCIEx  : 1;
			reg8_t g_RXCIEx  : 1;
		} grouped;
	} reg_UCSRxB;
	union {
		reg8_t byte;
		reg8_bits_t bits;
		struct {
			reg8_t g_UCPOLx   : 1;
			reg8_t g_UCSZxb01 : 2;
			reg8_t g_USBSx    : 1;
			reg8_t g_UPMx     : 2;
			reg8_t g_UMSELx   : 2;
		} grouped;
	} reg_UCSRxC;
	reg8_t reserved;
	union {
			reg8_t byte;
			reg8_bits_t bits;
	} reg_UBRRxL;
	union {
		reg8_t byte;
		reg8_bits_t bits;
		struct {
			reg8_t g_UBRRxH : 4;
			reg8_t g_unused : 4;
		} grouped;
	} reg_UBRRxH;
	union {
		reg8_t byte;
		reg8_bits_t bits;
	} reg_UDRx;
} uart_registers_t;


#define USART_BAUDRATE 9600
//#define USART_BAUDRATE 115200UL
//#define USART_BAUDRATE 250000UL
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define UMSEL_ASYNC 0x00
#define UMSEL_SYNC 0x01
#define UMSEL_MSPIM 0x03

#define UPM_DISABLED 0x00
#define UPM_EVEN 0x02
#define UPM_ODD 0x03

#define USBS_1 0x00
#define USBS_2 0x01

#define UCSZ_5 0x0
#define UCSZ_6 0x1
#define UCSZ_7 0x2
#define UCSZ_8 0x3
#define UCSZ_9 0x7

extern void UART_init(void);
extern uint8_t UART_send(char const * const data, const uint8_t len, const bool_t block);
extern uint8_t UART_busy(void);
extern uint8_t UART_receive(char * buf, uint8_t size);
extern uint8_t UART_putchar(char c);
extern uint8_t _UART_send_P(const char * const pm_addr, const bool_t block);

#define UART_send_P(msg_p) do { \
	extern const char msg_p[] __attribute__((__progmem__)); \
	_UART_send_P(msg_p, true); \
} while(0)


#endif /* _UART_H_ */
