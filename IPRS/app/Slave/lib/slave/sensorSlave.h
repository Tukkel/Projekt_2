#include "slave.h"

class SensorSlave : Slave
{
    public:
    void Init_ADC();
    unsigned int getSensorInformation() const;

};