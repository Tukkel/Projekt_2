#include "slave.h"

Slave::Slave(uint8_t * address) : x10_(0x01, 0x02, 0x04, address, 's')
{

    for(size_t i=0; i < 8;i++)
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