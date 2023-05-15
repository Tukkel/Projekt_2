#include "slaveAktuator.h"

slaveAktuator::slaveAktuator(int outPin, uint8_t * address, uint8_t logLysStatus): Slave(address)
{
    logLysStatus_ = logLysStatus;
    outPin_ = outPin;
}

void slaveAktuator::opdaterLog()
{
    setNormalPowerUsage();
    DDRB |= (1<<outPin_) ;
    x10_.readData();
    uint16_t address;
    for (size_t i = 0; i < sizeof(address_); i++)
    {
        address += pow(2, i) * address_[i];
    }
    if (x10_.getAddress() != address)
    {
        setLowPowerUsage();
        return;
    }
    logLysStatus_ = x10_.getValue();
    if (logLysStatus_)
    {
        PORTB |= (1<<outPin_);
    }
    else
    {
        PORTB &= ~(1<<outPin_);
    }
    setLowPowerUsage();
}
