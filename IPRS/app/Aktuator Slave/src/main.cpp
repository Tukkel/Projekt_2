// includes
#include <avr/io.h>
#include <stdlib.h>
#include "./Aktuator Slave/slaveAktuator.h"
#define F_CPU 16000000
// main
int main(void){
    // slave adresse sættes
    uint8_t adress[8] = {0};
    adress[7] = 1; // slave nr 1

    slaveAktuator slave1(0, adress); // slaveAktuator oprettes
    while(1){ // uendelig loop som opdaterer loggen og dermed lyset
        slave1.opdaterLog(); 
    }
}