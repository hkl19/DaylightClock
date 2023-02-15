#include <xc.h>
#include "LEDarray.h"

void LED_init(void){
    //initialise tris registers output (0)
    TRISDbits.TRISD7 = 0;  // for LED in practice 
    
    TRISAbits.TRISA5 = 0;  // timer pin 2 for calender
    TRISHbits.TRISH3 = 0;  // timer pin 1 for second interrupt
    TRISGbits.TRISG0 = 0;  // for LED ARRAY bit 1
    TRISGbits.TRISG1 = 0;  // for LED ARRAY bit 2
    TRISAbits.TRISA2 = 0;  // for LED ARRAY bit 3
    TRISFbits.TRISF6 = 0;  // for LED ARRAY bit 4
    TRISAbits.TRISA4 = 0;  // for LED ARRAY bit 5
    
    //initialise the LED lat initial output 
    LATDbits.LATD7 = 0; // 0V for initial output, left LED
    LATHbits.LATH3 = 0; // initiate timer pin 1 for second interrupt
    LATAbits.LATA5 = 0; // initiate timer pin 2 for calender 
    LATGbits.LATG0 = 0; // initial input of LED array bit 1 
    LATGbits.LATG1 = 0; // initial input of LED array bit 2
    LATAbits.LATA2 = 0; // initial input of LED array bit 3
    LATFbits.LATF6 = 0; // initial input of LED array bit 4
    LATAbits.LATA4 = 0; // initial input of LED array bit 5
}

void LEDarray_disp_bin(unsigned int number){
    //code that dictates the clock (array) to keep track of time of day
    //Use if statements and bit masks 
    //For 24 hours, we need a total of 5 bits (32)
    //compare the binary number of (hour count), if AND statement true, light up that LED
    if (number & 0b00001) {LATGbits.LATG0=1;} else {LATGbits.LATG0=0;} 
    if (number & 0b00010) {LATGbits.LATG1=1;} else {LATGbits.LATG1=0;}
    if (number & 0b00100) {LATAbits.LATA2=1;} else {LATAbits.LATA2=0;}
    if (number & 0b01000) {LATFbits.LATF6=1;} else {LATFbits.LATF6=0;}
    if (number & 0b10000) {LATAbits.LATA4=1;} else {LATAbits.LATA4=0;}
    
}


