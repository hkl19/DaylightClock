#ifndef _timers_H
#define _timers_H

#include <xc.h>
#define _XTAL_FREQ 64000000 //Oscillator of 64 Mhz chosen

void Timer0_init(void); //initiation function for timer 0 
unsigned int get16bitTMR0val (void); //function of retrieving the timer value

#endif 