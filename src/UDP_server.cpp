//
// Created by noname on 27.06.16.
//

#include "UDP_server.h"

#include "easylogging++.h"

#include <array>
#include <iomanip>
#include <sstream>

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <netdb.h>
#include <arpa/inet.h> // inet_addr
#include <stdio.h> // sprintf
//#include <unistd.h> // close

namespace nn {
    el::Logger *udp_logger{nullptr};

    bool UDP_server::create_server(int port) {
        el::Logger *l = el::Loggers::getLogger("udp_server");

        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        server.sin_port = htons(port);

        // bind to port
        if (::bind(sock, (sockaddr *) &server, sizeof(server)) < 0) {
            CLOG(ERROR, "udp_server") << "unable to bind socket";
            return false;
        }

        CVLOG(7, "udp_server") << "socket bound";
        return true;
    }

    bool UDP_server::create_socket() {
        sock = socket(AF_INET, SOCK_DGRAM, 0);

        if (sock < 0) {
            CLOG(ERROR, "udp_server") << "unable to create socket";
            return false;
        }

        CVLOG(7, "udp_server") << "socket created";
        return true;
    }

    void UDP_server::handle_data() {
        unsigned short int buf_len = 15;
        char buf[buf_len];
        int recv_len;
        sockaddr_in client;
        memset(&client, 0, sizeof(client));
        socklen_t client_len = sizeof(client);

        uint8_t counter;
        unsigned short int index;
        unsigned short int knot;
        std::stringstream knot_tmp;
        const uint8_t values_len{4};
        std::array<int, values_len> values;
        std::array<bool, values_len> updated;

        for (; ;) {
            memset(&buf, 0, buf_len);
            knot = 0;
            knot_tmp.str("");
            index = 0;

            for (int i = 0; i < 4; ++i) {
                values[i] = 0;
            }

            if ((recv_len = recvfrom(sock, buf, buf_len, 0, (sockaddr *) &client, &client_len)) == -1) {
                CLOG(ERROR, "udp_server") << "got wrong UDP input, aborting";
                return;
            }

            if (recv_len == 14) {
                CVLOG(7, "udp_server") << "got new UDP input, 14 bytes";

                if VLOG_IS_ON(9) {
                    std::stringstream raw_data;
                    raw_data << "raw data: ";
                    for (int i = 0; i < 14; ++i) {
                        raw_data << std::hex << ((int) buf[i] & 0xFF) << " ";
                    }

                    CVLOG(8, "udp_server") << raw_data.str();
                }

                // knot
                knot = (int) buf[0];

                // index
                index = (int) buf[1];

                // values
                counter = values_len - 1;
                for (int i = 9; i > 1; --i) {
                    if (i % 2 == 1) {
                        values[counter] = ((int) buf[i] & 0xFF) << 8 | ((int) buf[i - 1] & 0xFF);
                    }
                    else {
                        counter--;
                    }
                }

                // updated
                counter = values_len - 1;
                for (int i = 13; i > 9; --i) {
                    updated[counter] = (int) buf[i] & 0b1;
                    counter--;
                }

                // write updated values
                for (int i = 0; i < values_len; ++i) {
                    if ((int) updated[i]) {
                        data->set_field(knot, index, i, values[i]);
                    }
                }

                if VLOG_IS_ON(9) {
                    std::stringstream parsed;
                    char buffer[50];

                    parsed << knot << " " << index;

                    for (int i = 0; i < values_len; ++i) {
                        memset(&buffer, 0, sizeof(buffer));
                        sprintf(buffer, "%2.1f(%d)", ((double) values[i] / 10), (int) updated[i]);

                        parsed << buffer << ", ";
                    }

                    CVLOG(9, "udp_server") << "parsed: " << parsed.str().substr(0, parsed.str().length() - 2);
                }

                CVLOG(9, "udp_server") << "values: " << data->print_data();
            }
            else {
                CLOG(WARNING, "udp_server") << "invalid udp input, " << recv_len << " bytes";
            }
        }
    }

    void UDP_server::init() {
        if (udp_logger == nullptr) {
            el::Logger *udp_server = el::Loggers::getLogger("udp_server");
        }
    }
}
