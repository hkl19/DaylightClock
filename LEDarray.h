#ifndef _LEDarray_H
#define _LEDarray_H

#include <xc.h>

#define _XTAL_FREQ 64000000 //define oscillator to 64Mhz 

//define the functions (prototypes)
void LED_init(void); //initiation function for LED D7
void LEDarray_disp_bin(unsigned int number); //initiation function for LED array

#endif