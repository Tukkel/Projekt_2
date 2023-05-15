#include "slaveAktuator.h"

slaveAktuator::slaveAktuator(int outpin, bool *address, bool logLysStatus) : Slave(address)
{
    logLysStatus_ = logLysStatus;
    int outpin_ = outpin;
}

slaveAktuator::opdaterLog()
{
    setNormalPowerUsage();
    DDRB =| (1<<outpin_) ;
    x10_.readData();
    if (x10.getAdress() != address_)
    {
        setLowPowerUsage();
        return;
    }
    logLysStatus_ = x10_.getData();
    if (logLysStatus_)
    {
        PORTB =| (1<<outpin_);
    }
    else
    {
        PORTB = &~(1<<outpin_);
    }
    setLowPowerUsage();
}
