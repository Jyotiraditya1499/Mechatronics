/* Name: main.c
 * Project: Lab 1
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file

#define DUTY_CYCLE 50   // Set the desired duty cycle
#define DUTY_CYCLE_VAL ((DUTY_CYCLE*255)/100)  //Convert % to OCR3A value

int main(void)
{
    _clockdivide(0); //set the clock speed to 16Mhz
    DDRB |= (1 << PB6);  // Set PB7 as OUTPUT

    // Configure Timer3 for Mode 5 (PWM, Phase-Correct, 8-bit)
    TCCR3A = (1 << WGM30) | (1 << COM3B1); // (PWM Mode 5)
    TCCR3B = (1 << CS31) | (1 << WGM32);  // Counter 3 (Prescaler 8)
    
    OCR3A = DUTY_CYCLE_VAL;  // Set Initial duty cycle

    while(1){

    }

    return 0;   /* never reached */
}



