#include "interpolation.h"
#include "sine_math.h"
#include <cmath>
#include <algorithm>

static double sinc(double x, double eps=0.00000001) {
    if (std::abs(x) < 1e-12) {
        return 1.0;
    }

    const double pix = PI * x;
    return sine_taylor(pix, eps) / pix;
}

std::vector<double> interpolate2_sinc(const std::vector<double>& signal, int radius) {
    /* Интерполяция с повышением частоты дискретизации в 2 раза

    signal : исходный сигнал в формате double

    Метод основан на теореме Найквиста-Шеннона-Котельникова.
    Идеальное восстановление требует бесконечной sinc-суммы.
    В данной реализации используется приближенная sinc-интерполяция
    с конечным числом соседних отсчетов.
    */
    std::vector<double> interpolated_signal;
    if (signal.empty()) {
        return interpolated_signal;
    }

    const size_t int_sig_size = signal.size() * 2 - 1;
    interpolated_signal.reserve(int_sig_size);
    
    for (size_t i = 0; i < int_sig_size; ++i) {
        double x;
        if (i % 2 == 0) {
            x = signal[i / 2];
        } else {
            x = 0.0;
            const double pos = static_cast<double>(i) / 2.0;
            const int center = static_cast<int>(pos);
            
            const int left = std::max(-radius, -center);
            const int right = std::min(radius, static_cast<int>(signal.size()) - 1 - center);

            for (int k = left; k <= right; ++k) {
                const int n = center + k;
                x += signal[n] * sinc(pos - static_cast<double>(n));
            }
        }
        interpolated_signal.push_back(x);
    }
    return interpolated_signal;
}

std::vector<int16_t> interpolate2_lin_fixed_point(const std::vector<int16_t>& signal) {
    /* Линейная интерполяция с повышением частоты дискретизации в 2 раза

    signal : исходный сигнал в формате int16_t
    */
    std::vector<int16_t> interpolated_signal;
    if (signal.empty()) {
        return interpolated_signal;
    }

    const size_t int_sig_size = signal.size() * 2 - 1;
    interpolated_signal.reserve(int_sig_size);

    for (size_t n = 0; n < signal.size() - 1; ++n) {
        interpolated_signal.push_back(signal[n]);
        int32_t mid = (static_cast<int32_t>(signal[n]) + static_cast<int32_t>(signal[n + 1])) / 2;
        interpolated_signal.push_back(static_cast<int16_t>(mid));
    }
    interpolated_signal.push_back(signal.back());

    return interpolated_signal;
}