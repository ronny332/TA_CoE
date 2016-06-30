//
// Created by noname on 27.06.16.
//

#ifndef COE_SERVER_H
#define COE_SERVER_H

#include "Data.h"

namespace nn {
    class CoE_server {
    public:
        CoE_server() = delete;

        CoE_server(int port, Data* data) : port(port), data(data) {
            init();
            if (create_socket()) {
                runable = create_server(port);
            }
        }

        bool start() {
            if (runable) {
                handle_data();
                return true;
            }

            return false;
        }

    private:
        bool create_socket();
        bool create_server(int port);
        void handle_data();
        void init();

        Data* data;
        int port;
        bool runable;
        sockaddr_in server;
        int sock;
    };
}

#endif //COE_SERVER_SOCKET_H
