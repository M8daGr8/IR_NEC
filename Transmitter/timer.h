#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#include "nec.h"

/*
	fclk_IO / (2 * N * fPWM) = OCR0A
	
	(16 * 10^6) / (2 * 8 * (30 * 10^3)) - 1 =  32 = 0x20	(30kHz)
	(16 * 10^6) / (2 * 1 * (36 * 10^3)) - 1 = 221 = 0xDD	(36kHz)
	(16 * 10^6) / (2 * 1 * (38 * 10^3)) - 1 = 209 = 0xD1	(38kHz)
	(16 * 10^6) / (2 * 1 * (40 * 10^3)) - 1 = 199 = 0xC7	(40kHz)
	(16 * 10^6) / (2 * 1 * (56 * 10^3)) - 1 = 142 = 0x8E	(56kHz)
*/

typedef enum {
	kHz30 = 0x20,
	kHz36 = 0xDD,
	kHz38 = 0xD1,
	kHz40 = 0xC7,
	kHz56 = 0x8E
}Frequency;

void timers_init(Frequency fPwm);

#endif
