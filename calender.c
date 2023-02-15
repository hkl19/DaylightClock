#include <xc.h>
#include "calender.h"
#include "LDR.h"
#include "interrupts.h"
#include "timer.h"
#include "LCD.h"
#include "comparator.h"
#define Test_Second 2;  //comment this out for the below val for actual reading
//#define hour_to_second = 3600; 

#define _XTAL_FREQ 64000000

    //**************************************************************//
    //***************Daylight Saving Hour Function******************//
    //**************************************************************//
void daylight_save(char BST,char s,char h){
    //Setup all Variables
    unsigned int tol = 100; //tolerance in seconds
    unsigned int offset_s;  //second offset
    char         offset_h;  //hour offset
    unsigned char du_s;     //dusk second
    unsigned char du_h;     //dusk hour
    unsigned char da_s;     //dawn second
    unsigned char da_h;     //dawn hour
    unsigned char sol_noon; //solar noon
    
    //Declare where is solar noon based on BST value
    if (BST==1){sol_noon = 13;}
    //assume at BST, solar noon is 1:00pm sharp
    else {sol_noon = 12;} 
    //assume non BST, solar noon is 12:00pm sharp.
        
    //Check in dusk between 5-10am
    //If light turns off due to LDR triggering, record s as du_s and h as du_h
        if (h>=5 && h<=10) {
                if (LATDbits.LATD7=0){
                    du_s = s;
                    du_h = h;
                }
        }
    //Check in dawn between 3-10pm
    //If light turns on due to LDR triggering, record s as da_s and h as da_h
        else if (h>=15 && h<=22) {
                if (LATDbits.LATD7=1){
                    da_s = s;
                    da_h = h;
                }
        }
    
        offset_s = ((du_s)+(da_s))/2 ; //average du and da secs, this yields the offset in seconds
        offset_h = ((du_h+da_h)/2) - sol_noon; //offset_h tells if we are running over/under actual time.
        if (offset_s > tol) { //if recorded time runs over a certain tolerance
            if (offset_h<0){ //if the offset hour is less than 0, which means clock slower than actual time.
                h ++; //add an hour since its we are running slower
                s = s - offset_s; //deduct offset from current sec on clock
 
            }
            else {           // case for clock being faster than actual time
                s = s - offset_s;  //solely deduct the offset
            }
        }
}
