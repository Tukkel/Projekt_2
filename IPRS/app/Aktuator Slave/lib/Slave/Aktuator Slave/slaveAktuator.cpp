#include "slaveAktuator.h"
#include <util/delay.h>
#include <math.h>

SlaveAktuator::SlaveAktuator(int outPin, uint8_t *addressArray, uint8_t LogLightStatus) : Slave(addressArray)
{

    LogLightStatus_ = LogLightStatus;
    outPin_ = outPin;
    if (LogLightStatus_ == 1)
    {
        PORTB |= (1 << outPin_);
    }
    else
    {
        PORTB &= ~(1 << outPin_);
    }
}

void SlaveAktuator::updateLog()
{
    setNormalPowerUsage();
    DDRB |= (1 << outPin_);
    x10_.readData();
    uint8_t address = x10_.getAddress();

    if (address != slaveNr_)
    {
        setLowPowerUsage();
        return;
    }

    LogLightStatus_ = x10_.getValue();

    if (LogLightStatus_ == 1)
    {
        PORTB |= (1 << outPin_);
    }
    else
    {
        PORTB &= ~(1 << outPin_);
    }
    setLowPowerUsage();
}
