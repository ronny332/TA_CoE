//
// Created by noname on 28.06.16.
//

#ifndef TA_COE_TELNET_SERVER_H
#define TA_COE_TELNET_SERVER_H

#include "Data.h"

namespace nn {
    class Telnet_server {
    public:
        Telnet_server() = delete;

        Telnet_server(int port, Data* data) : port(port), data(data) {
            init();
            if (create_socket()) {
                runable = create_server(port);
            }
        }

        bool start() {
            if (runable) {
//                handle_data();
                return true;
            }

            return false;
        }

    private:
        bool create_socket();
        bool create_server(int port);
        void init();

        Data* data;
        int port;
        bool runable;
    };
}


#endif //TA_COE_TELNET_SERVER_H
