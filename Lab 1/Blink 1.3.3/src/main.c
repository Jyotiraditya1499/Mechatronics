/* Name: main.c
 * Project: Lab 1
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/

#include "MEAM_general.h"  // Includes the MEAM resources

#define DUTY_CYCLE 25  // Desired duty cycle (0-100)
#define DUTY_CYCLE_VAL ((DUTY_CYCLE * 255) / 100)  // Convert % to OCR3A value

int main(void) {
    _clockdivide(0);
    DDRC |= (1 << PC6);  // Set PC6 (OC3A) as OUTPUT
    
    TCCR3A = 0;
    TCCR3B = 0;

    // Configure Timer3 for Mode 5 (PWM, Phase-Correct, 8-bit)
    TCCR3A = (1 << WGM30) | (1 << COM3A1);  // Non-inverting PWM on OC3A (PC6)
    TCCR3B = (1 << WGM32);

    

    if (DUTY_CYCLE == 0)
        {
            PORTC &= ~(1 << PC6);  // Clear PC6 manually
            /* code */
        }

        else
        {
        TCCR3B = (1 << CS31);  // Prescaler 8
        OCR3A = DUTY_CYCLE_VAL;  // Set initial duty cycle

        }

    while (1) {  // PWM runs automatically


    }  
    return 0;
}
