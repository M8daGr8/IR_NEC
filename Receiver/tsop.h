#ifndef TSOP_H_
#define TSOP_H_

#include <avr/io.h>

void tsop_init(void);

uint8_t tsop_read(void);

#endif