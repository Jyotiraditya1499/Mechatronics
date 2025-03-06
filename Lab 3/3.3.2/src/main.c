/* Name: main.c
 * Project: Lab 3 3.1.3
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/


#include "MEAM_general.h"
#include "m_usb.h"

void ADC_init() {
    clear(ADMUX, REFS1);   // Set reference voltage to VCC (5V)
    set(ADMUX, REFS0);  

    set(ADCSRA, ADPS2) | (ADCSRA, ADPS1) | (ADCSRA, ADPS0); // Set ADC clock prescaler to 128


    set(ADCSRA, ADEN); // Enable ADC
}

uint16_t ADC_read(uint8_t channel) {

    if (channel < 8) {  // Disable digital input on selected ADC pin
        set(DIDR0, channel);
    } else {
        set(DIDR2, channel - 8);
    }

    ADMUX = (ADMUX & 0xF0) | (channel & 0x07); // Select the desired ADC channel (ADC0 to ADC7)

    set(ADCSRA, ADSC);  // Start conversion
    while (bit_is_set(ADCSRA, ADSC)); // Wait until conversion completes

    return ADC; // Return ADC result
}

// Map ADC range (0-1023) to an angle range (0-180°)
uint8_t map_adc_to_angle(uint16_t adc_value) {
    return (uint8_t)((adc_value * 180L) / 1023);  // 'L' ensures proper scaling
}

// Subroutine to read and print the angle from Potentiometer 1 (ADC7)
void read_pot1() {
    uint16_t pot1 = ADC_read(7);  // Read from ADC7 (A0)
    uint8_t angle1 = map_adc_to_angle(pot1);

    m_usb_tx_string("Pot 1 ADC: ");
    m_usb_tx_int(pot1);
    m_usb_tx_string(" | Angle: ");
    m_usb_tx_int(angle1);
    m_usb_tx_char('\n');
}

// Subroutine to read and print the angle from Potentiometer 2 (ADC6)
void read_pot2() {
    uint16_t pot2 = ADC_read(6);  // Read from ADC6 (A1)
    uint8_t angle2 = map_adc_to_angle(pot2);

    m_usb_tx_string("Pot 2 ADC: ");
    m_usb_tx_int(pot2);
    m_usb_tx_string(" | Angle: ");
    m_usb_tx_int(angle2);
    m_usb_tx_char('\n');
}

int main() {
    _disableJTAG();   // Disable fuse if using PORTF
    _clockdivide(0);  // Set clock speed to 16 MHz

    ADC_init();      // Initialize ADC
    m_usb_init();    // Initialize USB communication

    

    while (1) {
        read_pot1(); // Read and print Pot 1 angle
        read_pot2(); // Read and print Pot 2 angle
        _delay_ms(500);
    }
}

