/* Name: main.c
 * Project: Lab 3 3.1.3
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/


// #include "MEAM_general.h"
// #include "m_usb.h"

// void ADC_init() {
//     clear(ADMUX, REFS1);   // Set reference voltage to VCC (5V)
//     set(ADMUX, REFS0);  

//     set(ADCSRA, ADPS2) | (ADCSRA, ADPS1) | (ADCSRA, ADPS0); // Set ADC clock prescaler to 128


//     set(ADCSRA, ADEN); // Enable ADC
// }

// uint16_t ADC_read(uint8_t channel) {

//     if (channel < 8) {  // Disable digital input on selected ADC pin
//         set(DIDR0, channel);
//     } else {
//         set(DIDR2, channel - 8);
//     }

//     ADMUX = (ADMUX & 0xF0) | (channel & 0x07); // Select the desired ADC channel (ADC0 to ADC7)

//     set(ADCSRA, ADSC);  // Start conversion
//     while (bit_is_set(ADCSRA, ADSC)); // Wait until conversion completes

//     return ADC; // Return ADC result
// }

// // Map ADC range (0-1023) to an angle range (0-180°)
// uint8_t map_adc_to_angle(uint16_t adc_value) {
//     return (uint8_t)((adc_value * 180L) / 1023);  // 'L' ensures proper scaling
// }

// // Subroutine to read and print the angle from Potentiometer 1 (ADC7)
// void read_pot1() {
//     uint16_t pot1 = ADC_read(7);  // Read from ADC7 (A0)
//     uint8_t angle1 = map_adc_to_angle(pot1);

//     m_usb_tx_string("Pot 1 ADC: ");
//     m_usb_tx_int(pot1);
//     m_usb_tx_string(" | Angle: ");
//     m_usb_tx_int(angle1);
//     m_usb_tx_char('\n');
// }

// // Subroutine to read and print the angle from Potentiometer 2 (ADC6)
// void read_pot2() {
//     uint16_t pot2 = ADC_read(6);  // Read from ADC6 (A1)
//     uint8_t angle2 = map_adc_to_angle(pot2);

//     m_usb_tx_string("Pot 2 ADC: ");
//     m_usb_tx_int(pot2);
//     m_usb_tx_string(" | Angle: ");
//     m_usb_tx_int(angle2);
//     m_usb_tx_char('\n');
// }

// int main() {
//     _disableJTAG();   // Disable fuse if using PORTF
//     _clockdivide(0);  // Set clock speed to 16 MHz

//     ADC_init();      // Initialize ADC
//     m_usb_init();    // Initialize USB communication

    

//     while (1) {
//         read_pot1(); // Read and print Pot 1 angle
//         read_pot2(); // Read and print Pot 2 angle
//         _delay_ms(500);
//     }
// }


// #include "MEAM_general.h"
// #include "m_usb.h"
// #include <avr/io.h>
// #include <util/delay.h>

// void ADC_init() {
//     clear(ADMUX, REFS1);   // Set reference voltage to VCC (5V)
//     set(ADMUX, REFS0);  

//     set(ADCSRA, ADPS2);
//     set(ADCSRA, ADPS1);
//     set(ADCSRA, ADPS0); // Set ADC clock prescaler to 128

//     set(ADCSRA, ADEN); // Enable ADC
// }

// uint16_t ADC_read(uint8_t channel) {
//     if (channel < 8) {  // Disable digital input on selected ADC pin
//         set(DIDR0, channel);
//     } else {
//         set(DIDR2, channel - 8);
//     }

//     ADMUX = (ADMUX & 0xF0) | (channel & 0x07); // Select the desired ADC channel (ADC0 to ADC7)

//     set(ADCSRA, ADSC);  // Start conversion
//     while (bit_is_set(ADCSRA, ADSC)); // Wait until conversion completes

//     return ADC; // Return ADC result
// }

// // Map ADC range (0-1023) to Servo PWM range (1000-2000µs)
// uint16_t map_adc_to_pwm(uint16_t adc_value) {
//     return ((adc_value * 1000L) / 1023); // Scale ADC (0-1023) → PWM (1000-2000µs)
// }

// // Initialize Timer1 for Servo PWM on PB1 (OC1A)
// void servo_init() {
//     set(DDRB, PB1);  // Set PB1 (OC1A) as output

//     // Configure Timer1 for Fast PWM (Mode 14: ICR1 as TOP)
//     TCCR1A |= (1 << COM1A1) | (1 << WGM11);
//     TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11); // Prescaler 8 → 16MHz/8 = 2MHz

//     ICR1 = 20000;  // Set TOP for 50Hz (20ms period)
//     OCR1A = 1500;  // Default 1500µs (90° midpoint)
// }

// // Set Servo PWM (1000-2000µs)
// void set_servo_position(uint16_t pwm_value) {
//     OCR1A = pwm_value;
// }

// // Read and print angle from Potentiometer 1 (ADC7) & move Servo
// void read_pot1() {
//     uint16_t pot1 = ADC_read(7);  // Read from ADC7 (A0)
//     uint16_t pwm_value = map_adc_to_pwm(pot1); // Convert to servo PWM

//     set_servo_position(pwm_value); // Move Servo

//     m_usb_tx_string("Pot 1 ADC: ");
//     m_usb_tx_int(pot1);
//     m_usb_tx_string(" | PWM: ");
//     m_usb_tx_int(pwm_value);
//     m_usb_tx_char('\n');
// }

// // // Read and print angle from Potentiometer 2 (ADC6)
// // void read_pot2() {
// //     uint16_t pot2 = ADC_read(6);  // Read from ADC6 (A1)
// //     uint8_t angle2 = (pot2 * 180L) / 1023; // Convert ADC to angle

// //     m_usb_tx_string("Pot 2 ADC: ");
// //     m_usb_tx_int(pot2);
// //     m_usb_tx_string(" | Angle: ");
// //     m_usb_tx_int(angle2);
// //     m_usb_tx_char('\n');
// // }

// int main() {
//     _disableJTAG();
//     _clockdivide(0);  // Set clock to 16 MHz

//     ADC_init();
//     m_usb_init();
//     servo_init();  // Initialize Servo PWM

//     while (1) {
//         read_pot1(); // Read and move Servo based on Pot 1
//         // read_pot2(); // Just print Pot 2 values (no servo control)
//         _delay_ms(50); // Small delay for stability
//     }
// }


#include "MEAM_general.h"
#include "m_usb.h"
#include <avr/io.h>

void ADC_init() {
    clear(ADMUX, REFS1);   // Set reference voltage to VCC (5V)
    set(ADMUX, REFS0);  

    set(ADCSRA, ADPS2) | (ADCSRA, ADPS1) | (ADCSRA, ADPS0); // Set ADC clock prescaler to 128
    set(ADCSRA, ADEN); // Enable ADC
}

uint16_t ADC_read(uint8_t channel) {
    if (channel < 8) {
        set(DIDR0, channel);
    } else {
        set(DIDR2, channel - 8);
    }

    ADMUX = (ADMUX & 0xF0) | (channel & 0x07);
    set(ADCSRA, ADSC);
    while (bit_is_set(ADCSRA, ADSC));

    return ADC;
}

// Map ADC range (0-1023) to Servo PWM pulse width (1000-2000µs)
uint16_t map_adc_to_pwm(uint16_t adc_value) {
    return ((adc_value * 1000L) / 1023) + 1000;  // PWM range: 1000 to 2000 µs
}

void Timer3_init() {
    // Set OC3A (Pin PE3) as output
    set(DDRC, 6);

    // Mode 14: Fast PWM with ICR3 as TOP
    set(TCCR3A, WGM31);
    clear(TCCR3A, WGM30);
    set(TCCR3B, WGM33);
    set(TCCR3B, WGM32);

    // Set non-inverting mode for OC3A
    set(TCCR3A, COM3A1);
    clear(TCCR3A, COM3A0);

    // Set ICR3 for 50Hz (20ms period) with 128 prescaler
    ICR3 = 2499;

    // Prescaler = 1024
    set(TCCR3B, CS32);
    clear(TCCR3B, CS31);
    set(TCCR3B, CS30);
}

void set_servo_angle(uint16_t pulse_width) {
    OCR3A = (pulse_width * 1249L) / 20000; // Scale 1000-2000µs to ICR3 (0-2499)
}

int main() {
    _disableJTAG();
    _clockdivide(0);
    
    ADC_init();
    Timer3_init();
    m_usb_init();

    while (1) {
        uint16_t adc_value = ADC_read(7);  // Read ADC from Potentiometer
        uint16_t pwm_value = map_adc_to_pwm(adc_value);

        set_servo_angle(pwm_value);  // Control Servo with Timer 3 PWM

        m_usb_tx_string("ADC: ");
        m_usb_tx_int(adc_value);
        m_usb_tx_string(" | PWM: ");
        m_usb_tx_int(pwm_value);
        m_usb_tx_char('\n');

        _delay_ms(50);
    }
}


