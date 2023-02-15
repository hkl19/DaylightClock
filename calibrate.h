#ifndef calibrate_H
#define calibrate_H

#include <xc.h>
#define _XTAL_FREQ 64000000

unsigned int calibrate_sec(unsigned int sec, unsigned char s_noon, unsigned int tol);
unsigned char calibrate_hour(unsigned char hour, unsigned char s_noon);

#endif