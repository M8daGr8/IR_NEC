#ifndef LED_H_
#define LED_H_

#include <avr/io.h>

void led_init(void);

void led_off(void);
void led_on(void);
void led_transmit(uint8_t value);

#endif