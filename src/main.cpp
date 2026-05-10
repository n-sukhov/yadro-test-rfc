#include "signal_generator.h"
#include "quantizer.h"
#include"interpolation.h"
#include "utils.h"
#include <iostream>
#include <cstddef>
#include <vector>
#include <string>
#include <cmath>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage:\n";
        std::cout << "./yadro_test_rfc auto\n";
        std::cout << "./yadro_test_rfc manual\n";
        return 1;
    }

    std::string mode = argv[1];

    if (mode == "auto") {
        std::vector<test_pack> tests = {
            { {0.0, 5.0, 20.0, 30.0, 49.0}, -1.0, 1.0 },
            { {1.0, 15.0, 27.0, 45.0, 50.0}, 0.0, 1.0 },
            { {2.0, 18.0, 33.0, 48.0}, 0.0, 2.0 }
        };

        for (const test_pack& test : tests) {
            process_test(test);
        }
    } else if (mode == "manual") {
        test_pack user_test;
        double freq_count;

        std::cout << "Enter number of frequencies: ";
        std::cin >> freq_count;
        if (freq_count < 0 || freq_count != std::floor(freq_count)) {
            std::cout << "Array can't have negative or float size.\n";
            return 1;
        }

        user_test.frequencies.resize(static_cast<size_t>(freq_count));

        std::cout << "Enter frequencies:\n";
        for (size_t i = 0; i < freq_count; ++i) {
            std::cin >> user_test.frequencies[i];
        }

        std::cout << "Enter start time: ";
        std::cin >> user_test.start_time;

        std::cout << "Enter end time: ";
        std::cin >> user_test.end_time;

        process_test(user_test);
    } else {
        std::cout << "Unknown mode\n";
        return 1;
    }

    return 0;
}
