/* Name: main.c
 * Project: Lab 1
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#define COMPARE 65000


int main(void)
{
    _clockdivide(0); //set the clock speed to 16Mhz
    DDRB |= (1 << PB7);  // Set PB7 as OUTPUT
    TCCR3B = (1 << CS10) | (1 << CS11);  //Turn on Timer 3 (No prescaler)
    TCCR3A = 0;

    for(;;){
        /* insert your main loop code here */
        if (TCNT3 > COMPARE){
            PORTB ^= (1 << PB7);
            TCNT3 = 0;
        }
        //_delay_ms(1000);

    }
    return 0;   /* never reached */
}


