/* Name: main.c
 * Project: Lab 2 2.1.2
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/


#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#include "m_usb.h"

int main(void) {
    _disableJTAG();         // Disable fuse if using PORTF
    _clockdivide(0);        // Set the system clock speed to 16 MHz
    m_usb_init();           // Initialize USB communication
    
    DDRC |= (1 << PC6);     // Set PC6 (OC3A) as OUTPUT
    
    DDRC &= ~(1 << PC7);    // Set PC7 as INPUT
    PORTC |= (1 << PC7);    // Internal pull-up enabled
    
    TCCR1B = (1 << CS12) | (1 << CS10);  // Set Timer1 prescaler to 1024
    TCCR1B |= (1 << ICES1);  // Input capture on rising edge
    
    int first_press = 0;
    int second_press = 0;
    int press_count = 0;
    int prev_state = PINC & (1 << PC7);
    
    while(1) {
        int current_state = PINC & (1 << PC7);
        
        if ((prev_state != current_state) && !(current_state)) {  // Button pressed (active low)
            if (press_count == 0) {
                first_press = ICR1;  // Capture first press time
                press_count++;
            } else {
                second_press = ICR1;  // Capture second press time
                int time_diff = second_press - first_press;
                m_usb_tx_string("Time between presses: ");
                m_usb_tx_uint(time_diff);
                m_usb_tx_string("\n");
                first_press = second_press;  // Reset first press time
            }
        }
        prev_state = current_state;
    }
    return 0;
}

