/* Name: main.c
 * Project: Lab 1 1.4.1
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/

#include "MEAM_general.h"  
#include "util/delay.h"  //Include delay function
#include "m_usb.h"  //Include USB comm.(for debugging, if needed)

int i = 0;

void setup_PWM(int DUTY);  // Function to generate PWM signal
void fade_out(int start, int end);  //Function to create fading out effect
void fade_in(int start, int end);  //Fucntion to create fading in effect

int main(void) {
    _clockdivide(0);  // Set the system clock speed to 16 MHz
    DDRC |= (1 << PC6);  // Set PC6 (OC3A) as OUTPUT

    setup_PWM(0);  // Ensure LED starts off

    for (;;) {  // Infinite loop
        fade_in(0, 100);  //  Gradually increase brightness from 0% to 100%
        fade_out(100, 0);  // Gradually decrease brightness from 100% to 0%
    }

    return 0; // Never reached
}

void setup_PWM(int DUTY) {
    if (DUTY == 0) {
        OCR3A = 0;  // Turn off LED initially, output compare register is 0
    } 
    
    else {
        OCR3A = (DUTY * 255) / 100;  // Convert duty cycle (0-100%) to 8-bit (0-255) value

        // Configure Timer3 for Mode 5 (PWM, Phase-Correct, 8-bit)
        TCCR3A = (1 << WGM30) | (1 << COM3A1);  // Non-inverting PWM on OC3A
        TCCR3B = (1 << CS32);  // Prescaler 256 (~122 Hz PWM frequency)
    }
}

// Function to gradually increase brightness from 0% to 100%
void fade_in(int start, int end) {
    for (i = start; i <= end; i++) {  //Increase brightness in small steps
        setup_PWM(i);                 // Set PWM duty cycle
        _delay_ms(3);                 // Delay per step to control fade speed (Total fade-in: 300ms)
    }
}

// Function to gradually decrease brightness from 100% to 0%
void fade_out(int start, int end) {
    for (i = start; i >= end; i--) {  //Decrease brightness in small steps
        setup_PWM(i);                 // Set PWM duty cycle
        _delay_ms(6);                 // Delay per step to control fade speed (Total fade-out: 600ms)
    }
}















