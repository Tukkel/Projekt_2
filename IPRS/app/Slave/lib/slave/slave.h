#pragma once
#include "../X10/X10.h"


class Slave
{
private:
    bool data_[100];
    int address_[8];
    int powerUsage_;
    X10 x10_;

public:
    Slave();
    ~Slave();
    void setNormalPowerUsage(); 
    void setLowPowerUsage();

};