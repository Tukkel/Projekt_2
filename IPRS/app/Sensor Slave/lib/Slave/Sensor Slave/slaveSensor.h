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
};