#include "EventServer.hpp"
#include <unistd.h>
#include <string.h>

EventServer::EventServer(const unsigned short port) 
    : BaseServer(port)
{}

void EventServer::CreateConnectionCallback(Peer *peer) {
    printf("EventServer::CreateConnectionCallback\n");
    this->subscribers.push_back(peer);
}

void EventServer::NewEvent(std::string event) {
    printf("EventServer::NewEvent\n");
    printf("EventServer::NewEvent: event = %s\n", event.c_str());
    for(int i = 0; i < subscribers.size(); i++) {
        printf("EventServer::NewEvent: client %d\n", i);

        if(subscribers[i] == NULL) {
            printf("EventServer::NewEvent: subscriber %d is null. Delete him.\n", i);
            subscribers.erase(subscribers.begin()+i);
            continue;
        }

        subscribers[i]->setData(event.c_str(), event.length());
        SendData(subscribers[i]);
    }
}

void EventServer::ReceiveCallback(Peer *peer) {
    printf("EventServer::ReceiveCallback\n");
    printf("EventServer::ReceiveCallback: data = %s\n", peer->getData());
    Sensor sensor;
    std::string res = ReceiveCommandHandler(peer->getData());
    if(!res.empty()) {
        peer->setData(res.c_str(), res.length());
        SendData(peer);
    }
}



void EventServer::SetSensorsExpert(SensorsExpert *expert) {
    sensorsExpert = expert;
}

std::string EventServer::ReceiveCommandHandler(std::string command) {
    Json::Reader reader;
    Json::Value value;
    bool parsing = reader.parse(command, value);
    if(!parsing)
        return std::string("");
    if(value["command"].asString().compare("show_sensors") == 0) {
        std::vector<Sensor> sensors = sensorsExpert->getAllSensors();
        Json::Value sensors_json;
        for(int i = 0; i < sensors.size(); i++) {
            Json::Value sensor_json;
            sensor_json["id"] = sensors[i].getId();
            sensor_json["name"] = sensors[i].getName();
            sensor_json["data"] = sensors[i].getData();
            sensor_json["place"] = sensors[i].getPlace();
            sensor_json["sensor_type"] = sensors[i].getSensorType();
            sensors_json.append(sensor_json);
        }
    } else if(value["command"].asString().compare("get_parameter") == 0) {
    }
}
