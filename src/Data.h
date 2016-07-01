//
// Created by noname on 27.06.16.
//

#ifndef UDP_TEST_DATA_H
#define UDP_TEST_DATA_H

#include <array>
#include <unordered_map>

#include "json.hpp"

namespace nn {
    struct Data_Object {
        int value;
        unsigned short int type;
        time_t time;
    };

    class Data {
    public:
        Data() : auto_correct(true) {};

        nlohmann::json as_json();
        std::string as_string();

        void set_field(int knot, int index, int position, int value, unsigned short int type);

    private:
        bool auto_correct;
        std::unordered_map<int, std::unordered_map<int, std::array<Data_Object, 4>>> data;
    };
}


#endif //UDP_TEST_DATA_H
