
#ifndef calender_H
#define	calender_H

#include <xc.h>
#define _XTAL_FREQ 64000000

char calender_count(char name,char h,signed char min,signed char s,signed char d,char m, unsigned int y,char BST);
void daylight_save(char BST,char s,char h);
#endif