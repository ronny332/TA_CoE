//
// Created by noname on 27.06.16.
//

#include <iostream>

#include "Data.h"

namespace nn {
    void Data::print_data() {
        int value_number{0};

        for (int i = 0; i < data.size(); ++i) {
            for (int j = 0; j < data[i].size(); ++j) {
                for (int k = 0; k < data[i][j].size(); ++k) {
                    // only show updated values
                    if (data[i][j][k][2] == 1) {
                        value_number++;
                        std::cout << value_number << ":" << std::dec << data[i][j][k][0] << "\n";
                    }
                }
            }
        }

        std::cout << "\n";
    }

    void Data::set_field(int knot, int index, int position, int value) {
        int old_value = data[knot][index][position][1];

        if (auto_correct && old_value != 0 && value == 0 && (old_value > 10 || old_value < 10)) {
            return;
        }

        // value
        data[knot][index][position][0] = value;
        // time
        data[knot][index][position][1] = time(NULL);
        // updated
        data[knot][index][position][2] = 1;
    }
}


