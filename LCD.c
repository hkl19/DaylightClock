#include <xc.h>
#include <stdio.h>
#include "LCD.h"
#include "LDR.h"
/************************************
 * Function to toggle LCD enable bit on then off
 * when this function is called the LCD screen reads the data lines
************************************/
void LCD_E_TOG(void)
{
	//turn the LCD enable bit on
    LCD_E=1;//
	__delay_us(8); //wait a short delay
	//turn the LCD enable bit off again
    LCD_E=0;
    __delay_us(5);      //Delay 5uS
}
/************************************
 * Function to set the 4-bit data line levels for the LCD
************************************/
void LCD_sendnibble(unsigned char number)
{
	//set the data lines here (think back to LED array output)
    //if AND is true, 1 is shown on data line for that given bus
    if (number & 0b0001) {LCD_DB4 =1;} else {LCD_DB4=0;}
    if (number & 0b0010) {LCD_DB5 =1;} else {LCD_DB5=0;}
    if (number & 0b0100) {LCD_DB6 = 1;} else {LCD_DB6=0;}
    if (number & 0b1000) {LCD_DB7 = 1;} else {LCD_DB7=0;}
    
    LCD_E_TOG();			//toggle the enable bit to instruct the LCD to read the data lines
    __delay_us(5);      //Delay 5uS
}
/************************************
 * Function to send full 8-bit commands/data over the 4-bit interface
 * high nibble (4 most significant bits) are sent first, then low nibble sent
 *unsigned char 1 byte, 0 to 255
 *char 1 byte, -128 to 127 or 0 to 255
************************************/
void LCD_sendbyte(unsigned char Byte, char type)
{
    // set RS pin whether it is a Command (0) or Data/Char (1) using type argument
    LCD_RS = type;
    // send high bits of Byte using LCDout function-- LCD_sendnibble is used instead
    unsigned char HB = Byte & 0b11110000;  
    LCD_sendnibble (HB>>4);
    // send low bits of Byte using LCDout function-- LCD_sendnibble is used instead
    unsigned char LB = Byte & 0b00001111;
    LCD_sendnibble(LB);	
    __delay_us(50);               //delay 50uS (minimum for command to execute)
}
//
/************************************
 * Function to initialise the LCD after power on
************************************/
void LCD_Init(void)
{
    TRISBbits.TRISB3= 0; //Assign LCD_DB4 as output 
    TRISBbits.TRISB2= 0; //Assign LCD_DB5 as output 
    TRISEbits.TRISE3= 0; //Assign LCD_DB6 as output 
    TRISEbits.TRISE1= 0; //Assign LCD_DB7 as output
    TRISCbits.TRISC6= 0; //Assign LCD_RS as output
    TRISCbits.TRISC2= 0; //Assign LCD_E as output
    
    //set all pins low (might be random values on start up, fixes lots of issues)
    LATBbits.LATB3=0; //Assign LCD_DB4 as low 0V
    LATBbits.LATB2=0; //Assign LCD_DB5 as low 0V
    LATEbits.LATE3=0; //Assign LCD_DB6 as low 0V
    LATEbits.LATE1=0; //Assign LCD_DB7 as low 0V
    LATCbits.LATC6=0; //Assign LCD_RS as low 0V
    LATCbits.LATC2=0; //Assign LCD_E as low 0V
    //Define LCD Pins as Outputs and
    //set all pins low (might be random values on start up, fixes lots of issues)
    //Initialisation sequence code
    __delay_us(40); // wait for Vdd to rise to 4.5V
    LCD_sendnibble(0b0011); //use send nibble to carry out function set 1
    __delay_us(40) ;//wait for at least 39 micro s
    //LCD_sendbyte(0b01101100,0); // DB7->DB0 defined by 8bit number here
    LCD_sendbyte(0b00101000,0);
    // 3rd 1 is DB5, always 1 on function set, 4th 0 defines DB4 (ie DL is set to 4bit instead of 8)
    // 4th 0 is DB4, dictates display line DL (8bit or 4 bit) 0 means 8 bits
    // if this is 1, a 0 is shown on the screen? 
    // 5th 1 is DB3, dictates numbers of display line (1 means 2-line instead of 1-line);
    // 6th 1 is DB2, dictates font type (here we chose 5x11dots instead of 5x8dots); 
    __delay_us(40) ;// wait for 39 micro s
    //LCD_sendbyte(0b01101100,0) ;//same function line as before
    LCD_sendbyte(0b00101000,0);
    __delay_us(40);
    //LCD_sendbyte(0b00001111,0) ; //function for display ON/OFF control
    LCD_sendbyte(0b00000001,0);
    // first 1 is DB3, necessary for the function
    // 2nd 1 is DB2, dictates display on/off bit
    // 3rd 1 is DB1, dictates cursor on/off bit
    // 4th 1 is DB0, dictates blinking cursor, on/off bit
    __delay_us(40); // require delay of 37 micro s
    //LCD_sendbyte(0b00000001,0) ; //Display clear function as per table
    LCD_sendbyte(0b00000110,0);
    // last 1 in DB0 compulsory for function 
    __delay_ms(2); // follow this with 1.53ms delay
    //LCD_sendbyte(0b00000100,0) ;//Entry mode set function
    LCD_sendbyte(0b00001110,0);
    // 1 is necessary in DB2 to call function
    // 0/1 in DB1 dictates cursor moving direction 
    // 0/1 in DB0 enables or disables shift of entire display
    __delay_ms(2);
}
/************************************
 * Function to set the cursor to beginning of line 1 or 2
************************************/
void LCD_setline (char line)
{
    //Send 0x80(128)to set line to 1 (0x00(0) ddram address)
    if (line==1){
       LCD_sendbyte(0x80,0);}
    //Send 0xC0(192) to set line to 2 (0x40(64) ddram address)
    if (line==2){
        LCD_sendbyte(0xC0,0);}
}
/************************************
 * Function to send string to LCD screen
************************************/
void LCD_sendstring(char *string)
{	  
	while(*string != 0){  // While the data pointed to isn?t a 0x00 do below (strings in C must end with a NULL byte) 
		LCD_sendbyte(*string++,1); 	//Send out the current byte pointed to and increment the pointer
	}
}
/************************************
 * Function to send string to LCD screen
************************************/
void LCD_scroll(void)
{
	//code here to scroll the text on the LCD screen
    LCD_sendbyte(0b00011000,0); // Based on data booklet, 5th is Set cursor/display shift, 6th is Right/Left
    __delay_ms(500); // delay to make writing visible to human eye
}
/************************************
 * Function takes a ADC value and works out the voltage to 2 dp
 * the result is stored in buf as ascii text ready for display on LCD
 * Note result is stored in a buffer using pointers, it is not sent to the LCD
************************************/
void ADC2String(char *buf, unsigned int ADC_val){
	//code to calculate the integer and fractions part of a ADC value
	// and format as a string using sprintf (see GitHub readme)
    //first we need to assign the variables for int and frac
    unsigned int int_part ;// integer part of the ADC value
    unsigned int frac_part ;// fractional part of the ADC value
    unsigned int x =  850/11;//x = 850/11 can be manipulated based on what voltage we are working on.
    //since our max bit is 8, which is 255, 255/(ADC max voltage) = x.
    // since maximum ADC is 3.3V, we get the fraction 850/11!
    int_part = ADC_val/(x) ;// this would yield a int value of 3.3V (our ADC voltage)
    // note ADC_val is a int of 0-255.
    //int_part yields int part of the real voltage, floats are concated
    frac_part = (ADC_val*100/(x)) - int_part*100 ;// 
    // to reassign floats, we multiply the values both by 100. 
    // after deducting real value from int_part, we are left with float values up to 2db
    // 100 is variable depending on db chosen, if we want 3db, 1000 is chosen.
    sprintf(buf,"%d.%02d",int_part,frac_part); //added V after %.02d which shows V in screen
    //sprintf(buf, "%d", ADC_val); // comment out all above and input this function for 3(a)
    //writs value into the buf address, where its a string of 2 things, int part and frac part
    LCD_sendstring(buf); //use send string function to print value within buf
    __delay_ms(250);
    LCD_sendbyte (0b000000001,0); // clears the display once done (stops additional data being printed)
    __delay_ms(2);
    
}
void LCD_setlines(char cname,char ch,signed char cmin,signed char cs,signed char cd,char cm, unsigned int cy,char cBST){
   char line1[20];
   char line2[20];
    sprintf(line1,"%d   %d: %d: %d" ,cname,ch,cmin,cs); // print line1 for dayname, hour:min:sec
    sprintf(line2,"%d %d %d %d",cd,cm,cy,cBST); //print line2 for day,month,year and BST boolean
    LCD_sendbyte(0b00001100,0); //Turn on display
    LCD_sendstring(line1); //Send string 1 to LCD
    LCD_setline(2); //Set second line
    LCD_sendstring(line2); // Send string 2 as above 
    __delay_ms(20);
    LCD_sendbyte(0b00000001,0); //Clear display
   __delay_ms(2);
}
