#include "Sensor.hpp"
#include <fstream>
#include <sstream>


Sensor::Sensor(int id, std::string name, std::string data, int type) {
    this->id = id; 
    this->name = name;
    this->data = data;
}

int Sensor::getId() const {
    return id; 
}

Sensor* Sensor::setId(int id) {
    this->id = id; 
    return this;
}

std::string Sensor::getName() const {
    return this->name;
}

Sensor* Sensor::setName(std::string name) {
    this->name = name;
    return this;
}

std::string Sensor::getData() const {
    return this->data;
}

Sensor* Sensor::setData(std::string data) {
    this->data = data;
    return this;
}


bool Sensor::operator==(const Sensor &sensor) {
    return (this->id == sensor.id && this->name == sensor.name && this->data == sensor.data);
}


Sensor* Sensor::setMessageType(int message_type) {
    this->message_type = message_type;
    return this;
}

int Sensor::getMessageType() const {
    return message_type;
}

int Sensor::getSensorType() const {
    return sensor_type;
}

Sensor* Sensor::setSensorType(int sensor_type) {
    this->sensor_type = sensor_type;
    return this;
}


bool Sensor::isEmpty() {
    return name.empty();
}

std::string Sensor::getPlace() const {
    return this->place;
}

Sensor *Sensor::setPlace(std::string place) {
    this->place = place;
    return this;
}


std::map<int, Sensor> Sensor::parseConfig(std::string filename) {
    Json::Reader reader;
    Json::Value value;
    std::ifstream file(filename);
    std::map<int, Sensor> sensors;
    bool parsingSuccessful = reader.parse(file, value);
    if(!parsingSuccessful) {
        printf("Sensor::parseConfig: failure: %s\n", reader.getFormattedErrorMessages().c_str());
        return sensors;   
    }

    Json::Value::Members members = value.getMemberNames();
    std::string id_str = "";
    int id_int = 0;
    for(int i = 0; i < members.size(); i++) {
        id_str = members[i];
        std::istringstream(id_str) >> id_int;
        Sensor sensor;
        sensor.setId(id_int)->
            setName(value[id_str]["name"].asString())->
            setPlace(value[id_str]["place"].asString())->
            setData(value[id_str]["value"].asString());
        sensors[id_int] = sensor;
    }
}
