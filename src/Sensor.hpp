#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <string>
#include <time.h>
#include <jsoncpp/json/json.h>

class Sensor {
private:
    int id;
    std::string name;
    std::string data;
    std::string place;
    int sensor_type;
    int message_type;

public:
    enum SensorType { 
        UNKNOWN = 1,
        WATER = 2,
        OPEN_DOOR,
        SMOKE,
        TEMPERATURE
    };

    enum MessageType {
        EVENT = 1,
        VALUE
    };
        
    Sensor() {}
    Sensor(int id, std::string name, std::string data, int type);

    bool isEmpty();

    int getId() const;
    Sensor *setId(int id);
    
    std::string getName() const;
    Sensor *setName(std::string name);

    std::string getData() const;
    Sensor *setData(std::string data);

    int getMessageType() const;
    Sensor *setMessageType(int message_type);

    int getSensorType() const;
    Sensor *setSensorType(int sensor_type);

    std::string getPlace() const;
    Sensor *setPlace(std::string place);
    
    bool operator==(const Sensor &sensor);

    static std::map<int, Sensor> parseConfig(std::string filename);


};


#endif
