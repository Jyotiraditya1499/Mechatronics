/* Name: main.c
 * Project: Lab 1 1.4.2
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/

#include "MEAM_general.h"

// Adjustable Maximum Brightness (0-100%)
#define MAX_INTENSITY 100  

// Fade timing settings (adjust for desired speed)
#define FADE_STEPS 100    

int i = 0;

void setup_PWM(int DUTY);
void fade(int start, int end, int duration);
void heartbeat(void);

int main(void) {
    _clockdivide(0);  // Set clock to 16 MHz
    DDRC |= (1 << PC6);  // Set PC6 (OC3A) as OUTPUT for PWM

    setup_PWM(0);  // Start with LED OFF

    while (1) {
        heartbeat();  // Call heartbeat effect
        int new_intensity = MAX_INTENSITY - 10;
    }

    return 0; // Never reached
}

// Configure Timer3 for PWM based on duty cycle (0-100%)
void setup_PWM(int DUTY) {
    if (DUTY == 0) {
        OCR3A = 0;  // LED OFF
    } else {
        OCR3A = (DUTY * 255) / 100;  // Convert % to 8-bit (0-255)
        TCCR3A = (1 << WGM30) | (1 << COM3A1);  // Non-inverting PWM on OC3A
        TCCR3B = (1 << CS32);  // Prescaler 256 (~122 Hz PWM frequency)
    }
}

//Fade function (smooth transition between intensities)
void fade(int start, int end, int duration) {
    int step_delay = duration / FADE_STEPS;  // Calculate delay per step
    int step_size = (end - start) / FADE_STEPS;  // Calculate step size
    int intensity = start;

    for (i = 0; i < FADE_STEPS; i++) {
        setup_PWM(intensity);
        intensity += step_size;
        _delay_ms(step_delay);
    }
    setup_PWM(end);  // Ensure final value is set
}

// Heartbeat Effect: Simulates a cardiac rhythm ("Lub-Dub")
void heartbeat(void) {
    fade(0, MAX_INTENSITY, 100);  // t = 0s → 0% to 100% (0.1s)
    fade(MAX_INTENSITY, 0, 400);  // t = 0.1s → 100% to 0% (0.5s)
    fade(0, MAX_INTENSITY / 2, 100);  // t = 0.6s → 0% to 50% (0.1s)
    fade(MAX_INTENSITY / 2, 0, 400);  // t = 0.7s → 50% to 0% (0.4s)

    _delay_ms(2000);  // Pause between heartbeats (t = 1.0s to 3.0s)

    fade(0, MAX_INTENSITY, 100);  // t = 3.0s → 0% to 100% (0.1s)
    fade(MAX_INTENSITY, 0, 400);  // t = 3.1s → 100% to 0% (0.5s)
    fade(0, MAX_INTENSITY / 2, 100);  // t = 3.6s → 0% to 50% (0.1s)
    fade(MAX_INTENSITY / 2, 0, 400);  // t = 3.7s → 50% to 0% (0.4s)

    _delay_ms(1000);  // Extra pause before repeating
}
















