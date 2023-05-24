#include "slave.h"

Slave::Slave(uint8_t * address, uint8_t addressSize) : x10_(0x01, 0x02, 0x04, address, addressSize, 's')
{
    slaveNr_ = 0;
    for(size_t i=0; i < addressSize;i++)
    {
        slaveNr_ += address[7-i]<<i;
    }
    for(size_t i=0; i < addressSize;i++)
    {
        address_[i] = address[i];
    }
    data_[100] = {false};
}

void Slave::setNormalPowerUsage()
{

}

void Slave::setLowPowerUsage()
{

}