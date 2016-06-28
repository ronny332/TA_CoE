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
                if (create_server(port)) {
                    handle_data();
                }
            }
        }

        bool create_socket();
        bool create_server(int port);
        void handle_data();


    private:
        Data* data;
        int port;
        sockaddr_in server;
        int sock;
    };
}

#endif //UDP_TEST_SOCKET_H
