#include "slaveSensor.h"


SlaveSensor::SlaveSensor(int inPin, uint8_t * address, sensorType sType) : Slave(address)
{
    inPin_ = inPin;
    sType_ = sType;

    // Init ADC
    DDRF = 0;
    ADMUX = 0b01000000;
    ADCSRA = 0b10000111;    
}

void SlaveSensor::calibrate(){
    if (sType_ != idSensor){
        uint64_t sum = 0;
        for (int i = 0; i < 1000; i++)
        {
            sum += getSensorValue();
        }
        threshold_ = sum / 1000; 
    }
}

void SlaveSensor::sendActivity(){
    setNormalPowerUsage();
    x10_.writeData(&activity_, sizeof(activity_), address_, sizeof(address_));
    activity_ = false;
    setLowPowerUsage();
}

unsigned int SlaveSensor::getSensorValue() const
{
    if (sType_ == idSensor){
        return 0;
    }       
    ADCSRA |= inPin_ << ADSC; // Start conversion

    while(ADCSRA & inPin_ << ADSC){} // Wait for conversion to end

    return ADCW; // Return result
}

void SlaveSensor::updateActivity()
{
    if (sType_ != idSensor){
        uint16_t value = getSensorValue();
        uint16_t range = 0;
        if (sType_ == doorSensor)
        {
            range = 30;

        }
        else if (sType_ == roomSensor)
        {
            range = 15;
        }

        if (value + range > threshold_ && value - range < threshold_){
            activity_ = false;
        }
        else{
            activity_ = true;
        }
    }
}


bool SlaveSensor::getActivity() const
{
    return activity_;
}

void SlaveSensor::updateIds(){
    DDRA = 0x00;
    int input = 255 - PINA;
    int temp = 0;

    for (int i = 0; i < sizeof(ids_)/sizeof(ids_[0]); i++)
    {
        temp = 1<<i;
        if (temp == input){
            ids_[i] = 1;
            break;
        }
    }
}

void SlaveSensor::sendIds(){
    setNormalPowerUsage();
    x10_.writeData(ids_, sizeof(ids_), address_, sizeof(address_));
    for (size_t i = 0; i < sizeof(ids_)/sizeof(ids_[0]); i++)
    {
        ids_[i] = 0;
    }
    setLowPowerUsage();
}

uint8_t SlaveSensor::getIds() const{
    uint8_t ids = 0;
    for (size_t i = 0; i < sizeof(ids_)/sizeof(ids_[0]); i++)
    {
        ids += ids_[i] << i;
    }
    
    return ids;
}