#include "../slave.h"

class slaveAktuator : public Slave
{
private:
    bool logLysStatus_;
    int outpin_;
public:
    slaveAktuator(int * address, bool logLysStatus = false);
    opdaterLog();
};


