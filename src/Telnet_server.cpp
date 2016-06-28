//
// Created by noname on 28.06.16.
//

#include "Telnet_server.h"

#include "easylogging++.h"

namespace nn {
    el::Logger* telnet_logger{nullptr};

    bool Telnet_server::create_socket() {

        CVLOG(7, "telnet_server") << "socket bound";
        return true;
    }

    bool Telnet_server::create_server(int port) {

        CVLOG(7, "telnet_server") << "socket created";
        return true;
    }

    void Telnet_server::init() {
        if (telnet_logger == nullptr) {
            el::Logger* udp_server = el::Loggers::getLogger("telnet_server");
        }
    }
}



