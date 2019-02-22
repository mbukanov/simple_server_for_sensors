#ifndef EVENT_SERVER_HPP
#define EVENT_SERVER_HPP

#include "transport/BaseServer.hpp"
#include <vector>
#include "SensorsExpert.hpp"

class EventServer : public BaseServer {
private:
    std::vector<Peer*> subscribers;
    SensorsExpert * sensorsExpert;
public:
    EventServer(const unsigned short port);

    void SetSensorsExpert(SensorsExpert * expert);
    void CreateConnectionCallback(Peer *peer);
    void NewEvent(std::string event);
    void ReceiveCallback(Peer *peer);
    std::string ReceiveCommandHandler(std::string command);
};

#endif
