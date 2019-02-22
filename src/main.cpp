#include <stdio.h>
#include "Application.hpp"
#include "cli/CliServer.hpp"
#include "EventServer.hpp"

int main() {
    const unsigned short app_server_port = 5551;
    const unsigned short cli_server_port = 5552;
    const unsigned short event_server_port = 5553;

    DatabaseInterface *db = new sqlite3Database((char*)"test.db");

    EventServer event_server(event_server_port);
    event_server.Start();

    Application app(app_server_port, &event_server, db);
    app.Start();

    CliServer cli_server(cli_server_port, db);
    cli_server.Start();


    

    app.Wait();
    cli_server.Wait();
    event_server.Wait();



    delete db;

    return 0;
}
