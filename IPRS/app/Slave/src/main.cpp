#include <Arduino.h>
#include <avr/io.h>
#include "X10.h"
#include <stdlib.h>




/*
#############################################################################################################

=========== Test af X10 kommunikation readData ===========

#############################################################################################################

int main (void)
{

    bool address[8] = {false,false,false,false,false,false,false,true};
    X10 x10(1,2,4, address , 's');
    DDRB = 0x00;
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

    bool address[8] = {false,false,false,false,false,false,false,false};
    X10 x10(1,2,4, address , 'm');

    while (1)
    {
        bool data[10] = {false};
        data[0] = true;
        x10.writeData(data);
    }
}
*/

/*
#############################################################################################################

=========== Test af X10 kommunikation writeData ===========

#############################################################################################################
*/

int main(void){

    DDRA = 0;
}