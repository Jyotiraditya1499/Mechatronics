/* Name: main.c
 * Project: Lab 2 2.1.1
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/


#include "MEAM_general.h"
#include "m_usb.h"


int main(){
    m_usb_init();
    _clockdivide(0);  // Set the system clock speed to 16 MHz

    DDRC |= (1 << PC6);  // Set PC6 (OC3A) as OUTPUT

    DDRC &= ~(1 << PC7);  // Set PC7 as INPUT
    PORTC |= (1 << PC7);  //Internal pull-up enabled


    while (1)
    {
        if (!(PINC & (1 << PC7)))
        {
            PORTC |= (1 << PC6);
        } else
        {
            PORTC &= ~(1 << PC6);
        }
    }

}