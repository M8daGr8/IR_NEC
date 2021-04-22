#include "tsop.h"
#include "timer.h"
#include "serial.h"
#include "nec.h"

#define MSG_SIZE 30

int main (void) {
	uart_init();
	tsop_init();
	timer1_init();
	
	printf("\nReceiver\n");
	printf("[ADR]\t[~ADR]\t[?ADR]\t\t[DATA]\t[~DATA]\t[?DATA]\t\t[CHAR]\n");
	
	Message message = { 0, 0, 0, 0}; 
	
	uint8_t msg[MSG_SIZE] = { 0 };
		
	for(;;){
		uint8_t newData = receive_data(&message);
		if(newData){
			int8_t addressError = check_byte(message.address, message.addressinv);
			int8_t dataError = check_byte(message.data, message.datainv);
			
			printf("[0x%x]\t[0x%x]\t[%d]\t\t[0x%x]\t[0x%x]\t[%d]\t\t[%c]\n", message.address, message.addressinv, addressError, message.data, message.datainv, dataError, message.data);
			if(message.data == 0xd) { // CR
				print_msg(&msg[0]);
				clear_msg(&msg[0]);
			}
			else if(dataError == -1)
				add_msg(&msg[0], message.data, MSG_SIZE);
		}
	}
	return 1337;
}