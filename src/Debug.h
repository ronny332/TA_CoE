//
// Created by noname on 26.06.16.
//

#ifndef UDP_TEST_DEBUG_H
#define UDP_TEST_DEBUG_H

#include <iostream>

#include <errno.h>
#include <stdlib.h>
#include <string.h>

namespace nn {
    void die(const char *text, int error_no) {
        std::cerr << text << ": " << errno << ", " << strerror(error_no) << std::endl;
        exit(error_no);
    }
}

#endif //UDP_TEST_DEBUG_H
