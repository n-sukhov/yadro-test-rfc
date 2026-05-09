#pragma once
#include <vector>

double sine_taylor(double x, double eps);
std::vector<double> generate_sine(
    double frequency = 0.0,
    double start_time = 0.0,
    double end_time = 1.0,
    double eps = 0.00000001
);