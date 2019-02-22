#ifndef SQLITE3DATABASE_HPP
#define SQLITE3DATABASE_HPP

#include "DatabaseInterface.hpp"
#include "../Sensor.hpp"
#include <sqlite3.h>

#define TABLE_NAME "sensors"

class sqlite3Database : public DatabaseInterface {
private:
    sqlite3 *db = NULL;
    char *zErrMsg = NULL;

public:
    sqlite3Database(char* filename);
    ~sqlite3Database();

    void createSensor(const Sensor &sensor);
    void retrieveSensor(Sensor &sensor, int flag);
    void retrieveSensor(int row, Sensor &sensor, int flag);
    void updateSensor(const Sensor &sensor);
    void deleteSensor(const Sensor &sensor);
    
    void createTable();
    bool tableExists();
    bool sensorExists(const Sensor &sensor);
    int sensorsCount(const Sensor *sensor);


    static int retrieve_callback(void *data, int argc, char **argv, char **azColName);
    static int sensors_count_callback(void *data, int argc, char **argv, char **azColName);
};


#endif
