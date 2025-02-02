/* Name: main.c
 * Project: Lab 1
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file

#define COMPARE 50000 //Value based on the prescaller used to generate 20Hz


int main(void)
{
    _clockdivide(0); //set the clock speed to 16Mhz
    DDRB |= (1 << PB7);  // Set PB7 as OUTPUT
    TCCR3B = (1 << CS31) | (1 << CS30);  // Counter 3 (Prescaler 64)
    TCCR3A = 0; // (Normal Mode, 16-bit)

    for(;;){

        if (TCNT3 >= COMPARE){  //  Wait untill Timer3 reaches COMPARE value
            PORTB ^= (1 << PB7); // Toggle LED at PORT B7
            TCNT3 = 0;  //Reset Timer3
        }

    }
    return 0;   /* never reached */
}


