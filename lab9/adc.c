#include <avr/io.h>

#include "adc.h"

#define MASK 0x0f


void adc_init(void)
{
    // Initialize the ADC
    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1);

    ADMUX |= (1 << ADLAR);
    
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADEN); // Prescalar of 128

}

uint8_t adc_sample(uint8_t channel)
{
    // Set ADC input mux bits to 'channel' value
    ADMUX &= ~MASK;
    ADMUX |= (MASK & channel);
    
    ADCSRA |= (1<<ADSC);

    while (((ADCSRA & (1 << ADSC)))){}
    unsigned char result = ADCH;

    return result;
}
