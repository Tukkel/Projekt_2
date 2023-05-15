#include "../slave.h"

class slaveSensor : public Slave
{
private:
    bool activity_;
    int inPin_;

public:
    slaveSensor(int inPin, bool * address, bool activity = false);
    void sendActivity();
};