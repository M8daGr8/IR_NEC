#include "serial.h"

static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

volatile uint8_t byte = '\0';

ISR(USART_RX_vect){
	if(byte == '\0')
		byte = UDR0;
}

volatile uint8_t *uart_getbyteptr(void){
	return &byte;
}

void uart_init(void) {
	UBRR0H = (UBRR >> 8);
	UBRR0L = (UBRR);
	
	UCSR0A = 0;
	
	UCSR0B = ((1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0));
	UCSR0C = (1 << UCSZ01 | 1 << UCSZ00);

	stdout = &uart_stdout;
}

void uart_putchar(uint8_t data, FILE *stream) {
	if (data == '\n')
		uart_putchar('\r', NULL);

	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

