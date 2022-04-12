#include "serial_module.h"

// include the register/pin definitions
#include "derivative.h"
  	

struct Serial_port use_port_0(void){
  struct Serial_port port_0;
  
  port_0.baud_reg_high  = &SCI0BDH;     // SCI Baud Rate Bits High
  port_0.baud_reg_low   = &SCI0BDL;     // SCI Baud Rate Bits Low
  port_0.cont_reg_1     = &SCI0CR1;     // SCI Control Register 1
  port_0.cont_reg_2     = &SCI0CR2;     // SCI Control Register 2
  port_0.stat_reg_1     = &SCI0SR1;     // SCI Status Register 1
  port_0.data_reg       = &SCI0DRL;     // SCI Data Register

  return port_0;
}

struct Serial_port use_port_1(void){
  struct Serial_port port_1;
  
  port_1.baud_reg_high  = &SCI1BDH;     // SCI Baud Rate Bits High
  port_1.baud_reg_low   = &SCI1BDL;     // SCI Baud Rate Bits Low
  port_1.cont_reg_1     = &SCI1CR1;     // SCI Control Register 1
  port_1.cont_reg_2     = &SCI1CR2;     // SCI Control Register 2
  port_1.stat_reg_1     = &SCI1SR1;     // SCI Status Register 1
  port_1.data_reg       = &SCI1DRL;     // SCI Data Register

  return port_1;
}