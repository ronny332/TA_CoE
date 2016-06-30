
#include <iostream>
#include <thread>

#include "Data.h"
#include <Telnet_server.h>
#include "CoE_server.h"

#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP

void start_telnet_server(nn::Telnet_server server);
void start_udp_server(nn::CoE_server server);

int main(int argc, char** argv) {
    START_EASYLOGGINGPP(argc, argv);

    el::Logger* main = el::Loggers::getLogger("main");
    CVLOG(5, "main") << "started";

    // data container
    nn::Data data;

    // telnet server
    nn::Telnet_server telnet_server{5441, &data};
    std::thread t_telnet_server(start_telnet_server, telnet_server);

    // udp server
    nn::CoE_server udp_server{5441, &data};
    std::thread t_udp_server(start_udp_server, udp_server);

    // "join" threads (should never happen)
    t_telnet_server.join();
    t_udp_server.join();
}

void start_udp_server(nn::CoE_server server) {
    server.start();
}

void start_telnet_server(nn::Telnet_server server) {
    server.start();
}