#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>

void timer1_init(void);

uint8_t timer1_passed(void);
void timer1_reset(void);

#endif
