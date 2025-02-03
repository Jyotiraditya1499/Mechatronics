/* Name: main.c
 * Project: Lab 1
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file

#define DUTY_CYCLE 50
#define DUTY_CYCLE_VAL ((DUTY_CYCLE * 255) / 100)

int main(void) {
    _clockdivide(0);
    DDRB |= (1 << PB7);  // Set PB7 as OUTPUT

    // Configure Timer3 for Mode 5 (PWM, Phase-Correct, 8-bit)
    TCCR3A = (1 << WGM30) | (1 << COM3A1) | (1 << COM3A0);  // Inverting PWM (set on match, clear at rollover)
    TCCR3B = (1 << CS31);  // Prescaler 8

    OCR3A = DUTY_CYCLE_VAL;  // Set duty cycle

    while (1) {}  // PWM runs automatically

    return 0;
}



