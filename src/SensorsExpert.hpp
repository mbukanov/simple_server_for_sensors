#ifndef SENSORS_EXPERT_HPP
#define SENSORS_EXPERT_HPP

#include <vector>
#include "Sensor.hpp"
#include "DB/DatabaseInterface.hpp"
#include "DB/sqlite3Database.hpp"


class SensorsExpert {
private:
    DatabaseInterface *db;
    std::map<int, Sensor> sensors_from_config;

public:
    SensorsExpert(DatabaseInterface *db);
    ~SensorsExpert();

    void addSensor(const Sensor &sensor) const;
    void removeSensor(const Sensor &sensor) const;

    void getSensorByName(Sensor &sensor, std::string name) const;
    void getParameterLastValue(int parameter_type);

    std::map<int, Sensor> getSensorsFromConfig();

    std::vector<Sensor> getAllSensors();
};

#endif
