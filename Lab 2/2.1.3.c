/* Name: main.c
 * Project: Lab 2 2.1.3
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/

#include "MEAM_general.h"  // Includes system configurations
#include "m_usb.h"

int main(void) {
    _disableJTAG();         // Disable JTAG to use PORTF
    _clockdivide(0);        // Set the system clock speed to 16 MHz
    m_usb_init();           // Initialize USB communication

    DDRC |= (1 << PC6);     // Set PC6 (LED) as OUTPUT
    DDRC &= ~(1 << PC7);    // Set PC7 (Button) as INPUT
    PORTC |= (1 << PC7);    // Enable internal pull-up resistor for PC7

    TCCR3B = (1 << CS32) | (1 << CS30);  // Set Timer3 prescaler to 1024
    TCCR3B |= (1 << ICES3);              // Input capture on rising edge

    
    DDRC &= ~(1 << PC7);  // Set PC7 as input for switch with internal pull-up enabled
    PORTC |= (1 << PC7);

    int first_press_time = 0;
    int second_press_time = 0;
    int press_count = 0;

    while (1) {
        while (press_count < 2) {
            // Check if input capture flag is set
            if (TIFR3 & (1 << ICF3)) {
                if (press_count == 0) {
                    first_press_time = ICR3;  // Capture first press time
                    m_usb_tx_string("1st: ");
                    m_usb_tx_uint(first_press_time);
                    m_usb_tx_string(".\n");
                    
                    press_count = 1;
                    
                    // Switch to detecting falling edge
                    TCCR3B &= ~(1 << ICES3);
                } else if (press_count == 1) {
                    second_press_time = ICR3;  // Capture second press time
                    m_usb_tx_string("2nd: ");
                    m_usb_tx_uint(second_press_time);
                    m_usb_tx_string(".\n");

                    press_count = 2;
                }

                TIFR3 |= (1 << ICF3);  // Clear input capture flag
            }
        }

        float time_between_presses = (second_press_time - first_press_time) * 1000.0 / 15625.0;  // Calculate time between presses in milliseconds

        m_usb_tx_string("Time between presses: ");
        m_usb_tx_uint((int)time_between_presses);
        m_usb_tx_string(" ms\n");

        _delay_ms(10);  // Wait before restarting to ensure USB data is sent

        press_count = 0;  // Reset press count for next measurement
        
        TCCR3B |= (1 << ICES3);  // Reset input capture to detect rising edge again
    }

    return 0;
}
