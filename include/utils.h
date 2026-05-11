#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <cstddef>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <cstdint>


const std::string DATA_FOLDER = "data/";
struct test_pack {
    std::vector<double> frequencies;
    double start_time;
    double end_time;
};


void ensure_data_dir();
std::string format_double(double x, int precision = 2);

void process_test(const test_pack& test);
void analyze_test_signal(
    double frequency,
    const std::vector<double>& original_signal,
    const std::vector<double>& hz100,
    const std::vector<double>& hz200
);

template <typename T>
void csv_write(
    const std::string& filename,
    const std::vector<std::vector<T>>& data
) {
    /* Записывает таблицу в csv-файл

    filename : имя файла
    data : таблица
    */
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Can't open the file: " + filename);
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i + 1 < row.size()) {
                file << ",";
            }
        }
        file << "\n";
    }
}