#ifndef NEC_H_
#define NEC_H_

#include <stdio.h>

#include "tsop.h"
#include "timer.h"

#define BYTESIZE 8
#define STARTMULTIPLIER 16
#define LOGICONEMULTIPLIER 3

typedef struct{
	uint8_t address;
	uint8_t addressinv;
	uint8_t data;
	uint8_t datainv;
}Message;

typedef enum{
	START	= 0,
	ADDRESS = 2,
	DATA	= 1,
	STOP	= 3
}Status;

uint8_t receive_data(Message *message);
int8_t check_byte(uint8_t byte, uint8_t inv);

void clear_msg(uint8_t *msg);
void print_msg(const uint8_t *msg);
void add_msg(uint8_t* msg, const uint8_t chr, const uint8_t size);

#endif