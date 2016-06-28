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
    enum LOG_TYPES {
        LOG_ERR,
        LOG_STD,
    };

    void die(const char *text, int error_no) {
        std::cerr << text << ": " << errno << ", " << strerror(error_no) << std::endl;
        exit(error_no);
    }

    void log(LOG_TYPES type, const char *text) {
        switch (type) {
            case LOG_ERR:
                std::cerr << text << "\n";
                break;
            case LOG_STD:
                std::cout << text << "\n";
                break;
        }
    }
}

#endif //UDP_TEST_DEBUG_H
