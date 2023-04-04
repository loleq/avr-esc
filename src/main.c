/*
 * main.c
 *
 *  Created on: 25 mar 2023
 *      Author: bpierzy
 */

#include "esc.h"

void init(void) {
	ESC_init();
}

int main(void) {

	init();

	return 0;
}
