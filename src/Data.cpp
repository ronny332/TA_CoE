//
// Created by noname on 27.06.16.
//

#include <mutex>
#include <sstream>

#include "Data.h"

#include "strlib.h"

namespace nn {
    std::mutex mtx;

    nlohmann::json Data::as_json() {
        nlohmann::json json;

        for (auto knot :data) {
            for (auto index : knot.second) {
                for (auto position : index.second) {
                    json[std::to_string(knot.first)][index.first][position.first] = position.second.value;
                }
            }
        }
        return json;
    }

    std::string Data::as_string() {
        int value_number{0};
        std::stringstream ss_out;
        std::string out;

        nlohmann::json json;

        for (auto knot :data) {
            for (auto index : knot.second) {
                for (auto position : index.second) {
                    value_number++;
                    ss_out << value_number << ":" << std::dec << position.second.value << ", ";
//                    }
                }
            }
        }


        out = trim(ss_out.str());

        return out.substr(0, out.length() - 1);
    }

    void Data::set_field(int knot, int index, int position, int value, unsigned short int type) {
        if (type > 0) {
            int old_value = data[knot][index][position].value;

            if (auto_correct && old_value != 0 && value == 0 && (old_value > 10 || old_value < 10)) {
                return;
            }
        }

        std::lock_guard<std::mutex> lock(mtx);

        // value
        data[knot][index][position].value = value;
        // type
        data[knot][index][position].type = type;
        // time
        data[knot][index][position].time = time(NULL);
    }
}


