#include "sine_math.h"
#include <cmath>

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

double sine_taylor(double x0, double eps) {
    /* Разложение синуса в ряд Тейлора

    x : аргумент функции
    eps : точность
    */
    double x = reduce_phase(x0);

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