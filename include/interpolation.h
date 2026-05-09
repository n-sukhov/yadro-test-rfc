#pragma once
#include <vector>
#include <cstdint>
#include <cstddef>

std::vector<double> interpolate2_sinc(const std::vector<double>& signal, int radius = 100);
std::vector<int16_t> interpolate2_lin_fixed_point(const std::vector<int16_t>& signal);