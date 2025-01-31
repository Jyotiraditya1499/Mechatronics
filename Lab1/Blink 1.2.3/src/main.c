/* Name: main.c
 * Project: Lab 1
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/


#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#define DUTYCYCLE 50  // Set the duty cycle percentage

int main(void)
{
    _clockdivide(0); //set the clock speed to 16Mhz

    DDRB |= (1 << PB7);  // Set PB7 as OUTPUT

   
    for(;;){
       
        PORTB |= (1 << PB7);  // Turn ON led
        _delay_ms(10*DUTYCYCLE);  //Delay 
        PORTB &= ~(1 << PB7);  // Turn OFF led
        _delay_ms(10* (100 - DUTYCYCLE));  //Delay

    }
    return 0;   /* never reached */
}

