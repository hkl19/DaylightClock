#pragma config FEXTOSC = HS //External Oscillator mode Selection bits
#pragma config RSTOSC = EXTOSC_4PLL // power-up default val for COSC bits

#pragma config WDTE = OFF //WDT operating mode (WDT enabled regardless of sleep 

#include <xc.h>
#include "LEDarray.h"
#include "LDR.h"
#include "comparator.h"
#include "interrupts.h"
#include "timer.h"
#include "LCD.h"
#include "calender.h"
#define Test_Second 2;  //comment this out for the below val for actual reading
//#define hour_to_second = 3600; 


#define _XTAL_FREQ 64000000 // intrinsic __delay function is 62.5ns at 64MHz

void main(void) {
   // call functions for initialisations 
    LED_init(); //LED initiation for pins
    LDR_init(); //LDR initiation for light detection calculations
    Interrupts_init(); //Interrupt Initiation for Second Counter
    DAC_init();    // DAC initiation for converter
    Comp1_init();  // initiate comparator functions and pins
    LCD_Init(); //Initiation for LCD, allows calender function to show
    Timer0_init(); // Initiate timer0 for counter 
    
    //**************************************************************//
    //****Variables that determine the calender and clock output****//
    //**************************************************************//
    
    char         ds = 0; // Initial input for sec, 0-59
    char         dmin = 0; // Initial input for min, 0-59
    signed char  dh = 4; // Initial input for hour, 0-23
    signed char  dname = 6 ; // Initial input for day name, Sunday to Saturday (0-6)
    signed char  dd = 26; // Initial input for day, 1-31 depending on month.
    char         dm = 3; // Initial input for month, 1-12
    unsigned int dy = 2019; // Initial input for year
    char         dBST = 0;//BST input
    unsigned int min_length = 1; //set this to 60 for non-test
    unsigned int hour_length = 1; // set this to 60 for non-test
    unsigned int hours_in_day = 24; //Usually set to 24hours for Terrestrial days
    unsigned int dim[] = {31,28,31,30,31,30,31,31,30,31,30,31}; //Days in months assign array
    
    //**************************************************************//
    //******************MAIN CODE FOR CALENDER**********************//
    //**************************************************************//
    while (1){
        //START WITH LEAP YEAR TRACKER//
        if ((dy%4==0 && dy%100!=0) || (dy%400==0)) {           // if leap year
            dim[1] = 29;                                    // Feb has 29 days
            }
        else {                                         // Else, Feb has 28 days
            dim[1] = 28;
            } 
        
        //TIMER CLOCK STARTS HERE//
        if (LATHbits.LATH3){
        LATHbits.LATH3=0;
        ds++;
        if (ds>=min_length){
            ds = 0;                // set second = 0, so second won't go over 59
           if (dmin<(hour_length-1)) {                   // if minute count < 60
                dmin ++;                                  // increment min count
           }
           else if (dmin>=(hour_length-1)){                 //if min count = 60
               dmin = 0;                                  // set min count to 0
                if (dh<(hours_in_day-1)) {                 // if hour count <24
                    dh++;                                      //Increment hour
                }
                else if (dh>=(hours_in_day-1)){              //if hour count =24
                    dh = 0;                                   //reset hour to 0
                   if ((dname<6)&& (dd<dim[dm-1])){ // if not Saturday and not end of month
                        dname ++;                        //Increment day and date
                        dd ++; 
                   }
                   else if ((dname==6) && (dd<dim[dm-1])){ // if Sat and not end of month
                       dname = 0;                        //Change date to Sunday
                       dd ++;                                  //Increment date
                            if (dm==3){ 
                                //if its the last Sunday of March, when BST is 0
                             if ((dh==0 && dname==0) && (dd>=25 && dBST==0)){
                                    dh=1;                        //Add an hour
                               }
                            }
                            else if (dm==10){ 
                                //if its the last Sunday of October, BST is 1
                                if ((dh==0 && dname==0) && (dd>=25 && dBST==1)){
                                    dh=-1;                           //let h -1 
                                    dname = -1; //set it to -1 since h = 0 would cause a day shift
                                    dd = dd-1;             //due to above h = -1
                                    dBST=0;                         //reset BST
                               }
                           }
                        
                    }
                    else if ((dname<6) && (dd==dim[dm-1])){ 
                        // If its not a Saturday but its End of the Month
                        dname ++;                            //Add day of week
                       dd = 1;                        //Reset Date of Month to 1
                        if (dm<12) {                //for Months before December
                           dm++;                              // Increment Month 
                        }
                        else if (dm==12){               // for December Months
                            dm=1;                       // Set month to January
                           dy++;                          // Increment a Year 
                           
                        }
                    }
                   else if ((dname==6)&&(dd==dim[dm-1])){  
                       //If it is a Saturday and an End of Month
                        dname = 0;                        //Reset Day to Sunday
                      dd = 1;                             //Reset Date day to 1
                        if (dm<12) {                      //If its not December
                           dm++;                                // Add Month
                        }
                        else if (dm==12){                   //If its December
                           dm=1;                            //Reset Month to 1
                            dy++;                            //Increment Year
                            } 
                       }
                   }
                }
            }
        }
        daylight_save(dBST,ds,dh);
        LCD_setlines(dname,dh,dmin,ds,dd,dm,dy,dBST);  //Function for LCD display
        LEDarray_disp_bin(dh);                   //LDR function, controls LED RD7
        LDR_val();                                   //Yields LDR voltage value
        LDR_thres(LDR_val(),dh);                //Compares that to hour on clock
    }
}
   
    

    

