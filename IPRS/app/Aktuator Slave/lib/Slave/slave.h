#include "../X10/X10.h"

class Slave
{
protected:
    uint8_t data_[100];
    uint8_t address_[8];
    X10 x10_;
public:
    Slave(uint8_t * address);
    void setNormalPowerUsage(); 
    void setLowPowerUsage();
};