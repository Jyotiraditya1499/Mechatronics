/* Name: main.c
 * Project: Lab 3 3.1.3
 * Author: Jyotiraditya
 * Copyright: Jyotiraditya Ingawale - All Rights Reserved
 * License: You may use, distribute and modify this code under the terms of the GNU GPLv3.0 license.
*/

 // two servos using two potentiometer inputs

#include "MEAM_general.h"
#include "m_usb.h"

void setup()
{
    // Set Pin 9 (OC1A) and Pin 10 (OC1B) as outputs
    DDRB |= (1 << PB5) | (1 << PB6);

    // Configure Timer1 in Fast PWM Mode 14 (ICR1 as TOP)
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11); // OC1A & OC1B Fast PWM, non-inverting mode
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);    // Fast PWM, Prescaler = 8

    ICR1 = 40000; // Set TOP value for 50Hz (20ms period)

    // ADC Setup
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1); // Enable ADC, Start conversion, Prescaler = 64

    m_usb_init(); // Initialize USB for debugging
}

uint16_t read_adc(uint8_t channel)
{
    ADMUX = (1 << REFS0) | (channel & 0x0F); // Select ADC channel
    ADCSRA |= (1 << ADSC);                   // Start ADC conversion
    while (ADCSRA & (1 << ADSC));       // Wait for conversion to complete
    return ADC; // Return 10-bit ADC result (0-1023)
}

void loop()
{

    // Read potentiometer values
    uint16_t adc_value1 = read_adc(7); // Read from A0 (Servo 1)
    uint16_t adc_value2 = read_adc(1); // Read from A4 (Servo 2)

    // Map ADC values to PWM pulse width (1000 to 5000)
    uint16_t servo_pulse1 = 1000 + ((uint32_t)adc_value1 * 4000) / 1023;
    uint16_t servo_pulse2 = 1000 + ((uint32_t)adc_value2 * 4000) / 1023;

    // Set OCR1A and OCR1B for respective servos
    OCR1A = servo_pulse1; // Control Servo 1
    OCR1B = servo_pulse2; // Control Servo 2

    m_usb_tx_string("ADC 1: ");
    m_usb_tx_uint(adc_value1);
    m_usb_tx_string("\tServo Pulse: ");
    m_usb_tx_uint(servo_pulse1);
    m_usb_tx_string("\tADC 2: ");
    m_usb_tx_uint(adc_value2);
    m_usb_tx_string("\tServo Pulse: ");
    m_usb_tx_uint(servo_pulse2);
    m_usb_tx_string("\n");

    _delay_ms(20); // Small delay for stability
}

void main()
{
    setup();

    while (1)
    {
        loop();
    }
}
