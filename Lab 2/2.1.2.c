/* Name: main.c
 * Project: Lab 2 2.1.2
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/


#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#include "m_usb.h"

int main(void) {
    _disableJTAG();         //disable fuse if using PORTF
    _clockdivide(0);        // Set the system clock speed to 16 MHz
    m_usb_init();           // Initialize USB communication
    
    DDRC |= (1 << PC6);     // Set PC6 (OC3A) as OUTPUT
    
    DDRC &= ~(1 << PC7);  // Set PC7 as INPUT
    PORTC |= (1 << PC7);  // Internal pull-up enabled
    
    TCCR3B = (1 << CS32) | (1 << CS30);    // Set prescaler to 1024
    
    // Store initial switch state
    int prev_state = PINC & (1 << PC7);
    
    while(1) {
        // Read current switch state
        int current_state = PINC & (1 << PC7);
        
        // Check if state has changed
        if(current_state != prev_state) {
            
            m_usb_tx_uint(TCNT3);   // Transmit Timer3 count over USB
            m_usb_tx_string("\n");  // Print timer value
            
            // Update LED state
            if(!(PINC & (1 << PC7)))   // Switch is pressed (active low)
            {    
                PORTC |= (1 << PC6);   // Turn LED on
            } else                     // Switch is released
            {                
                PORTC &= ~(1 << PC6);  // Turn LED off
            }
            
            // Update previous state
            prev_state = current_state;
        }
    }
    
    return 0;
}
