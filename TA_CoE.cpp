
#include <iostream>
#include <string>

#include "Data.h"
#include "UDP_server.h"

using namespace std;

int main() {
    nn::Data data;
    nn::UDP_server con{5441, &data};
}