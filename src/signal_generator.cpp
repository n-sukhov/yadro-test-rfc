#include "signal_generator.h"
#include "sine_math.h"
#include <cstddef>

std::vector<double> generate_sine(
    double frequency,
    double start_time,
    double end_time,
    double eps,
    double sample_rate
) {
    /* Генерация массива отсчетов синусоидального сигнала
    
    frequency : частота синусоидального сигнала, Гц
    start_time : начальное время генерации сигнала, с
    end_time : конечное время генерации сигнала, с
    eps : точность вычисления синуса рядом Тейлора
    sample_rate : частота дискретизации, Гц
    */
    std::vector<double> signal;
    if (end_time <= start_time) {
        return signal;
    }

    size_t sample_count = static_cast<std::size_t>(sample_rate * (end_time - start_time));
    signal.reserve(sample_count);

    for (size_t n = 0; n < sample_count; ++n) {
        const double x_reduced = TWO_PI * frequency * 
            (start_time + static_cast<double>(n) / sample_rate);
            
        signal.push_back(sine_taylor(x_reduced, eps));
    }

    return signal;
}