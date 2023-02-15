#include <xc.h>
#include "interrupts.h"
#include "LEDarray.h"
#include "current_hour.h"
#include "calender.h"

/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/
void Interrupts_init(void)
{
	// turn on global interrupts, peripheral interrupts and the interrupt source 
    INTCONbits.PEIE=1; // enable peripheral inputs
    PIE0bits.TMR0IE=1; // enable peripheral input regis 0, so timer interrupt is enabled
    PIR0bits.TMR0IF=0; // enable peripheral input regis 0, interrupt flag on 
    INTCONbits.GIE=1;  // turn on global interupts (GIE)
	// It's a good idea to turn on global interrupts last, once all other interrupt configuration is done.
}

/************************************
 * High priority interrupt service routine
 * Make sure all enabled interrupts are checked and flags cleared
************************************/
void __interrupt(high_priority) HighISR()
{
	//add your ISR code here i.e. check the flag, do something (i.e. toggle an LED), clear the flag...
    if(PIR0bits.TMR0IF){ // interrupt flag triggered
        //Change state of the two pins used for timer interrupts 
        LATHbits.LATH3=!LATHbits.LATH3; //changes the state of the H3 pin 
        PIR0bits.TMR0IF=0;
    }
//reset interrupt (clear the flag)
    
} 

