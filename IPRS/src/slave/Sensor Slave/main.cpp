#include "slaveSensor.h"

int main(void)
{
    bool address = false;
    SlaveSensor s(1, address, roomSensor);
}