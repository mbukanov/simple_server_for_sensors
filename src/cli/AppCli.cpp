#include "AppCli.hpp"

AppCli::AppCli(DatabaseInterface *db) {
    this->db = db;
}

void AppCli::Input(std::string input) {
    printf("AppCli::Input, input string: %s\n", input.c_str());
    if(input.compare(0, 4, "show") == 0) {
        showSensors();
    } 
}

bool AppCli::hasOutput() {
    return !output.empty();
}

void AppCli::showSensors() {
    printf("AppCli::%s start\n", __FUNCTION__);
    int sensors_count = db->sensorsCount(NULL);
    printf("AppCli::%s: sensors_count = %d\n", __FUNCTION__, sensors_count);
    output = "Sensors:";
    Sensor sensor;
    char str[64];
    for(int i = 0; i < sensors_count; i++) {
//        db->retrieveSensor(i, sensor);
        memset(str, 0, 64);
//        sprintf(str, "%d;%s;%s\n", sensor.getId(), sensor.getName().c_str(), Sensor::TypeConversion::FromIntToString(sensor.getSensorType()).c_str());
        output += str;
    }
    printf("AppCli::%s: output = %s\n", __FUNCTION__, output.c_str());
}

std::string AppCli::getOutput() {
    return output;
}
