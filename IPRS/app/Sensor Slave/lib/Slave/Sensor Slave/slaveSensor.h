#include "../slave.h"

typedef enum sensorType
{
    doorSensor,
    roomSensor,
    idSensor
};

/*
SlaveSensor Klasse
Denne klasse er en subklasse af Slave klassen. Denne klasse er lavet til at håndtere sensorer.
SlaveSensor bruger en analog pin til at læse værdien af sensoren. Denne værdi bliver brugt til at
bestemme om sensoren er aktiv eller ej. Denne klasse kan også bruges til at sende en liste af id'er
til masteren. Denne liste bliver brugt til at bestemme hvilke personer er i rummet.
Klassen bruger X10 klassen til at kommunikere med masteren.
Klassen bruger også en enum til at bestemme hvilken type sensor der er tale om.

Klassen bruger DDRA til at læse id'erne fra personer i rummet.
Klassen Bruger DDRF til at læse værdien af sensoren.

Klassen tager følgende parametre:
    - inPin:    Denne parameter er den pin som sensoren er tilsluttet.
    - address:  Denne parameter er adressen på sensoren.
    - sType:    Denne parameter er typen af sensoren.

*/
class SlaveSensor : public Slave
{
private:
    uint8_t activity_;
    uint16_t inPin_;
    uint16_t threshold_;
    uint8_t ids_[8] = {0};
    sensorType sType_;
public:
    SlaveSensor(int inPin, uint8_t * address, sensorType sType);
    void sendActivity();
    bool getActivity() const;
    void updateIds();
    void sendIds();
    uint8_t getIds() const;
    void updateActivity();
    void calibrate();
    unsigned int getSensorValue() const;
    bool dataRequested();
};