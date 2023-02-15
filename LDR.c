//LDR is the input that dictates if RH3 is on or off
//We can assume dawn and dusk having the same amount of sunlight (set a value)
//If we average the two times, we could get the midpoint (noon time)

//setup of LDR 
#include <xc.h>
#include "LDR.h"

//initialising the LDR 
void LDR_init(void){
    TRISAbits.TRISA3=1; //Here, selected A3 pin as my input
    ANSELAbits.ANSELA3=1; //Ensuring Analogue circuitry active for A3 pin
    
    //Setup of ADC module#
    ADREFbits.ADNREF = 0;//set lower Volt ref to ground
    ADREFbits.ADPREF = 0b00;//set higher Volt ref to 3.3V
    ADPCH = 0b11 ; //Selected channel ANA3 for ADC 
    ADCON0bits.ADFM = 0; //Left justified result (no leading 0s)
    ADCON0bits.ADCS = 1; //Use internal fast RC (FRC) as clock source
    ADCON0bits.ADON = 1; // this enables the ADC
}

unsigned int LDR_val(void){
    unsigned int temp;
    ADCON0bits.GO= 1; //start ADC conversion 
    
    while (ADCON0bits.GO); //wait until conversion is finished
    // do we need the full bits? 
    //say we get the most sig 8 bit number : 
    temp = ADRESH; // returns 8 most sig bit of results , min is 0 max is 255 or 11111111
    // the LDR gives a greater voltage if its darker. 0(bright)->255(darkest)
    return temp ;
}

void LDR_thres(unsigned char val,unsigned char hour){
    unsigned int thres = 150; // set threshold somewhere in middle-> 150 or 10010110
    if (hour>=1 && hour<=5) { //if between 1-5am, make sure lED is off
            LATDbits.LATD7 = 0;
        }
    else if (val<thres) { //if its daytime (brighter than threshold)
            LATDbits.LATD7 = 0; //turn the light off
        }
    else if (val>thres) {//if its night (darker than threshold)
            LATDbits.LATD7 = 1; //turn light on
        }
}