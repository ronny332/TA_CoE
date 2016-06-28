
#include <iostream>
#include <thread>

#include "Data.h"
#include "UDP_server.h"

void start_connection(nn::UDP_server con);

int main() {
    nn::Data data;
    nn::UDP_server con{5441, &data};
    std::thread t_con(start_connection, con);

    t_con.join();
}

void start_connection(nn::UDP_server con) {
    con.start();
}
