#include "CliServer.hpp"
#include <stdio.h>
#include <string.h>
#include <algorithm>

CliServer::CliServer(const unsigned short port, DatabaseInterface *db) 
    : BaseServer(port),
      cli(db) 
{}

void string_to_uchar(const std::string &src, unsigned char * out) {
    std::copy( src.begin(), src.end(), out );
}

void CliServer::ReceiveCallback(Peer *peer) {
    printf("We are in CliServer::ConnectionHandler\n");
    for(;;) {
        if(strcmp(peer->getData(), "exit") == 0) 
            break;

        printf("receive in cli: %s\n", peer->getData());
        cli.Input(peer->getData());
        if(cli.hasOutput()) {
            peer->setData(cli.getOutput().c_str(), cli.getOutput().length());
            SendData(peer);
        }
    }
};
