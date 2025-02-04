/* Name: main.c
 * Project: Lab 1
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/

#include "MEAM_general.h"  // Includes MEAM resources
#include <util/delay.h>    // Required for _delay_ms()

#define MAX_BRIGHTNESS 255  // Maximum PWM value (100% brightness)
#define FADE_STEPS 100      // Number of steps for smooth fading

// Function to initialize Timer3 PWM on PC6 (OC3A)
void setup_PWM(void) {
    _clockdivide(0);
    DDRC |= (1 << PC6);  // Set PC6 (OC3A) as OUTPUT

    // Configure Timer3 for Mode 5 (PWM, Phase-Correct, 8-bit)
    TCCR3A = (1 << WGM30) | (1 << COM3A1);  // Non-inverting PWM
    TCCR3B = (1 << CS31);  // Prescaler 8 (PWM ~3.92 kHz)
}

// Function to set LED to maximum brightness instantly
void set_max_intensity(void) {
    OCR3A = MAX_BRIGHTNESS;  // Full brightness
}

// Function to turn LED off instantly
void set_min_intensity(void) {
    OCR3A = 0;  // LED OFF
}

// Function to gradually fade LED in and out
void pulse_LED(uint16_t fade_in_time, uint16_t fade_out_time) {
    uint8_t i;
    uint16_t step_delay_in = fade_in_time / FADE_STEPS;   // Delay per step for fade-in
    uint16_t step_delay_out = fade_out_time / FADE_STEPS; // Delay per step for fade-out

    // Fade in (0 to MAX_BRIGHTNESS)
    for (i = 0; i <= MAX_BRIGHTNESS; i += (MAX_BRIGHTNESS / FADE_STEPS)) {
        OCR3A = i;
        _delay_ms(step_delay_in);
    }

    // Fade out (MAX_BRIGHTNESS to 0)
    for (i = MAX_BRIGHTNESS; i > 0; i -= (MAX_BRIGHTNESS / FADE_STEPS)) {
        OCR3A = i;
        _delay_ms(step_delay_out);
    }

    OCR3A = 0;  // Ensure it fully turns off at the end
}

int main(void) {
    setup_PWM();  // Initialize PWM

    uint16_t fade_in_time = 500;  // Default fade-in time (milliseconds)
    uint16_t fade_out_time = 500; // Default fade-out time (milliseconds)

    while (1) {
        pulse_LED(fade_in_time, fade_out_time);  // Smooth pulsing effect
    }

    return 0;
}












