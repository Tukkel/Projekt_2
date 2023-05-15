#include "slave.h"
#pragma once

class SensorSlave : Slave
{
    public:
    SensorSlave();
    ~SensorSlave();
    void Init_ADC();
    unsigned int getSensorInformation() const;
};