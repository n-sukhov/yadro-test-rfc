#include "signal_generator.h"
#include <cmath>
#include <cstddef>


const double PI = 3.14159265358979323846;
const double TWO_PI = 2.0 * PI;
const double SAMPLE_RATE = 100.0;

static double reduce_phase(double x) {
    // Приведение аргумента x к диапазону [-pi/2; pi/2]
    x = std::remainder(x, TWO_PI);
    if (x > PI / 2.0) {
        x = PI - x;
    } else if (x < -PI / 2.0) {
        x = -PI - x;
    }
    return x;
}

double sine_taylor(double x, double eps) {
    /* Разложение синуса в ряд Тейлора

    x : аргумент функции
    eps : точность
    */
    double func = x;
    int n = 1;
    double factorial_member = 1;
    double x_powered = x;
    double last_fn = x;

    const int max_n = 20;

    while (std::abs(last_fn) > eps && n < max_n) {
        x_powered *= x * x;
        factorial_member *= (2 * n) * (2 * n + 1);
        last_fn = x_powered / factorial_member;
        if (n % 2 == 0) {
            func += last_fn;
        } else {
            func -= last_fn;
        }
        ++n;
    }
    return func;
}

std::vector<double> generate_sine(
    double frequency,
    double start_time,
    double end_time,
    double eps
) {
    /* Генерация массива отсчетов синусоидального сигнала
    
    frequency : частота синусоидального сигнала, Гц
    start_time : начальное время генерации сигнала, с
    end_time : конечное время генерации сигнала, с
    eps : точность вычисления синуса рядом Тейлора
    */
    std::vector<double> signal;
    if (end_time <= start_time) {
        return signal;
    }

    size_t sample_count = static_cast<std::size_t>(SAMPLE_RATE * (end_time - start_time));
    signal.reserve(sample_count);

    for (size_t n = 0; n < sample_count; ++n) {
        const double x_reduced = reduce_phase(
            TWO_PI * frequency * (start_time + static_cast<double>(n) / SAMPLE_RATE)
        );
        signal.push_back(sine_taylor(x_reduced, eps));
    }

    return signal;
}