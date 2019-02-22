#ifndef CLISERVER_HPP
#define CLISERVER_HPP
#include <../transport/BaseServer.hpp>
#include "AppCli.hpp"

class CliServer : public BaseServer {
private:
    AppCli cli;
public:
    void ReceiveCallback(Peer *peer);
    CliServer(const unsigned short port, DatabaseInterface *db);
};


#endif
