/*
 * esc.c
 *
 *  Created on: 25 mar 2023
 *      Author: bpierzy
 */

#include "common.h"
#include "esc.h"



void esc_init(void) {
	init_drivers_pins();
	init_timers();
}


void init_drivers_pins(void) {
	pin_t b0 = PIN_B0;
	pin_set_high(b0);
	pin_set_high(PIN_B2);
//	pin_set_high(PIN_C1);
//	pin_set_high(PIN_B3);

//	/* Na początku wyłączam wszystkie drivery, żeby nie zrobić zwarcia na mostku */
//	/* Ustaw kierunek pinów na OUT */
//	ESC_DDR_SD |=   _BV(ESC_PIN_PHASE_A_SD)
//	           | _BV(ESC_PIN_PHASE_B_SD)
//               | _BV(ESC_PIN_PHASE_C_SD);
//
//	/* Ustaw stan niski = zwarcie do GND */
//	/* W tym momencie drivery powinny być wyłączone */
//	ESC_PORT_SD &= ~(_BV(ESC_PIN_PHASE_A_SD)
//			       | _BV(ESC_PIN_PHASE_B_SD)
//			       | _BV(ESC_PIN_PHASE_C_SD));
//
//	/* Podobnie konfiguruje piny odpowiedzialne za sterowanie High/Low side */
//
//	ESC_DDR_IN |=   _BV(ESC_PIN_PHASE_A_IN)
//		           | _BV(ESC_PIN_PHASE_B_IN)
//	               | _BV(ESC_PIN_PHASE_C_IN);
//
//		/* Ustaw stan niski = zwarcie do GND */
//		/* W tym momencie drivery powinny być wyłączone */
//		ESC_PORT_IN &= ~(_BV(ESC_PIN_PHASE_A_IN)
//				       | _BV(ESC_PIN_PHASE_B_IN)
//				       | _BV(ESC_PIN_PHASE_C_IN));
}


void init_timers(void) {
	/* Potrzebujemy 3 sygnały PWM, użyjemy do tego kanały A i B timera 1 i kanał A timera 2 */
	/* Timer 1 */



}

