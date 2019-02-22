#ifndef APPCLI_HPP
#define APPCLI_HPP

#include <string>
#include "../DB/DatabaseInterface.hpp"
#include "../DB/sqlite3Database.hpp"

class AppCli { 
private:
    std::string input;
    std::string output;
    DatabaseInterface *db;

public:
    AppCli(DatabaseInterface *db);
    void Input(std::string);
    std::string getOutput();
    bool hasOutput();
    
    void showSensors();
    void addSensor() {};
    void removeSensor();
    void getSensorInfo();
    void disconnect();



};



#endif
