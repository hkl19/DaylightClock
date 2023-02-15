#ifndef current_hour_H
#define current_hour_H

//This code will be a integer function, which returns and integer, to be inputted 
//Into the LED_disp_bin(). Which would indefinitely tell the time on the LED array
//Based upon the LDR reading as well. 

#include <xc.h>
#define _XTAL_FREQ 64000000 //oscillator of 64Mhz assigned

int what_hour(int current_hour, int count, int max_count);

#endif

