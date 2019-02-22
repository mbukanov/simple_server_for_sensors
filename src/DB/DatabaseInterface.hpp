#ifndef DATABASEINTERFACE_HPP
#define DATABASEINTERFACE_HPP

#include <stdio.h>
#include <string.h>
#include "../Sensor.hpp"
#include <vector>


class DatabaseInterface {
protected:
    char db_name[64];
public:

    enum {
        FLAG_BY_ID = ( 1<< 0),
        FLAG_BY_NAME = ( 1 << 1 ),
        FLAG_BY_SENSOR_TYPE = ( 1 << 2),
        FLAG_BY_MESSAGE_TYPE = ( 1<< 3),
    };

    DatabaseInterface(char *db_name) { strcpy(this->db_name, db_name); }
    virtual ~DatabaseInterface() {}
    virtual void createSensor(const Sensor &sensor){};
    virtual void retrieveSensor(Sensor &sensor, int flag) {};
    virtual void retrieveSensor(int row, Sensor &sensor, int flag ) {};
    virtual void updateSensor(const Sensor &sensor) {};
    virtual void deleteSensor(const Sensor &sensor) {}; 
    virtual bool sensorExists(const Sensor &sensor) {};
    virtual int sensorsCount(const Sensor *sensor) {};
};



#endif
