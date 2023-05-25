#include "./Sensor Slave/slaveSensor.h"
#include <avr/io.h>


// Main program for dør eller rum sensor
/* int main(void){
    DDRB = 0xFF;
    uint8_t address[8] = {false};
    address[7] = true;
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
} */

//Main program for id sensor
int main(void){
    DDRB = 0xFF;
    uint8_t address[8] = {false};
    address[7] = true;
    SlaveSensor s(1, address, idSensor);
    s.calibrate();

    while (1)
    {
        s.updateIds();
        while(s.getActivity()){
            if (s.dataRequested()){
                s.sendIds();
            }
        }
    }
}
