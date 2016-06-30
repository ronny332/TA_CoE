//
// Created by noname on 30.06.16.
//

#ifndef TA_COE_UTILS_H
#define TA_COE_UTILS_H

#include <string>

namespace nn {
    class Utils {
    public:
        static std::string get_ip(sockaddr_in &client);
    };
}


#endif //TA_COE_UTILS_H
