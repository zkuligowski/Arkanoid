#include "utilities.h"



unsigned long __stack_chk_guard;
void __stack_chk_guard_setup(void) {     __stack_chk_guard = 0xBAAAAAAD;}
void __stack_chk_fail(void){ }

unsigned long randi = 334324324;
unsigned long randr(unsigned long range) {
	randi = randi * 1103515245UL + 12345;
	return randi % range;
}

