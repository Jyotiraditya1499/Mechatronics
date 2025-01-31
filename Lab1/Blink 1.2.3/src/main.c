/* Name: main.c
 * Project: Lab 1
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/


#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file

int main(void)
{
    _clockdivide(0); //set the clock speed to 16Mhz

    DDRB |= (1 << PB7);  // Set PB7 as OUTPUT

   
    for(;;){
       
        PORTB ^= (1 << PB7);  // TOGGLE the state of PB7
        _delay_ms(1000);  //Delay 1 sec

    }
    return 0;   /* never reached */
}
