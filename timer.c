#include <xc.h>
#include "timer.h"

void Timer0_init(void){
    T0CON1bits.T0CS=0b010; // FOSC/4
    T0CON1bits.T0ASYNC=1;// ensures the FOSC/4 clock source is of correct operation
    T0CON1bits.T0CKPS=0b1000;// 1:256, where 256 is selected for max before overflow. 
    //since we need to reach 65535beats/s for a 16 bit timer, and timer increments at 62.5ns intervals 
    //using formula, PS = 1/(65535*62.5*10^-9) = 244.14, closest binary bit no is 256. 
    //to overcome discrepancy caused by round up, error = 1/(256*62.5*10^-9) = 62500.
    //65535-62500=3035, hence in binary, error is 101111011011. TMR0H will need to be written first. 
    T0CON0bits.T016BIT=1; //1 means 16 bit mode of timer is active 
    TMR0H=3035>>8;  //write high reg, which takes the 4 most sig bits.
    TMR0L=3035&0b11111111; //write low reg, which takes 8 lower bits.
    T0CON0bits.T0EN=1; // start the timer !!!! 
        
         
}

unsigned int get16bitTMR0val(void){
    unsigned char a = TMR0L; // always read value from TMR0L first
    unsigned char b = TMR0H; // contains a copy of 8 most sig bits from TMR0L
    return b; 
}