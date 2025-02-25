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



// #include "MEAM_general.h"
// #include "m_usb.h"

// volatile uint16_t first_capture = 0;
// volatile uint16_t second_capture = 0;
// volatile uint16_t pulse_duration = 1;  // Avoid division by zero

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

// // // **Input Capture Interrupt Service Routine (ISR)**
// // ISR(TIMER1_CAPT_vect) {
// //     first_capture = second_capture;  // Shift the last capture
// //     second_capture = ICR1;  // Store new capture
// //     pulse_duration = second_capture - first_capture;  // Compute pulse duration
// // }

// ISR(TIMER1_CAPT_vect) {
//     first_capture = second_capture;  // Store previous capture first
//     second_capture = ICR1;  // Store new capture
//     if (first_capture != 0) {  // Prevent calculation errors on first pulse
//         pulse_duration = second_capture - first_capture;
//     }
// }


// // **Detect and Process Frequency**
// void frequency_detect() {

//     float frequency = 250000.0 / pulse_duration;  // Frequency calculation

//     // USB Output
//     //m_usb_tx_string("Frequency: ");
//     m_usb_tx_int((int)frequency);
//     //m_usb_tx_string(".");
//     //m_usb_tx_int(((int)(frequency * 100)) % 100);  // Two decimal places
//     m_usb_tx_string(" Hz\n");

//     // LED Logic
//     if (frequency > 24 && frequency < 26) {  // Check for ~25 Hz
//         PORTC |= (1 << PC6);
//         PORTD &= ~(1 << PD0);
//     } else if (frequency > 660 && frequency < 665) {  // Check for ~662 Hz
//         PORTC &= ~(1 << PC6);
//         PORTD |= (1 << PD0);
//     } else {
//         PORTC &= ~(1 << PC6);
//         PORTD &= ~(1 << PD0);
//     }
// }

// int main(void) {
//     setup();
//     while (1) {
//         if (pulse_duration > 0)
//         {
//             frequency_detect();
            
//         }
//         else
//         {
//             PORTC &= ~(1 << PC6);
//             PORTD &= ~(1 << PD0);
//         }
        
        
//     }
//     return 0;
// }


#include "MEAM_general.h"

#include "m_usb.h"

volatile uint16_t first_capture = 0;
volatile uint16_t second_capture = 0;
volatile uint16_t pulse_duration = 1;  // Avoid division by zero
volatile uint8_t timeout_flag = 0;  // Tracks if a timeout occurs

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

    //  Configure Timer1 with 256 prescaler (16MHz / 256 = 62.5 kHz)
    TCCR1B |= (1 << CS12);  
    TCCR1B |= (1 << ICES1);  // Start capturing on rising edge
    TIMSK1 |= (1 << ICIE1);  // Enable input capture interrupt
    TIMSK1 |= (1 << TOIE1);  // Enable overflow interrupt for timeout

    sei();  // Enable global interrupts
}

// **ISR for Input Capture**
ISR(TIMER1_CAPT_vect) {
    first_capture = second_capture;  // Store previous capture
    second_capture = ICR1;  // Store new capture

    if (first_capture != 0) {  // Prevent errors on first pulse
        if (second_capture >= first_capture) {
            pulse_duration = second_capture - first_capture;
        } else {
            pulse_duration = (65536 - first_capture) + second_capture;  // Handle overflow case
        }
    }
    timeout_flag = 0;  // Reset timeout flag (signal detected)
}

// **ISR for Timer Overflow (Timeout)**
ISR(TIMER1_OVF_vect) {
    timeout_flag = 1;  // Mark timeout if no signal received
}

// **Detect and Process Frequency**
void frequency_detect() {
    uint16_t safe_pulse_duration;
    cli();  // Disable interrupts to safely read pulse_duration
    safe_pulse_duration = pulse_duration;
    sei();  // Re-enable interrupts

    if (timeout_flag) {  // If no signal received for too long, reset everything
        pulse_duration = 1;  // Prevent divide-by-zero
        PORTC &= ~(1 << PC6);
        PORTD &= ~(1 << PD0);
        return;  // Skip further calculations
    }

    if (safe_pulse_duration > 0) {  // Prevent divide-by-zero
        float frequency = 62500.0 / safe_pulse_duration;  // Corrected calculation

        // USB Output
        m_usb_tx_int((int)frequency);
        m_usb_tx_string(" Hz\n");

        // LED Logic
        if (frequency > 24 && frequency < 26) {  // ~25 Hz
            PORTC |= (1 << PC6);
            PORTD &= ~(1 << PD0);
        } else if (frequency > 660 && frequency < 665) {  // ~662 Hz
            PORTC &= ~(1 << PC6);
            PORTD |= (1 << PD0);
        } else {
            PORTC &= ~(1 << PC6);
            PORTD &= ~(1 << PD0);
        }
    }
}

int main(void) {
    setup();
    while (1) {
        frequency_detect();
    }
    return 0;
}

