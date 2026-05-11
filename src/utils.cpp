#include "utils.h"
#include "signal_generator.h"
#include "quantizer.h"
#include "interpolation.h"
#include <iostream>
#include <cmath>


inline void ensure_data_dir() {
    // Проверка наличия папки для сохранения сигналов / её создание
    if (!std::filesystem::exists(DATA_FOLDER)) {
        std::filesystem::create_directory(DATA_FOLDER);
    }
}
inline std::string format_double(double x, int precision) {
    // Форматирование double для записи в названия файлов с заданной точностью
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << x;
    return out.str();
}

void process_test(const test_pack& test) {
    /* Получает структуру теста для генерации сигнала,
    проверяет данные на корректность, сохраняет сигнал в csv-файл,
    вызывает функцию для анализа ошибки квантования
    */
    ensure_data_dir();

    if (test.end_time <= test.start_time) {
        std::cout << "Incorrect time was entered.\n";
        return;
    }

    std::cout << "time range: [" << test.start_time << ", " << test.end_time << "]\n";
    std::cout << "frequencies: ";
    for (double freq : test.frequencies) {
        std::cout << freq << " ";
    }
    std::cout << "\n\n";

    size_t size100 = static_cast<size_t>((test.end_time - test.start_time) * 100.0);
    size_t size200 = static_cast<size_t>((test.end_time - test.start_time) * 200.0) - 1;
    //-1 тк интерполяция строит функцию только между точками

    std::vector<double> hz100(size100);
    std::vector<double> hz200(size200);

    for (size_t i = 0; i < size100; ++i)
        hz100[i] = test.start_time + i * 0.01;

    for (size_t i = 0; i < size200; ++i)
        hz200[i] = test.start_time + i * 0.005;

    for (double frequency : test.frequencies) {
        if (frequency < 0) {
            std::cout << "Incorrect frequency was entered.\n";
            return;
        }

        std::vector<std::vector<double>> sine_signal_for_csv(2);
        sine_signal_for_csv[0] = hz100;
        std::vector<double> sine_signal = generate_sine(
            frequency,
            test.start_time,
            test.end_time
        );
        sine_signal_for_csv[1] = sine_signal;

        std::string filename =
            DATA_FOLDER +
            format_double(frequency, 1) + "hz_from_" +
            format_double(test.start_time, 1) + "_to_" +
            format_double(test.end_time, 1) + "_signal.csv";
        csv_write(filename, sine_signal_for_csv); 
        
        std::cout << "Analysis\n";
        analyze_test_signal(frequency, sine_signal, hz100, hz200);
    }
}

void analyze_test_signal(
    double frequency,
    const std::vector<double>& original_signal,
    const std::vector<double>& hz100,
    const std::vector<double>& hz200
) {
    /* Анализ ошибки квантования + сохранение в csv сигналов
    для последующего анализа интерполяции
    frequency : частота оригинального сигнала в гц
    original_signal : оригинальный сигнал
    hz100 : массив значений времени для частоты дискретизации 100гц
    hz200 : массив значений времени для частоты дискретизации 200гц
    */
    std::cout << "Frequency: " << frequency << " hz\n\n";

    std::vector<int16_t> q = quantize16(original_signal);
    std::vector<double> deq = dequantize16(q);
    double q_mae = mean_abs_error(original_signal, deq);
    double q_max = max_abs_error(original_signal, deq);
    std::cout << "[Quantization]\nMAE = " << q_mae << "\nMax error = " << q_max << "\n\n";

    std::vector<double> sinc = interpolate2_sinc(original_signal, 120);
    std::vector<double> signal200 = generate_sine(
        frequency,
        0.0,
        static_cast<double>(original_signal.size()) / 100.0 - 0.005,
        0.000000001,
        200.0
    );

    std::vector<int16_t> q200 = quantize16(signal200);
    std::vector<int16_t> lin_fixed = interpolate2_lin_fixed_point(q);

    std::string base =
        DATA_FOLDER +
        format_double(frequency, 1) + "hz_from_" +
        format_double(hz200.front(), 1) + "_to_" +
        format_double(hz200.back(), 1);
        
    csv_write<double>(
        base + "_sinc.csv",
        std::vector<std::vector<double>>{ hz200, sinc }
    );

    std::vector<double> lin_fixed_d(lin_fixed.begin(), lin_fixed.end());
    csv_write<double>(
        base + "_lin_fixed.csv",
        std::vector<std::vector<double>>{ hz200, lin_fixed_d }
    );

    csv_write<double>(
        base + "_ref_200.csv",
        std::vector<std::vector<double>>{ hz200, signal200 }
    );

    std::vector<double> q200_d(q200.begin(), q200.end());
    csv_write<double>(
        base + "_ref_quantized_200.csv",
        std::vector<std::vector<double>>{ hz200, q200_d }
    );

}