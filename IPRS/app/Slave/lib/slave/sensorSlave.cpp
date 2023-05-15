#include "sensorSlave.h"

//  HUGGET FRA MSYS LAB-ØVELSE 13 LØSNINGSFORSLAG
SensorSlave::SensorSlave()
{

}
SensorSlave::~SensorSlave()
{

}

void SensorSlave::Init_ADC()
{
  // PF pins are inputs (ADC7-ADC0 inputs)
  DDRF = 0;
  // Internal 5 volt reference, ADLAR = 0, Input = ADC0 single ended (potentiometer)
  ADMUX = 0b01000000;
  // ADC enable
  // ADC interrupt disabled
  // ADC prescaler = 128 (=> ADC clock = 16 MHz / 128 = 125 kHZ)
  ADCSRA = 0b10000111;  
}

unsigned int SensorSlave::getSensorInformation() const
{
    ADCSRA |= 1 << ADSC; // Start conversion

    while(ADCSRA & 1 << ADSC) // Wait for conversion to end
    {}

    return ADCW; // Return result
}
