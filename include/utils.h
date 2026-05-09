#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <cstddef>
#include <stdexcept>

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