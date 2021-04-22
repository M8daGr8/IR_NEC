#ifndef SERIAL_H_
#define SERIAL_H_

#define F_CPU			16000000UL
#define BAUD			38400UL
#define UBRR			(F_CPU / (BAUD * 16UL)) - 1

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

ISR(USART_RX_vect);

void uart_init(void);

volatile uint8_t *uart_getbyteptr(void);

void uart_putchar(uint8_t data, FILE *stream);

#endif

