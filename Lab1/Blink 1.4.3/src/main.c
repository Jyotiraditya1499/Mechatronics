/* Name: main.c
 * Project: Lab 1 1.4.3
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/

#include "MEAM_general.h"

// Adjustable Maximum Brightness (starts at 100% and fades over 20 beats)
#define INITIAL_MAX_INTENSITY 100  
#define TOTAL_BEATS 20  // Number of beats before fading to 0%

// Fade timing settings (adjust for desired speed)
#define FADE_STEPS 100    

int i = 0;

void setup_PWM(int DUTY);
void fade(int start, int end, int duration);
void heartbeat(int max_intensity);

int main(void) {
    _clockdivide(0);  // Set clock to 16 MHz
    DDRC |= (1 << PC6);  // Set PC6 (OC3A) as OUTPUT for PWM

    setup_PWM(0);  // Start with LED OFF

    int max_intensity = INITIAL_MAX_INTENSITY;  // Start at full intensity
    int beat;

    for (beat = 0; beat < TOTAL_BEATS; beat++) {  
        heartbeat(max_intensity);  // Play two heartbeat cycle
        max_intensity -= INITIAL_MAX_INTENSITY / TOTAL_BEATS;  // Reduce intensity gradually
    }

    // Once all beats are completed, ensure LED is off
    fade(max_intensity, 0, 500);  // Slowly fade LED to OFF

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

// Generic fade function (smooth transition between intensities)
void fade(int start, int end, int duration) {
    float step_size = (float)(end - start) / FADE_STEPS;    // Calculate step size
    int step_delay = duration / FADE_STEPS;                 // Calculate delay per step
    float intensity = start;                                // Use float to prevent rounding errors

    for (i = 0; i < FADE_STEPS; i++) {
        setup_PWM((int)intensity);  // Convert back to int when setting brightness
        intensity += step_size;     // Smoothly update brightness
        _delay_ms(step_delay);
    }
    
    setup_PWM(end);  // Ensure the final value is correctly set
}

// Heartbeat Effect: Simulates a cardiac rhythm ("Lub-Dub")
void heartbeat(int max_intensity) {
    fade(0, max_intensity, 100);  // t = 0s → 0% to max_intensity% (0.1s)
    fade(max_intensity, 0, 400);  // t = 0.1s → max_intensity% to 0% (0.5s)
    fade(0, max_intensity / 2, 100);  // t = 0.6s → 0% to half max_intensity% (0.1s)
    fade(max_intensity / 2, 0, 400);  // t = 0.7s → half max_intensity% to 0% (0.4s)

    _delay_ms(2000);  // Pause between heartbeats

   fade(0, max_intensity, 100);  // t = 3.1s → 0% to max_intensity% (0.1s)
   fade(max_intensity, 0, 400);  // t = 3.5s → max_intensity% to 0% (0.5s)
   fade(0, max_intensity / 2, 100);  // t = 3.6s → 0% to half max_intensity% (0.1s)
   fade(max_intensity / 2, 0, 400);  // t = 4.0s → half max_intensity% to 0% (0.4s)

   _delay_ms(1000);  // Pause before next cycle
}















