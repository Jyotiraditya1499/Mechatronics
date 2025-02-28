/* Name: main.c
 * Project: Lab 3 3.2
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/


#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#include "m_usb.h"



void ADC_init(uint8_t channel) {
    
    clear(ADMUX, REFS1);  // Set reference voltage to Vcc
    set(ADMUX, REFS0); 

    
    set(ADCSRA, ADPS2) | (ADCSRA, ADPS1) | (ADCSRA, ADPS0); // Set ADC clock prescaler to 64 (adjust based on clock speed)

    
    if (channel < 8) {              // Disable digital input on selected ADC pin
        set(DIDR0, channel);
    } else {
        set(DIDR2, channel - 8);
    }


    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);    // Select ADC channel
    if (channel >= 8) {
        set(ADCSRB, MUX5);
    } else {
        clear(ADCSRB, MUX5);
    }

    set(ADCSRA, ADEN);    // Enable ADC
}

uint16_t ADC_read() {
    set(ADCSRA, ADSC);              // Start conversion
    while (ADCSRA & (1 << ADSC));   // Wait until conversion completes
    return ADC;                     // Return ADC result
}



int main() {
    _disableJTAG();         //disable fuse if using PORTF
    _clockdivide(0);        //set the clock speed to 16Mhz

    ADC_init(1);            // Initialize ADC on channel 0 (F0)
    m_usb_init();           // Initialize USB communication

    
    while (1) {
        uint16_t adc_value = ADC_read(); // Read ADC value
        m_usb_tx_int(adc_value);        // Print value over USB (if using debug)
        m_usb_tx_char('\n');
        _delay_ms(500);                 // Delay for readability
    }
}

// #include "MEAM_general.h"
// #include "m_usb.h"

// void ADC_init(uint8_t channel) {
//     // Set reference voltage to AVCC (5V)
//     clear(ADMUX, REFS1);
//     set(ADMUX, REFS0);

//     // Set ADC clock prescaler to 64 (assuming 16MHz clock)
//     set(ADCSRA, ADPS2);
//     set(ADCSRA, ADPS1);
//     set(ADCSRA, ADPS0);

//     // Select ADC channel
//     ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
//     if (channel >= 8) {
//         set(ADCSRB, MUX5);
//     } else {
//         clear(ADCSRB, MUX5);
//     }

//     // Disable digital input on selected ADC pin
//     if (channel < 8) {
//         set(DIDR0, channel);
//     } else {
//         set(DIDR2, channel - 8);
//     }

//     // Enable ADC
//     set(ADCSRA, ADEN);

//     // Start first conversion (for stability)
//     set(ADCSRA, ADSC);
// }

// uint16_t ADC_read() {
//     set(ADCSRA, ADSC);            // Start conversion
//     while (bit_is_set(ADCSRA, ADSC)); // Wait until conversion completes
//     return ADC;                   // Return ADC result
// }

// int main() {
//     _disableJTAG();  // Disable JTAG if using PORTF
//     _clockdivide(0); // Set clock speed to 16MHz

//     ADC_init(0);     // Initialize ADC on channel 0 (PF0)
//     m_usb_init();    // Initialize USB communication

//     while (1) {
//         uint16_t adc_value = ADC_read(); // Read ADC value
//         m_usb_tx_int(adc_value);        // Print ADC value
//         m_usb_tx_char('\n');
//         _delay_ms(500);                 // Delay for readability
//     }
// }
