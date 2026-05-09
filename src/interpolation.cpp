#include "interpolation.h"
#include "sine_math.h"
#include <cmath>

static double sinc(double x, double eps=0.00000001) {
    if (std::abs(x) < 1e-12) {
        return 1.0;
    }

    const double pix = PI * x;
    return sine_taylor(pix, eps) / pix;
}

std::vector<double> interpolate2_sinc(const std::vector<double>& signal) {
    /* Интерполяция с повышением частоты дискретизации в 2 раза

    signal : исходный сигнал в формате double

    Метод основан на теореме Найквиста-Шеннона-Котельникова.
    Идеальное восстановление требует бесконечной sinc-суммы.
    В данной реализации используется приближенная sinc-интерполяция
    с конечным числом соседних отсчетов.
    */


}
std::vector<int16_t> interpolate2_sinc_fixed(const std::vector<int16_t>& signal) {
    /* Интерполяция, основанная не теореме Найквиста-Шеннона-Котельникова:
    если шаг дискретизации удовлетворяет условию ∆t < 1/(2B), где Фурье-образ
    исходной функции содержится в отрезке [-B, B], сигнал восстанавливается полностью.

    signal : исходный сигнал в формате int16_t
    */
}
