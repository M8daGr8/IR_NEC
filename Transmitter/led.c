#include "led.h"

//Set Port D pin 5 to Output
void led_init(void) {
	DDRD |= (1 << DDD5);
	PORTD |= (1 << PORTD5);
}

//START pwm output port D OC0B (DDD5)
void led_on(void){
	TCCR0A |= (1 << COM0B0);
}

//STOP pwm output port D OC0B (PORTD5)
void led_off(void){
	TCCR0A &= ~(1 << COM0B0);
	PORTD |= (1 << PORTD5);
}

void led_transmit(uint8_t value){
	if(!value)
		led_on();
	else
		led_off();
}