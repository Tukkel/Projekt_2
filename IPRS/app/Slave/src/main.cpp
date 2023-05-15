#include <Arduino.h>
#include <avr/io.h>
#include "X10.h"
#include <stdlib.h>
<<<<<<< HEAD
=======
#include "sensorSlave.h"
#include "uart.h"
#include <string.h>

>>>>>>> 9ae44df1fe67a5153f4625a1740e36b65b240799

/*
#############################################################################################################

=========== Test af X10 kommunikation readData ===========

#############################################################################################################

int main (void)
{

    bool address[8] = {false,false,false,false,false,false,false,true};
    X10 x10(1,2,4, address , 's');
    DDRB = 0xFF;
    while (1){
        bool* data = new bool[100];
        data = x10.readData();

        int j = 0;
        for (int i = 0; i < 100; i++){
            j++;
            if (data[i] == true && data[i - 1] == false && data[i-2] == false && i > 2){
                break;
            }
        }
        uint16_t readData = 0b00000000;
        for (int i = 0; i < j; i++){
            if (data[i] == true)
                readData += pow(2, i);
        }
        PORTB = readData;
    }
}
*/

/*
#############################################################################################################

=========== Test af X10 kommunikation writeData ===========

#############################################################################################################


int main(void){

    bool address[8] = {false,false,false,false,false,false,false,true};
    X10 x10(1<<0, 1<<1, 1<<2, address , 'm');

    while (1)
    {
        bool data[10] = {false};
        data[2] = true;
        x10.writeData(data);
    }
}
*/

/*
#############################################################################################################

=========== Test af aflæsning af data fra sensor ===========

#############################################################################################################
*/


int main(void){
    SensorSlave slave;
    slave.Init_ADC();
    InitUART(9600, 8);
    char c[] = "\n\r";
    uint16_t x;
    while(1)
    {
    x = slave.getSensorInformation();
    SendInteger(x);
    SendString(c);
    _delay_ms(1000);
    }
}