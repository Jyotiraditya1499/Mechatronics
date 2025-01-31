/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file

int main(void)
{
    _clockdivide(0); //set the clock speed to 16Mhz

    DDRB |= (1 << PB7);

    /* insert your hardware initialization here */
    for(;;){
        /* insert your main loop code here */
        PORTB ^= (1 << PB7);
        _delay_ms(1000);

    }
    return 0;   /* never reached */
}
