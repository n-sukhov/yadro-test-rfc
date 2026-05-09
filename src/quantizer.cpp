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

}

std::vector<double> calc_qauntizer_err(
    const std::vector<double> &orig_signal,
    const std::vector<double> &restored_signal
) {

}
