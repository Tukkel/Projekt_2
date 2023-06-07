#include "../slave.h"
#include <avr/io.h>
#include <stdlib.h>
/*
SlaveAktuator er en klasse som bruges til at styre en aktuator.
Klassen bruger X10 kommunikation til at kommunikere med masteren.
Klassen læser data fra masteren og sætter aktuatoren tilsvarende.
Klassens constructor tager parametrene:
outPin: hvilket pin ben som aktuatoren er på
address: en pointer til en uint8_t array med længden 8, som er adressen på enheden, denne er 0 er det en master
logLysStatus: en uint8_t som som indeholder om lyset er tændt eller slukket
*/
class SlaveAktuator : public Slave
{
private:
    uint8_t logLightStatus_;
    int outPin_;

public:
    SlaveAktuator(int outPin, uint8_t *address, uint8_t logLightStatus = false);
    void updateLog();
};
