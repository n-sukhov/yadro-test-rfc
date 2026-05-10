#include "signal_generator.h"
#include "quantizer.h"
#include"interpolation.h"
#include "utils.h"
#include <iostream>
#include <cstddef>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <iomanip>

const std::string DATA_FOLDER = "data/";
struct test_pack {
    std::vector<double> frequencies;
    double start_time;
    double end_time;
};

inline void ensure_data_dir() {
    if (!std::filesystem::exists(DATA_FOLDER)) {
        std::filesystem::create_directory(DATA_FOLDER);
    }
}
inline std::string format_double(double x, int precision = 2) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << x;
    return out.str();
}

void process_test(const test_pack& test);

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
            { {0.0, 5.0, 10.0, 20.0, 30.0, 40.0, 49.0}, -1.0, 1.0 },
            { {1.0, 7.0, 15.0, 27.0, 35.0, 45.0, 50.0}, 0.0, 1.0 },
            { {2.0, 12.0, 18.0, 25.0, 33.0, 41.0, 48.0}, 0.0, 2.0 }
        };

        for (const test_pack& test : tests) {
            process_test(test);
        }
    } else if (mode == "manual") {
        test_pack user_test;
        size_t freq_count;

        std::cout << "Enter number of frequencies: ";
        std::cin >> freq_count;

        user_test.frequencies.resize(freq_count);

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


void process_test(const test_pack& test) {
    ensure_data_dir();

    std::cout << "time range: [" << test.start_time << ", " << test.end_time << "]\n";
    std::cout << "frequencies: ";
    for (double freq : test.frequencies) {
        std::cout << freq << " ";
    }
    std::cout << std::endl;
    
    size_t size100 = static_cast<size_t>(
        (test.end_time - test.start_time) * 100.0
    );
    size_t size200 = static_cast<size_t>(
        (test.end_time - test.start_time) * 200.0
    );
    std::vector<double> hz100;
    std::vector<double> hz200;
    hz100.resize(size100);
    hz200.resize(size200);
    for (size_t i = 0; i < size100; ++i) {
        hz100[i] = test.start_time + static_cast<double>(i) * 0.01;
    }
    for (size_t i = 0; i < size200; ++i) {
        hz200[i] = test.start_time + static_cast<double>(i) * 0.005;
    }

    for (double frequency : test.frequencies) {
        std::vector<std::vector<double>> sine_signal_for_csv(2);
        sine_signal_for_csv[0] = hz100;
        std::vector<double> sine_signal = generate_sine(
            frequency,
            test.start_time,
            test.end_time
        );
        sine_signal_for_csv[1] = sine_signal;

        std::string filename =
            DATA_FOLDER + "signal_" +
            format_double(frequency, 1) + "hz_from_" +
            format_double(test.start_time, 1) + "_to_" +
            format_double(test.end_time, 1) + ".csv";
        csv_write(filename, sine_signal_for_csv); 
     }

    // генерация сигнала
    // квантование
    // интерполяция
    // вывод статистики
}