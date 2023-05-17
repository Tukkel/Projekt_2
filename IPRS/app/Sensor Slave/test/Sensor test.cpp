#include "./Sensor Slave/slaveSensor.h"
#include <avr/io.h>
#include <util/delay.h>
/*
====================================================================================================
    Test of SlaveSensor class for a room sensor

====================================================================================================

int main(void)
{
    uint8_t address[8] = {false};
    SlaveSensor s(1, address, roomSensor);
    DDRB = 0xFF;
    s.calibrate();
    while(1)
    {
        s.updateActivity();
        PORTB = s.getActivity() ? 0xFF : 0x00;
        _delay_ms(1000);
    }
}
*/

/*
====================================================================================================
    Test of SlaveSensor class for a door sensor

====================================================================================================

int main(void)
{
    uint8_t address[8] = {false};
    SlaveSensor s(1, address, doorSensor);
    DDRB = 0xFF;
    s.calibrate();
    while(1)
    {
        s.updateActivity();
        PORTB = s.getActivity() ? 0xFF : 0x00;
        _delay_ms(1000);
    }
}
*/

/*
====================================================================================================
    Test of SlaveSensor class for a id sensor

====================================================================================================
*/
int main(void)
{
    uint8_t address[8] = {false};
    SlaveSensor s(1, address, idSensor);
    DDRB = 0xFF;    
    s.calibrate();
    while(1)
    {
        s.updateIds();
        PORTB = s.getIds();
        _delay_ms(1000);
    }
}