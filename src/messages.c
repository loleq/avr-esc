/*
 * strings.c
 *
 *  Created on: 12 kwi 2023
 *      Author: pierba1
 */

//#include <avr/pgmspace.h>

const char str_step0[] __attribute__((__progmem__))  = "step 0\r\n"; /* len = 8 */
const char str_step1[] __attribute__((__progmem__))  = "step 1\r\n";
const char str_step2[] __attribute__((__progmem__))  = "step 2\r\n";
const char str_step3[] __attribute__((__progmem__))  = "step 3\r\n";
const char str_step4[] __attribute__((__progmem__))  = "step 4\r\n";
const char str_step5[] __attribute__((__progmem__))  = "step 5\r\n";
const char str_power[] __attribute__((__progmem__))  = "ACK new power\r\n"; /* len = 15*/
const char str_crlf [] __attribute__((__progmem__))  = "\r\n"; /* len = 2 */
const char str_chreq[] __attribute__((__progmem__))  = "ACK change request: "; /* len = 20*/

const char str_cold_start_init[] __attribute__((__progmem__))  = "Cold start init\r\n";
const char str_cold_start[] __attribute__((__progmem__))  = "Cold start\r\n";

const char str_last_state[] __attribute__((__progmem__)) = "Last state: ";
