//
// Created by noname on 27.06.16.
//

#ifndef UDP_TEST_DATA_H
#define UDP_TEST_DATA_H

#include <array>
#include <unordered_map>

namespace nn {
    class Data {
    public:
        void print_data();
        void set_field(int knot, int index, int position, int value);

    private:
        bool auto_correct = true;
        std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, std::array<int, 3>>>> data;
    };
}


#endif //UDP_TEST_DATA_H
