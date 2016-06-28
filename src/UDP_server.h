//
// Created by noname on 27.06.16.
//

#ifndef UDP_TEST_SOCKET_H
#define UDP_TEST_SOCKET_H

#include "Data.h"

#include <netinet/in.h>

namespace nn {
    class UDP_server {
    public:
        UDP_server(int port, Data *data) : port(port), data(data) {
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

        Data* data;
        int port;
        bool runable;
        sockaddr_in server;
        int sock;
    };
}

#endif //UDP_TEST_SOCKET_H
