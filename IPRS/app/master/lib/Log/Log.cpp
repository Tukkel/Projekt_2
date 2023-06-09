#include "Log.h"

Log::Log(uint8_t numberRooms, size_t numberPeople) : numberRooms_(numberRooms), numberPeople_(numberPeople)
{
    _delay_ms(100);
    rooms_[numberRooms_][numberPeople_] = {false};
    roomChances_[numberRooms_][numberPeople_] = {0};
    peopleHistory_[numberRooms_][numberPeople_] = {0};
    roomConnections_[numberRooms_][numberRooms_] = {false};
    roomNames_[numberRooms_][15];
    peopleNames_[numberPeople_][16];
    nextEntry_ = 0;
    timeMin_ = 0;

    PORTB = 2;

    logTime_[100] = {0};
    log_[numberRooms_*numberPeople_*100] = {0};

    for(size_t i = 0; i<numberRooms_; ++i)
    {
        for(size_t j = 0; j<numberRooms_; ++j)
        {
            peopleHistory_[i][j] = 1/(double)numberRooms_;
        }
    }

    for(size_t i = 0; i<numberRooms_; ++i)
    {
        roomNames_[i][0] = 'N';
        roomNames_[i][1] = 'a';
        roomNames_[i][2] = 'N';
        roomNames_[i][4] = '\0';
    }

    for(size_t i = 0; i<numberPeople_; ++i)
    {
        peopleNames_[i][0] = 'N';
        peopleNames_[i][1] = 'a';
        peopleNames_[i][2] = 'N';
        peopleNames_[i][4] = '\0';
    }

    
}

void Log::setRoomConnection(uint8_t roomNumber, bool* connections)
{
    if(sizeof(connections) < numberRooms_)
    {
        for(size_t i = 0; i<sizeof(connections) ; ++i)
        {
            roomConnections_[roomNumber][i] = connections[i];
        }
    }
    else
    {
        for(size_t i = 0; i<numberRooms_ ; ++i)
        {
            roomConnections_[roomNumber][i] = connections[i];
        }
    }
}

void Log::setPersonHistory(size_t personNumber, double* personHistory)
{
    if(sizeof(personHistory) < numberRooms_)
    {
        for(size_t i = 0; i<sizeof(personHistory); ++i)
        {
            peopleHistory_[i][personNumber] = personHistory[i];
        }
    }
    else
    {
        for(size_t i = 0; i<numberRooms_ ; ++i)
        {
            peopleHistory_[i][personNumber] = personHistory[i];
        }
    }
}

void Log::setRoomName(uint8_t roomNumber, char* roomName)
{
    if(strlen(roomName)>16)
    {
        for(size_t i = 0; i<16; ++i)
        {
            roomNames_[roomNumber][i] = roomName[i];
        }
        roomNames_[roomNumber][16] = '\0';
    }
    else
    {
        for(size_t i = 0; i<strlen(roomName); ++i)
        {
            roomNames_[roomNumber][i] = roomName[i];
        }
        roomNames_[roomNumber][strlen(roomName)] = '\0';
    }
}

void Log::setPersonName(size_t personNumber, char* personName)
{
    if(strlen(personName)>16)
    {
        for(size_t i = 0; i<16; ++i)
        {
            peopleNames_[personNumber][i] = personName[i];
        }
        peopleNames_[personNumber][16] = '\0';
    }
    else
    {
        for(size_t i = 0; i<strlen(personName); ++i)
        {
            peopleNames_[personNumber][i] = personName[i];
        }
        peopleNames_[personNumber][strlen(personName)] = '\0';
    }
}

void Log::setAddress(uint8_t address, uint32_t addressType)
{
    if(address < 256)
    {
        addresses_[address] = addressType; 
    }
}

void Log::logActivity(uint8_t roomNumber)
{
    double sum = 0;
    for(size_t i=0; i<numberPeople_; ++i)
    {
        sum += roomChances_[roomNumber][i];
    }

    if(sum >= 1)    //If expecting to have people do nothing
    {
        return;
    }
    else if((roomNumber <= 0) && (sum < 0.05))  //If entrance has activity and is empty expect someone new entered
    {
        bool peopleAbsent[numberPeople_] = {false};
        size_t numberAbsent = 0;
        double personSum;

        for(size_t i = 0; i<numberPeople_; ++i)
        {
            personSum = 0;
            for(size_t j = 0; j<numberRooms_; ++j)
            {
                personSum += roomChances_[j][i];
            }
            if(personSum < 0.05)
            {
                peopleAbsent[i] = true;
                ++numberAbsent;
            }
        }

        for(size_t i = 0; i<numberPeople_; ++i)
        {
            if(peopleAbsent[i])
            {
                roomChances_[roomNumber][i] += 1/numberAbsent;
            }
        }
    }
    else if(sum < 1)
    {
        double adjacentSum = 0;
        for(size_t i = 0; i<numberRooms_; ++i)
        {
            if(roomConnections_[roomNumber][i])
            {
                for(size_t j = 0; j<numberPeople_; ++j)
                {
                    adjacentSum += roomChances_[i][j];
                }
            }
        }
        for(size_t i = 0; i<numberRooms_; ++i)
        {
            if(roomConnections_[roomNumber][i])
            {
                for(size_t j = 0; j<numberPeople_; ++j)
                {
                    roomChances_[i][j] -= (roomChances_[i][j]/adjacentSum)*sum;
                    roomChances_[roomNumber][j] += (roomChances_[i][j]/adjacentSum)*sum;
                }
            }
        }
    }
    //setLog();
}

void Log::logMovement(uint8_t roomNumber1, uint8_t roomNumber2)
{
    double room1Sum = 0;
    for(size_t i = 0; i<numberPeople_; ++i)
    {
        room1Sum += roomChances_[roomNumber1][i];
    }
    for(size_t i = 0; i<numberPeople_; ++i)
    {
        roomChances_[roomNumber1][i] -= roomChances_[roomNumber1][i]/room1Sum;
        roomChances_[roomNumber2][i] += roomChances_[roomNumber1][i]/room1Sum;
    }
    //setLog();
}

void Log::logID(uint8_t roomNumber, size_t personNumber)
{
    for(size_t i = 0; i<numberRooms_; ++i)
    {
        roomChances_[i][personNumber] = 0.0;
    }
    roomChances_[roomNumber][personNumber] = 1.0;
    //setLog();
}

void Log::setTime(size_t timeMin)
{
    timeMin_ = timeMin;
}

size_t Log::offset(size_t logNumber, size_t roomNumber, size_t personNumber)
{
    return (logNumber*numberRooms_*numberPeople_) + (personNumber*numberRooms_) + roomNumber;
}

void Log::setLog()
{
    if(nextEntry_ >= 100)
    {
        nextEntry_ = 0;
    }

    for(size_t i=0; i<numberRooms_; ++i)
    {
        for(size_t j=0; j<numberPeople_; ++j)
        {
            log_[offset(nextEntry_, i, j)] = roomChances_[i][j];
        }
    }

    logTime_[nextEntry_] = timeMin_;

    ++nextEntry_;
}