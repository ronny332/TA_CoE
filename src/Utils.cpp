//
// Created by noname on 30.06.16.
//

#include <arpa/inet.h>

#include "Utils.h"

namespace nn {
    std::string nn::Utils::get_ip(sockaddr_in &client) {
        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client.sin_addr.s_addr, ip, INET_ADDRSTRLEN);

        return std::string(ip);
    }
}

