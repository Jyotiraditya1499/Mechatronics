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
    _clockdivide(0);        // Set the system clock to 16 MHz
    m_usb_init();           // Initialize USB communication

    DDRC |= (1 << PC6);  // Set PC6 (OC3A) as OUTPUT

    DDRC &= ~(1 << PC7);  // Set PC7 as INPUT
    PORTC |= (1 << PC7);  //Internal pull-up enabled

    while (1) {
        if (PINC & (1 << PC7)) {   // Light detected
            //PORTC &= ~(1 << PC6);  // Turn OFF LED
            PORTC |= (1 << PC6);   // Turn ON LED
        } else {
            //PORTC |= (1 << PC6);   // Turn ON LED
            PORTC &= ~(1 << PC6);  // Turn OFF LED
        }
    }
    return 0;
}


