//
// Created by noname on 27.06.16.
//

#include <array>
#include <iomanip>
#include <sstream>

#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <netdb.h>
#include <arpa/inet.h> // inet_addr
#include <stdio.h> // sprintf

#include "CoE_server.h"

#include "easylogging++.h"

namespace nn {
    el::Logger *coe_logger{nullptr};

    bool CoE_server::create_server(int port) {
        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        server.sin_port = htons(port);

        // bind to port
        int res{0};
        if ((res = ::bind(sock, (sockaddr *) &server, sizeof(server))) < 0) {
            CLOG(ERROR, "coe_server") << "unable to bind socket: #" << res << ", port:" << port;
            return false;
        }

        CVLOG(6, "coe_server") << "socket bound to port " << port << "/udp";
        return true;
    }

    bool CoE_server::create_socket() {
        sock = socket(AF_INET, SOCK_DGRAM, 0);

        if (sock < 0) {
            CLOG(ERROR, "coe_server") << "unable to create socket";
            return false;
        }

        CVLOG(6, "coe_server") << "socket created";
        return true;
    }

    void CoE_server::handle_data() {
        unsigned short int buf_len = 15;
        char buf[buf_len];
        int recv_len;
        sockaddr_in client;
        memset(&client, 0, sizeof(client));
        socklen_t client_len = sizeof(client);

        uint8_t counter;
        bool digital_values{true};
        unsigned short int index;
        unsigned short int knot;
        std::stringstream knot_tmp;
        const uint8_t values_len{4};
        std::array<int, values_len> value_types;
        std::array<int, values_len> values;

        for (; ;) {
            memset(&buf, 0, buf_len);
            digital_values = true;
            knot = 0;
            knot_tmp.str("");
            index = 0;

            for (int i = 0; i < 4; ++i) {
                value_types[i] = 0;
                values[i] = 0;
            }

            if ((recv_len = recvfrom(sock, buf, buf_len, 0, (sockaddr *) &client, &client_len)) == -1) {
                CLOG(ERROR, "coe_server") << "got wrong UDP input, aborting";
                return;
            }

            if (recv_len == 14) {
                CVLOG(7, "coe_server") << "got new UDP input, 14 bytes";

                if VLOG_IS_ON(9) {
                    std::stringstream raw_data;
                    raw_data << "raw data: ";
                    for (int i = 0; i < 14; ++i) {
                        raw_data << std::hex << ((int) buf[i] & 0xFF) << " ";
                    }

                    CVLOG(9, "coe_server") << raw_data.str();
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

                // detect value types (digital values always have a type of 0 for all 4 fields)
                counter = values_len - 1;
                for (int i = 13; i > 9; --i) {
                    if (((int) buf[i] & 0x1F) > 0) {
                        if (digital_values) {
                            digital_values = false;
                        }

                        value_types[counter] = (int) buf[i] & 0x1F;
                    }

                    counter--;
                }

                // write updated values
                for (int i = values_len - 1; i >= 0; --i) {
                    if (digital_values) {
                        data->set_field(knot, index, i, values[i], 0);
                    }
                    else if (value_types[i] > 0) {
                        data->set_field(knot, index, i, values[i], value_types[i]);
                    }
                }

                if VLOG_IS_ON(9) {
                    std::stringstream parsed;
                    char buffer[50];

                    parsed << knot << " " << index;

                    for (int i = 0; i < values_len; ++i) {
                        memset(&buffer, 0, sizeof(buffer));
                        sprintf(buffer, "%2.1f(%d)", ((double) values[i] / 10), (int) value_types[i]);

                        parsed << " " << buffer << ", ";
                    }

                    CVLOG(8, "coe_server") << "parsed: " << parsed.str().substr(0, parsed.str().length() - 2);
                }

                CVLOG(9, "coe_server") << "values: " << data->as_string();
            }
            else {
                CLOG(WARNING, "coe_server") << "invalid udp input, " << recv_len << " bytes";
            }
        }
    }

    void CoE_server::init() {
        if (coe_logger == nullptr) {
            coe_logger = el::Loggers::getLogger("coe_server");
        }
    }
}
