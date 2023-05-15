#include "../slave.h"

typedef enum sensorType
{
    doorSensor,
    roomSensor,
    idSensor
};
class SlaveSensor : public Slave
{
private:
    bool activity_;
    uint16_t inPin_;
    uint16_t threshold;
    sensorType sType_;
public:
    slaveSensor(int inPin, bool * address, sensorType sType);
    void sendActivity();
    void Init_ADC();
    void updateActivity();
    unsigned int getSensorValue();
};