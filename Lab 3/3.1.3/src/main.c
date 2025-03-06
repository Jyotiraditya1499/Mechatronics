/* Name: main.c
 * Project: Lab 3 3.1.2
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#include "m_usb.h"

void ADC_init(uint8_t channel) {
    clear(ADMUX, REFS1);  // Set reference voltage to Vcc
    set(ADMUX, REFS0);

    set(ADCSRA, ADPS2) | (ADCSRA, ADPS1) | (ADCSRA, ADPS0); // Set ADC clock prescaler to 128

    if (channel < 8) {  // Disable digital input on selected ADC pin
        set(DIDR0, channel);
    } else {
        set(DIDR2, channel - 8);
    }

    ADMUX = (ADMUX & 0xF0) | (channel & 0x07);  // Select ADC channel (ADC0 to ADC7)
    if (channel >= 8) {
        set(ADCSRB, MUX5);
    } else {
        clear(ADCSRB, MUX5);
    }

    set(ADCSRA, ADEN);  // Enable ADC
}

uint16_t ADC_read() {
    set(ADCSRA, ADSC);              // Start conversion
    while (bit_is_set(ADCSRA, ADSC));  // Wait until conversion completes
    return ADC;                     // Return ADC result
}

int main() {

    _disableJTAG();   // Disable fuse if using PORTF
    _clockdivide(0);  // Set clock speed to 16 MHz

    ADC_init(1);      // Initialize ADC
    m_usb_init();     // Initialize USB communication

    while (1) {
        uint16_t adc_value = ADC_read(); // Read ADC value
        m_usb_tx_int(adc_value);        // Print value over USB
        m_usb_tx_char('\n');
        _delay_ms(500);                 // Delay for readability
    }
}







