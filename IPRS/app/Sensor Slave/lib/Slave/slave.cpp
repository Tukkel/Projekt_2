#include slave.h

Slave::Slave(bool * address)
{
    address_ = address;
    x10_ = X10(0x01, 0x02, 0x03, address_, 's');
    data_[100] = {false};
}

void Slave::setNormalPowerUsage()
{

}

void Slave::setLowPowerUsage()
{

}