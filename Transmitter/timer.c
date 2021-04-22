#include "timer.h"

// Frequency generator
void timer0_init(Frequency fPwm) {
	// CTC mode
	TCCR0A |= (1 << WGM01);

	if(fPwm == kHz30)
		// 8 prescale
		TCCR0B |= (1 << CS01);
	else
		// 1 prescale
		TCCR0B |= (1 << CS00);
	
	// 36KHz
	OCR0A = fPwm;
}

ISR(TIMER1_COMPA_vect){
	transmit_data();
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
	
	//  Output Compare A Match Interrupt Enable
	TIMSK1 |= (1 << OCIE1A);
}

void timers_init(Frequency fPwm){
	timer0_init(fPwm);
	timer1_init();
}