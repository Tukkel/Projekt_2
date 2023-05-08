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
        if(i < historyCols)
        {
            for(size_t j = 0; j<rows; ++j)
            {
                if(j < historyCols)
                {  
                    roomHistory_[i][j] = roomHistory[i][j];
                }
            }
        }
        
    }
}