#include "./Sensor Slave/slaveSensor.h"
#include <avr/io.h>

int main(void){
    DDRB = 0xFF;
    uint8_t address[8] = {false};
    address[6] = true;
    SlaveSensor s(1, address, doorSensor);
    s.calibrate();

    while (1)
    {
        s.updateActivity();
        while(s.getActivity()){
            if (s.dataRequested()){
                s.sendActivity();
            }
        }
    }
}