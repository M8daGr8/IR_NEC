#include "nec.h"

int8_t receive(uint8_t activeState, uint8_t cycles){
	if(tsop_read() != activeState)
		return -1;
	timer1_reset();
	
	uint8_t cycle = 0;
	while(1){
		if(timer1_passed())
			cycle++;
		
		if(tsop_read() != activeState || cycle > cycles)
			break;	
	}
	return cycle;
}

uint8_t receive_start(void){
	static uint8_t pulse = 0;
	uint8_t cycles = (!pulse) ? STARTMULTIPLIER : (STARTMULTIPLIER / 2);
	
	uint8_t res = (receive(pulse, cycles) == cycles);
	if(res){
		pulse = !pulse;
		if(!pulse)
			return 1;
	}
	else{
		pulse = 0;
	}
	return 0;
}

int8_t receive_bit(void){
	static uint8_t pulse = 0;
	
	int8_t cycles = receive(pulse, LOGICONEMULTIPLIER);
	
	if(cycles)
		pulse = !pulse;
	
	if(!pulse)
		return (cycles == 3);
	return -1;
}

int8_t receive_byte_msb(uint8_t *byte){
	int8_t bit = receive_bit();
	
	if(bit == -1)
		return -1;
		
	static uint8_t currentBit = 0;
	
	if(bit)
		*byte |= (1 << currentBit++);
	else
		*byte &= ~(1 << currentBit++);
	
	if(currentBit == BYTESIZE){
		currentBit = 0;
		return 1;
	}
	return 0;
}

int8_t receive_byte_lsb(uint8_t *byte){
	int8_t bit = receive_bit();
	
	if(bit == -1)
		return -1;
	
	static uint8_t currentBit = BYTESIZE;
	
	if(bit)
		*byte |= (1 << --currentBit);
	else
		*byte &= ~(1 << --currentBit);
		
	if(!currentBit){
		currentBit = BYTESIZE;
		return 1;
	}
	return 0;
}

uint8_t receive_stop(void){
	return (receive(0, 1) == 1);
}

uint8_t receive_data(Message *message){
	static Status status = START;
		
	if(status == START){
		if(receive_start())
			status = ADDRESS;
	}
	else if(status == ADDRESS){
		static uint8_t inverted = 0;
		
		if(!inverted){
			if(receive_byte_msb(&message->address) == 1)
				inverted = !inverted;
		}
		else{
			if(receive_byte_msb(&message->addressinv) == 1){
				inverted = !inverted;
				status = DATA;	
			}
		}
	}
	else if(status == DATA){
		static uint8_t inverted = 0;
		
		if(!inverted){
			if(receive_byte_msb(&message->data) == 1)
				inverted = !inverted;
		}
		else{
			if(receive_byte_msb(&message->datainv) == 1){
				inverted = !inverted;
				status = STOP;	
			}
		}
	}
	else if(status == STOP){
		if(receive_stop()){
			status = START;
			return 1;
		}
	}
	return 0;
}

int8_t check_byte(uint8_t byte, uint8_t inv){
	for(uint8_t bit = 0; bit < BYTESIZE; bit++){
		if((byte & (1 << bit)) == (inv & (1 << bit)))
			return bit;
	}
	return -1;
}

void print_msg(const uint8_t* msg) {
	for (; *msg != 0; msg++)
		printf("%c", *msg);
	printf("\n");
}


void add_msg(uint8_t* msg, const uint8_t chr, const uint8_t size){
	for (uint8_t i = 0; *msg != 0; msg++, i++)
		if (i >= size - 2)
			return;
	*msg = chr;
}

void clear_msg(uint8_t *msg){
	while(*msg)
		*(msg++) = 0;
}
