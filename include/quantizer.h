#pragma once
#include <vector>
#include <cstdint>

std::vector<int16_t> quantize16(const std::vector<double> &signal);
std::vector<double> dequantize16(const std::vector<int16_t> &quant_signal);

double mean_abs_error(
    const std::vector<double> &orig_signal,
    const std::vector<double> &restored_signal
);
double max_abs_error(
    const std::vector<double>& orig_signal,
    const std::vector<double>& restored_signal
);