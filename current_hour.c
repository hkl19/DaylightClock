#include <xc.h>
#include "current_hour.h"
#include "comparator.h"
#include "interrupts.h"
#include "timer.h"
#include "LEDarray.h"
#include "LDR.h"

//If we can assume that brightness for dusk and dawn are the same.
//we can assigned a threshold to the LDR voltage, which gives time of 8am or 4pm.
//According to the graph, if we take the midpoint of when the two threshold voltages meet.
//We can declare that as noon.
//This is done assuming the sun is always of constant brightness, not taking into
//account cloudiness, we could also use the timer to count, maybe use the H3 output
//as a for loop to add the hours up. #

int what_hour(int current_hour, int count,  int max_count){
    //here we use the timer to represent an hour change
    //initialisation of the LED clock should be via the current_hour int replacement
    //max_count is 3600s for 1 day case, and max_count is 1s for the 24s testing period. 
    if (LATHbits.LATH3){ //interrupt flag triggered
        LATHbits.LATH3 = 0;
        count ++; //add a second to the counter
            if (count==max_count){
                if (current_hour < 23){
                    current_hour ++;
                    count = 0;
                }
                else {
                    current_hour = 0;
                    count = 0;
                 } 
             }   
    return current_hour;
    }
}
    
