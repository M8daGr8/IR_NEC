#include "timer.h"

void timer1_reset(void){
	TIFR1 |= (1 << OCF1A);
}

uint8_t timer1_passed(void){
	if(TIFR1 & (1 << OCF1A)){
		timer1_reset();
		return 1;
	}
	return 0;
}


/*
	NEC CYCLE = 562.5
			
	Compare Value = (t / (1 / fclk_IO)) / N
	
	t = 562.5 uS = (562.5 * 10^-6) S
	1125 = (0.0005625 / (1 / (16 * 10^6))) / 8
	1125 = 0x465
*/
void timer1_init(void){
	// CTC mode
	TCCR1B |= (1 << WGM12);
	
	// 8 prescale
	TCCR1B |= (1 << CS11);
	
	// 562.5 uS @ 8 prescale
	OCR1A = 0x465;
}