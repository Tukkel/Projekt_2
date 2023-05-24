#include "slaveSensor.h"

SlaveSensor::SlaveSensor(int inPin, bool * address, sensorType sType) : Slave(address)
{
    inPin_ = inPin;
    sType_ = sType;

    if(sType_ == roomSensor)
    {
        threshold_ = 1; //insert value here after test
    }
    else if(sType_ == doorSensor)
    {
        threshold_ = 500;
    }
}

SlaveSensor::sendActivty(){
    setNormalPowerUsage();
    updateActivity();
    x10_.sendData(activity_);
    setLowPowerUsage();
}

// Taget fra MSYS LAB-13 på brightspace
void SlaveSensor::Init_ADC()
{
  // PF pins are inputs (ADC7-ADC0 inputs)
  DDRF = 0;
  // Internal 5 volt reference, ADLAR = 0, Input = ADC0 single ended
  ADMUX = 0b01000000;
  // ADC enable
  // ADC interrupt disabled
  // ADC prescaler = 128 (=> ADC clock = 16 MHz / 128 = 125 kHZ)
  ADCSRA = 0b10000111;  
}


unsigned int SlaveSensor::getSensorValue() const
{
  ADCSRA |= inPin_ << ADSC; // Start conversion

  while(ADCSRA & inPin_ << ADSC){} // Wait for conversion to end

  return ADCW; // Return result
}

void slaveSensor::updateActivity()
{
    activity_ = getSensorValue() > threshold_? true : false;
}

bool slaveSensor::getActivity() const
{
    return activity_;
}

void setNormalPowerUsage()
{

}

void setLowPowerUsage()
{

}