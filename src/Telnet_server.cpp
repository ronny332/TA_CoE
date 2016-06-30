//
// Created by noname on 28.06.16.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h> // close

#include "Telnet_server.h"
#include "Utils.h"

#include "easylogging++.h"
#include "strlib.h"


namespace nn {
    el::Logger *telnet_logger{nullptr};

    bool Telnet_server::create_server(int port) {
        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        server.sin_port = htons(port);

        // bind to port
        int res{0};
        if ((res = ::bind(sock, (sockaddr *) &server, sizeof(server))) < 0) {
            CLOG(ERROR, "telnet_server") << "unable to bind socket: #" << res << ", port:" << port;
            return false;
        }

        CVLOG(6, "telnet_server") << "socket bound to port " << port << "/tcp";

        if ((res = listen(sock, 5) < 0)) {
            CLOG(ERROR, "telnet_server") << "unable to listen to socket: #" << res;
            return false;
        }

        CVLOG(6, "telnet_server") << "listening to port " << port << "/tcp";

        return true;
    }

    bool Telnet_server::create_socket() {
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if (sock < 0) {
            CLOG(ERROR, "telnet_server") << "unable to create socket";
            return false;
        }

#ifdef SO_REUSEPORT
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, (const char *) &reuse_socket_port, sizeof(reuse_socket_port)) <
            0) {
            CLOG(ERROR, "telnet_server") << "SO_REUSEPORT available, but setsockopt(SO_REUSEPORT) failed";
            return false;
        }
#endif

        CVLOG(7, "telnet_server") << "socket created";
        return true;
    }

    void Telnet_server::handle_requests() {
        sockaddr_in client{};
        char recv_buffer[recv_buffer_size];
        int recv_size{0};
        int send_size{0};
        int sock_client{0};
        socklen_t sock_len = sizeof(client);

        std::string request_str{};
        std::string response_str{};
        std::string response_stream{};

        CVLOG(6, "telnet_server") << "waiting for new connections";

        for (; ;) {
            memset(&client, 0, sizeof(client));

            sock_client = accept(sock, (sockaddr *) &client, &sock_len);

            if (sock_client < 0) {
                CLOG(ERROR, "telnet_server") << "invalid request, socket: " << sock_client;
            }

            if ((recv_size = recv(sock_client, recv_buffer, recv_buffer_size, 0)) < 0) {
                CLOG(ERROR, "telnet_server") << "invalid request, received size: " << recv_size;
            }

            CVLOG(7, "telnet_server") << "new connection from " << Utils::get_ip(client);

            request_str = trim(recv_buffer);
            response_str = "";
            response_stream.c_str();

            if (commands[request_str]) {
                if (request_str == "list") {
                    response_str = data->print_data();
                }
            }
            else {
                response_str = "invalid request";
            }

            if ((send_size = send(sock_client, response_str.c_str(), response_str.length(), 0)) < 0) {
                CLOG(ERROR, "telnet_server") << "unable to send response to client ";
            }

            shutdown(sock_client, SHUT_WR);
            close(sock_client);
        }
    }

    void Telnet_server::init() {
        commands["list"] = 1;

        if (telnet_logger == nullptr) {
            el::Logger *udp_server = el::Loggers::getLogger("telnet_server");
        }
    }
}



