/* Name: main.c
 * Project: Lab 2 2.2.3
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/


// #include "MEAM_general.h"
// #include "m_usb.h"

// volatile uint16_t first_capture = 0;
// volatile uint16_t second_capture = 0;
// volatile uint16_t pulse_duration = 0;  
// volatile uint8_t new_capture = 0;

// void setup() {
//     _disableJTAG();
//     _clockdivide(0);
//     m_usb_init();
//     while (!m_usb_isconnected());

//     // Set PC6 (Red LED) and PD0 (Green LED) as outputs
//     DDRC |= (1 << PC6);
//     DDRD |= (1 << PD0);

//     // Set PD4 as input for sensor signal
//     DDRD &= ~(1 << PD4);
//     PORTD |= (1 << PD4);

//     // Configure Timer 1 for input capture with 64 prescaler (16MHz / 64 = 250 kHz)
//     TCCR1B |= (1 << CS11) | (1 << CS10);  
//     TCCR1B |= (1 << ICES1);  // Start capturing on rising edge
//     TIMSK1 |= (1 << ICIE1);  // Enable input capture interrupt

//     sei();  // Enable global interrupts
// }

// // Input Capture Interrupt Service Routine (ISR)
// ISR(TIMER1_CAPT_vect) {
//     if (new_capture == 0) {
//         first_capture = ICR1;
//         new_capture = 1;
//     } else {
//         second_capture = ICR1;
//         pulse_duration = second_capture - first_capture;
//         new_capture = 2;
//     }
// }

// void frequency_detect() {
//     if (new_capture == 2) {
//         float frequency = 250000.0 / pulse_duration;  // Correct frequency calculation

//         // USB Output
//         m_usb_tx_string("Frequency: ");
//         m_usb_tx_int((int)frequency);
//         m_usb_tx_string(".");
//         m_usb_tx_int(((int)(frequency * 100)) % 100);  // Two decimal places
//         m_usb_tx_string(" Hz\n");

//         // LED Logic
//         if (frequency > 24 && frequency < 26) {  // Check for ~25 Hz
//             PORTC |= (1 << PC6);
//             PORTD &= ~(1 << PD0);
//         } else if (frequency > 660 && frequency < 665) {  // Check for ~662 Hz
//             PORTC &= ~(1 << PC6);
//             PORTD |= (1 << PD0);
//         } else {
//             PORTC &= ~(1 << PC6);
//             PORTD &= ~(1 << PD0);
//         }

//         new_capture = 0;  // Reset capture flag
//     }
// }

// int main(void) {
//     setup();

//     while (1) {
//         frequency_detect();
//     }

//     return 0;
// }



#include "MEAM_general.h"
#include "m_usb.h"

volatile uint16_t first_capture = 0;
volatile uint16_t second_capture = 0;
volatile uint16_t pulse_duration = 1;  // Avoid division by zero

void setup() {
    _disableJTAG();
    _clockdivide(0);
    m_usb_init();
    while (!m_usb_isconnected());

    // Set PC6 (Red LED) and PD0 (Green LED) as outputs
    DDRC |= (1 << PC6);
    DDRD |= (1 << PD0);

    // Set PD4 as input for sensor signal
    DDRD &= ~(1 << PD4);
    PORTD |= (1 << PD4);

    // Configure Timer 1 for input capture with 64 prescaler (16MHz / 64 = 250 kHz)
    TCCR1B |= (1 << CS11) | (1 << CS10);  
    TCCR1B |= (1 << ICES1);  // Start capturing on rising edge
    TIMSK1 |= (1 << ICIE1);  // Enable input capture interrupt

    //sei();  // Enable global interrupts
}

// **Input Capture Interrupt Service Routine (ISR)**
ISR(TIMER1_CAPT_vect) {
    first_capture = second_capture;  // Shift the last capture
    second_capture = ICR1;  // Store new capture
    pulse_duration = second_capture - first_capture;  // Compute pulse duration
}

// **Detect and Process Frequency**
void frequency_detect() {
    float frequency = 250000.0 / pulse_duration;  // Correct frequency calculation

    // USB Output
    m_usb_tx_string("Frequency: ");
    m_usb_tx_int((int)frequency);
    m_usb_tx_string(".");
    m_usb_tx_int(((int)(frequency * 100)) % 100);  // Two decimal places
    m_usb_tx_string(" Hz\n");

    // LED Logic
    if (frequency > 24 && frequency < 26) {  // Check for ~25 Hz
        PORTC |= (1 << PC6);
        PORTD &= ~(1 << PD0);
    } else if (frequency > 660 && frequency < 665) {  // Check for ~662 Hz
        PORTC &= ~(1 << PC6);
        PORTD |= (1 << PD0);
    } else {
        PORTC &= ~(1 << PC6);
        PORTD &= ~(1 << PD0);
    }
}

int main(void) {
    setup();
    while (1) {
        frequency_detect();
    }
    return 0;
}
