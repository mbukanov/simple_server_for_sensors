#include "SensorsExpert.hpp"

#define CONFIG_FILENAME "config.json"

SensorsExpert::SensorsExpert(DatabaseInterface *db) {
    this->db = db;
    sensors_from_config = Sensor::parseConfig(CONFIG_FILENAME);
}

SensorsExpert::~SensorsExpert() {
}


void SensorsExpert::addSensor(const Sensor &sensor) const {
    printf("SensorsExpert::addSensor: id=%d, name=%s, data=%s\n", sensor.getId(), sensor.getName().c_str(), sensor.getData().c_str());
    if(db->sensorExists(sensor)) {
        printf("SensorsExpert::addSensor: updateSensor\n");
        db->updateSensor(sensor);
    } else {
        printf("SensorsExpert::addSensor: createSensor\n");
        db->createSensor(sensor);
    }
}

void SensorsExpert::removeSensor(const Sensor &sensor) const {
    db->deleteSensor(sensor);
}

void SensorsExpert::getSensorByName(Sensor &sensor, std::string name) const {
    sensor.setName(name);
    db->retrieveSensor(sensor, DatabaseInterface::FLAG_BY_NAME);
}

std::map<int, Sensor> SensorsExpert::getSensorsFromConfig() {
    return sensors_from_config;
}

std::vector<Sensor> SensorsExpert::getAllSensors() {
    std::vector<Sensor> res;
    int count = db->sensorsCount(NULL);
    for(int i = 0; i < count; i++) {
        Sensor sensor;
        db->retrieveSensor(i, sensor, 0);
        res.push_back(sensor);
    }
    return res;
}


