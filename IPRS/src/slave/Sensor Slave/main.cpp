#include "slaveSensor.h"

int main(void)
{
    bool address = {false, false, false, false, false, false, false, true};
    SlaveSensor s(1, address, roomSensor);
}