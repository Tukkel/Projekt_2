#ifndef PCHANDLER_H
#define PCHANDLER_H

#pragma once
#include "User.h"
#include "Serial.h"
#include "dbHandler.h"
#include <vector>

class PCHandler
{
public:
    // PCHandler(std::string password = "admin");
    PCHandler(User *admin, SerialPort *arduino, dbHandler *dataBase);

    void checkIfInitialised();
    void initialiseOnRestart();
    void showMenu();

    void printData();

    std::vector<std::string> getLog(bool connect = true);
    std::vector<std::string> getLog2();
    std::vector<int> formatLog(bool connect = true);
    void printLog(std::vector<int> log, bool clrScreen = true);
    void printRawData();
    void printSystemInfo();

    void showChangeOptions();
    void addSlave();
    void setRooms();
    void setUsers();
    void selectRoomConnection();
    void selectSaveOnline();

    void calibrateSystem();

    void initialiseSystem();

    void changeLog();
    void updateLog(std::vector<int> log);

    void exit();

    void nextMenu();
    bool isValidRoom(const std::string &input);
    void sendData(const char *sendString);

private:
    int amountOfRooms;
    int amountOfUsers;
    bool running;
    // User user;
    User *userPtr;
    SerialPort *arduino;
    dbHandler *db;
    const char *portName = "\\\\.\\COM3";

    const char *logRequest = "A,LOG\0";
    const char *calibrateRequest = "D,CAL\0";
};

#endif
