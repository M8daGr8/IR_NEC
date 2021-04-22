#include "serial.h"
#include "led.h"
#include "timer.h"
#include "nec.h"

int main (void) {
	uart_init();
	led_init();
	timers_init(kHz36);

	printf("Transmitter\n");
	//printf("[ADR]\t[DATA]\t[  ADR   ]\t[  ~ADR  ]\t[  DATA  ]\t[ ~DATA  ]\n");
	printf("[ADR]: 0x%x\n[DATA]\n", TRANSMITTERADDRESS);
	
	sei();
		
	for(;;){
		volatile uint8_t *byte = uart_getbyteptr();
		if(*byte != '\0')
			set_data(byte);
	}
	
	return 1337;
}
