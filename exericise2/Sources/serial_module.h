#ifndef SERIALMODULE_HEADER
#define SERIALMODULE_HEADER
#include "derivative.h"


struct Serial_port{
	byte* baud_reg_high;     // SCI Baud Rate Bits High
	byte* baud_reg_low;     // SCI Baud Rate Bits Low
	byte* cont_reg_1;     // SCI Control Register 1
	byte* cont_reg_2;     // SCI Control Register 2
	byte* stat_reg_1;     // SCI Status Register 1
	byte* data_reg;     // SCI Data Register	
};

struct Serial_port use_port_0(void);

struct Serial_port use_port_1(void);



#endif
