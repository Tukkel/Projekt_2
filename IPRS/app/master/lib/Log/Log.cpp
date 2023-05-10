#include "Log.h"

Log::Log(uint8_t numberRooms, uint8_t numberPeople, double** roomHistory)
{
    rooms_[numberRooms][numberPeople] = {0};
    roomChances_[numberRooms][numberPeople] = {0};
    roomHistory_[numberRooms][numberPeople] = {0};
    roomNames_[numberRooms][20];
    peopleNames_[numberPeople][20];

    size_t historyCols = sizeof(roomHistory[0]);
    size_t historyRows = sizeof(roomHistory)/historyCols;

    size_t cols;
    size_t rows;
    
    if(numberRooms < historyCols)
    {
        cols = numberRooms;
    }
    else
    {
        cols = historyCols;
    }
    
    if(numberPeople < historyRows)
    {
        rows = numberPeople;
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

    for(size_t i = 0; i<numberRooms; ++i)
    {
        roomNames_[i][0] = 'N';
        roomNames_[i][1] = 'a';
        roomNames_[i][2] = 'N';
        roomNames_[i][4] = '\0';
    }

    for(size_t i = 0; i<numberPeople; ++i)
    {
        peopleNames_[i][0] = 'N';
        peopleNames_[i][1] = 'a';
        peopleNames_[i][2] = 'N';
        peopleNames_[i][4] = '\0';
    }
}