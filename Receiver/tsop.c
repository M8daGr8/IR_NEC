#include "tsop.h"


void tsop_init(void){
	DDRD &= ~(1 << DDD2);
}

uint8_t tsop_read(void){
	if(PIND & (1 << PIND2))
		return 1;
	return 0;
}
