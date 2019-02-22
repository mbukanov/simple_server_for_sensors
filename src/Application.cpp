#include "Application.hpp"
#include <jsoncpp/json/json.h>

#define CONFIG_FILENAME "config.json"

std::string MakeEventMessage(const Sensor &sensor) {
    std::string result = "New event.\n";
    result += "Sensor: "+sensor.getName()+"\n";
    result += "Place: "+sensor.getPlace()+"\n";
    result += "Value: "+sensor.getData()+"\n";

    return result;
}

Application::Application(const unsigned short port, EventServer * event_server, DatabaseInterface *db)
    : BaseServer(port),
      sensorsExpert(db)
{
    this->eventServer = event_server;
    this->eventServer->SetSensorsExpert(&sensorsExpert);
}


void Application::ReceiveCallback(Peer *peer) {
    printf("Application::ReceiveCallback\n");
    printf("Application::%s: receive message: %s\n", __FUNCTION__, peer->getData());
    std::string data = std::string(peer->getData());
    
    Json::Reader reader;
    Json::Value value;
    bool parsingSuccessful = reader.parse(data, value);
    if(!parsingSuccessful) {
        printf("Application::%s: message parsing failure\n", __FUNCTION__);
        return;
    }
    Sensor sensor;
    int id = value["id"].asUInt();
    sensor.setId(id)->
           setData(value["data"].asString())->
           setSensorType(value["sensor_type"].asUInt())->
           setMessageType(value["message_type"].asUInt());

    if(sensorsExpert.getSensorsFromConfig().count(id) == 0)
        return;

    Sensor sensor_from_config = sensorsExpert.getSensorsFromConfig()[id];

    sensor.setName(sensor_from_config.getName());
    sensor.setPlace(sensor_from_config.getPlace());

    if(sensor.getMessageType() == Sensor::EVENT) {
        eventServer->NewEvent(MakeEventMessage(sensor));
    }

    sensorsExpert.addSensor(sensor);
}

