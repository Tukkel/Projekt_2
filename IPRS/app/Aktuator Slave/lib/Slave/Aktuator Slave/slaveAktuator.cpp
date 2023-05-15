#include "slaveAktuator.h"
#include <util/delay.h>
#include <math.h>
slaveAktuator::slaveAktuator(int outPin, uint8_t* addressArray, uint8_t logLysStatus): Slave(addressArray)
{
    slaveNr_ = 0;
    for(size_t i=0; i < 8;i++)
    {
        slaveNr_ += addressArray[7-i]<<i;
    }
    logLysStatus_ = logLysStatus;
    outPin_ = outPin;
}

void slaveAktuator::opdaterLog()
{
    setNormalPowerUsage();
    DDRB |= (1<<outPin_) ;
    x10_.readData();
    uint8_t address = x10_.getAddress();
    
    if (address == slaveNr_)
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
