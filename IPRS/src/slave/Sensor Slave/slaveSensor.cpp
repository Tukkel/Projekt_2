#include "sensorSlave.h"

sensorSlave::sensorSlave(int inPin, bool * address, bool activity) : Slave(address)
{
    activity_ = activity;
    inPin_ = inPin;
}

sensorSlave::sendActivty(){
    setNormalPowerUsage();
    x10_.sendData(activity_);
    setLowPowerUsage();
}