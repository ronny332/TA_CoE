//
// Created by noname on 28.06.16.
//

#ifndef TA_COE_TELNET_SERVER_H
#define TA_COE_TELNET_SERVER_H

#include <netinet/in.h>
#include <unordered_map>

#include "Data.h"

namespace nn {
    class Telnet_server {
    public:
        Telnet_server() = delete;

        Telnet_server(int port, Data* data) : data(data), port(port), recv_buffer_size(1024), reuse_socket_port(1) {
            init();
            if (create_socket()) {
                runable = create_server(port);
            }
        }

        bool start() {
            if (runable) {
                handle_requests();
                return true;
            }

            return false;
        }

    private:
        bool create_socket();
        bool create_server(int port);
        void handle_requests();
        void init();

        std::unordered_map<std::string, int> commands;
        Data* data;
        int port;
        int recv_buffer_size;
        int reuse_socket_port;
        bool runable;
        sockaddr_in server;
        int sock;
    };
}


#endif //TA_COE_TELNET_SERVER_H
