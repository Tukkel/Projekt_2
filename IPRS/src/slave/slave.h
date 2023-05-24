#include "../X10/X10.h"

class Slave
{
private:
    bool data_[100];
    bool address_[8];
    X10 x10_;

public:
    Slave(bool * address);
    void setNormalPowerUsage(); 
    void setLowPowerUsage();
};