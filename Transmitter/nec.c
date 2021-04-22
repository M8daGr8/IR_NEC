#include "nec.h"

volatile CurrentTransmit currentTransmit = { START, 0, 0 };

void transmit_data(void){
	if(!currentTransmit.transmitting)
		return;
	
	if(currentTransmit.status == START || currentTransmit.status == STOP){
		if(currentTransmit.bit)
			led_on();
		else
			led_off();
		currentTransmit.transmitting = 0;
	}
	else{
		static uint8_t cycle = 0;
		
		led_transmit(cycle);
		if(currentTransmit.bit ? (cycle == 3) : (cycle == 1)){
			currentTransmit.transmitting = 0;
			cycle = 0;
			return;
		}
		cycle++;
	}
}

uint8_t set_start(void){
	static uint8_t cycle = 0;
	static uint8_t firstPulse = 1;
	
	cycle++;
	if(firstPulse){
		currentTransmit.bit = 1;
		if(cycle == STARTMULTIPLIER){
			firstPulse = 0;
			cycle = 0;
		}
	}
	else{
		currentTransmit.bit = 0;
		if(cycle == STARTMULTIPLIER / 2){
			firstPulse = 1;
			cycle = 0;
			return 1;
		}
	}
	return 0;
}

uint8_t set_stop(void){
	static uint8_t cycle = 0;
	if(cycle++ == 0)
		currentTransmit.bit = 1;
	else{
		currentTransmit.bit = 0;
		cycle = 0;
		return 1;
	}
	return 0;
}

uint8_t set_bit_msb(uint8_t byte, volatile CurrentTransmit *currentTransmit, uint8_t inverted){
	static int8_t bit = BYTESIZE;
	
	currentTransmit->bit = (byte & (1 << --bit)) > 0;
	if(inverted)
	currentTransmit->bit = !currentTransmit->bit;
	
	if (bit == 0){
		bit = BYTESIZE;
		return 1;
	}
	return 0;
}

uint8_t set_bit_lsb(uint8_t byte, volatile CurrentTransmit *currentTransmit, uint8_t inverted){
	static int8_t bit = 0;
	
	currentTransmit->bit = (byte & (1 << bit++)) > 0;
	if(inverted)
	currentTransmit->bit = !currentTransmit->bit;
	
	if (bit == BYTESIZE){
		bit = 0;
		return 1;
	}
	return 0;
}

void set_data(volatile uint8_t *data){
	if(currentTransmit.transmitting)
		return;
		
	static Status status = START;
	if(status == START){
		currentTransmit.status = START;
		if(set_start()){
			status = ADDRESS;
			//printf("[0x%x]\t[%c]\t[", TRANSMITTERADDRESS, *data);
		}
	}
	else if(status == ADDRESS){
		currentTransmit.status = ADDRESS;
		static uint8_t inverted = 0;
		if(set_bit_lsb(TRANSMITTERADDRESS, &currentTransmit, inverted)){
			if(inverted){
				status = DATA;
			}
			//printf("%d]\t[", currentTransmit.bit);
			inverted = !inverted;
		}
		//else
			//printf("%d", currentTransmit.bit);
	}
	else if(status == DATA){
		currentTransmit.status = DATA;
		static uint8_t inverted = 0;
		if(set_bit_lsb(*data, &currentTransmit, inverted)){
			if(inverted){
				status = STOP;
				//printf("%d]\n", currentTransmit.bit);
			}
			//else
				//printf("%d]\t[", currentTransmit.bit);
			inverted = !inverted;
		}
		//else
			//printf("%d", currentTransmit.bit);
	}
	else if(status == STOP){
		currentTransmit.status = STOP;
		if(set_stop()){
			printf("%c\n", *data);
			*data = '\0';
			status = START;
		}
	}
	currentTransmit.transmitting = 1;
}