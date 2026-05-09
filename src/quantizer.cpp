#include "quantizer.h"
#include <cmath>
#include <limits>
#include <algorithm>

std::vector<int16_t> quantize16(const std::vector<double> &signal) {
    /* Квантование сигнала в 16-битную сетку

    signal : исходный сигнал в формате double

    Значения сигнала считаются нормированными к диапазону [-1; 1].
    После квантования значения записываются в тип int16_t.
    */
    std::vector<int16_t> quant_signal;
    quant_signal.reserve(signal.size());

    for (double x : signal) {
        x = std::clamp(x, -1.0, 1.0);
        int16_t qx;

        if (x >= 0) {
            qx = static_cast<int16_t>(round(x*std::numeric_limits<int16_t>::max()));
        } else {
            qx = static_cast<int16_t>(round(-x*std::numeric_limits<int16_t>::min()));
        }
        quant_signal.push_back(qx);
    }
    return quant_signal;
}

std::vector<double> dequantize16(const std::vector<int16_t> &quant_signal) {
    /* Восстановление сигнала из квантованной формы

    quant_signal : квантованный сигнал в формате int16_t

    В результате получается сигнал в формате double,
    нормированный к диапазону [-1; 1].
    */
    std::vector<double> signal;
    signal.reserve(quant_signal.size());

    for (int16_t qx : quant_signal) {
        double x;
        
        if (qx >= 0) {
            x = static_cast<double>(qx) / static_cast<double>(std::numeric_limits<int16_t>::max());
        } else {
            x = - static_cast<double>(qx) / static_cast<double>(std::numeric_limits<int16_t>::min());
        }
        signal.push_back(x);
    }
    return signal;
}

double mean_abs_error(
    const std::vector<double> &orig_signal,
    const std::vector<double> &restored_signal
) {
    // MAE между сигналами
    double sum = 0.0;
    const size_t size = std::min(orig_signal.size(), restored_signal.size());
    if (size == 0) {
        return 0.0;
    }
    for (size_t i = 0; i < size; ++i) {
        sum += std::abs(orig_signal[i] - restored_signal[i]);
    }

    return sum / static_cast<double>(size);
}

double max_abs_error(
    const std::vector<double>& orig_signal,
    const std::vector<double>& restored_signal
) {
    // Максимальная ошибка между сигналами
    double max_error = 0.0;
    const std::size_t size = std::min(orig_signal.size(), restored_signal.size());
    if (size == 0) {
        return 0.0;
    }
    for (std::size_t i = 0; i < size; ++i) {
        double error = std::abs(orig_signal[i] - restored_signal[i]);

        if (error > max_error) {
            max_error = error;
        }
    }

    return max_error;
}