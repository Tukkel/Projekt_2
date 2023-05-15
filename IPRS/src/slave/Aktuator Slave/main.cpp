#include <Arduino.h>
#include <avr/io.h>
#include <stdlib.h>
#include "slaveAktuator.h"

int main(void){

    bool adress[8] = {false,false,false,false,false,false,false,true};
    slaveAktuator slaveAktuator(1, adress);
    while(1){
        slaveAktuator.opdaterLog();
    }
}