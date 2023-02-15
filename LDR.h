//LDR is a ADC, this file encompases the functions in LDR.C 

#ifndef _ADC_H
#define _ADC_H

#include <xc.h>
#define _XTAL_FREQ 64000000 //oscillator of 64MHz assigned

void LDR_init(void);
unsigned int LDR_val(void); 
void LDR_thres(unsigned char val,unsigned char hour);

#endif 