#ifndef _LCD_H
#define _LCD_H

#include <xc.h>

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

//Define Pins Used with the LCD Screen
#define LCD_RS LATCbits.LATC6
//Pin 4 on LCD screen, or 5V on board 
#define LCD_E LATCbits.LATC2
//pin 6 on LCD screen, or RD5 on board
#define LCD_DB4 LATBbits.LATB3
//pin 11 on LCD screen, or RD6 on board
#define LCD_DB5 LATBbits.LATB2
//pin 12 on LCD screen, or RB4 on board
#define LCD_DB6 LATEbits.LATE3
//pin 13 on LCD screen, or RB5 on board
#define LCD_DB7 LATEbits.LATE1
//pin 14 on LCD screen, or RB3 on board


void LCD_E_TOG(void);
void LCD_sendnibble(unsigned char number);
void LCD_sendbyte(unsigned char Byte, char type);
void LCD_Init(void);
void LCD_setline (char line);	
void LCD_sendstring(char *string);
void LCD_scroll(void);
void LCD_clear(void);
void LCD_setlines(char cname,char ch,signed char cmin,signed char cs,signed char cd,char cm, unsigned int cy,char cBST);
void ADC2String(char *buf, unsigned int number);

#endif
