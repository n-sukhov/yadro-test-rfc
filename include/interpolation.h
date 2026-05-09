#pragma once
#include <vector>
#include <cstdint>

std::vector<double> interpolate2_sinc(const std::vector<double>& signal);
std::vector<int16_t> interpolate2_sinc_fixed(const std::vector<int16_t>& signal);