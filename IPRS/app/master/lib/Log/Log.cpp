#include "Log.h"

Log::Log(uint8_t numberRooms, uint8_t numberPeople, double** roomHistory)
{
    numberRooms_ = numberRooms;
    numberPeople_ = numberPeople;
    rooms_[numberRooms_][numberPeople_] = {0};
    roomChances_[numberRooms_][numberPeople_] = {0};
    roomHistory_[numberRooms_][numberPeople_] = {0};
    roomNames_[numberRooms_][20];
    peopleNames_[numberPeople_][20];

    size_t historyCols = sizeof(roomHistory[0]);
    size_t historyRows = sizeof(roomHistory)/historyCols;

    size_t cols;
    size_t rows;
    
    if(numberRooms_ < historyCols)
    {
        cols = numberRooms_;
    }
    else
    {
        cols = historyCols;
    }
    
    if(numberPeople_ < historyRows)
    {
        rows = numberPeople_;
    }
    else
    {
        rows = historyRows;
    }

    for(size_t i = 0; i<cols; ++i)
    {
        for(size_t j = 0; j<rows; ++j)
        {
            roomHistory_[i][j] = roomHistory[i][j];
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

void Log::setRoomName(int roomNumber, char* roomName)
{
    if(sizeof(roomName)>20)
    {
        for(size_t i = 0; i<19; ++i)
        {
            roomNames_[roomNumber][i] = roomName[i];
        }
        roomNames_[roomNumber][19] = '\0';
    }
    else
    {
        for(size_t i = 0; i<sizeof(roomName); ++i)
        {
            roomNames_[roomNumber][i] = roomName[i];
        }
    }
}

void Log::setPersonName(int personNumber, char* personName)
{
    if(sizeof(personName)>20)
    {
        for(size_t i = 0; i<19; ++i)
        {
            peopleNames_[personNumber][i] = personName[i];
        }
        peopleNames_[personNumber][19] = '\0';
    }
    else
    {
        for(size_t i = 0; i<sizeof(personName); ++i)
        {
            peopleNames_[personNumber][i] = personName[i];
        }
    }
}

void Log::setAddress(size_t address, uint32_t addressType)
{
    if(address < 256)
    {
        addresses_[address] = addressType; 
    }
}

void Log::logActivity(size_t roomNumber)
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
    else if(sum < 0.05)
    {
        
    }
}

void Log::logMovement(size_t roomNumber1, size_t roomNumber2)
{

}