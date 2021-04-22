#ifndef NEC_H_
#define NEC_H_

#include <stdio.h>

#include "led.h"

#define TRANSMITTERADDRESS 0xFF
#define BYTESIZE 8

#define STARTMULTIPLIER 16

typedef enum{
	START	= 0,
	ADDRESS	= 1,
	DATA	= 2,
	STOP	= 3
}Status;

typedef struct{
	Status status;
	uint8_t bit;
	uint8_t transmitting;
}CurrentTransmit;

void set_data(volatile uint8_t *data);
void transmit_data(void);

#endif