#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "SensorsExpert.hpp"
#include "BaseServer.hpp"
#include "EventServer.hpp"


class Application : public BaseServer {
private:
    SensorsExpert sensorsExpert;
    EventServer *eventServer;

public:
    Application(const unsigned short port, EventServer *eventServer, DatabaseInterface *db);

    void ReceiveCallback(Peer *peer);
};


#endif
