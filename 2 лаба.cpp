#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

// класс для обработки исключений
class CustomException : public exception {
private:
    string message;
    double value;
    int code;
public:
    CustomException(const string& msg, double val, int c) : message(msg), value(val), code(c) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
    double getValue() const { return value; }
    int getCode() const { return code; }
};

// функция для вычисления Z1
double calculate_z1(double x) {
    try {
        double z1 = pow((2 + (1 + x + x * x) / (2 * x + x * x) - (1 - x + x * x) / (2 * x - x * x)), 2) * (5 - 2 * x * x);
        return z1;
    }
    catch (const exception& e) {
        throw CustomException("Обнаружено деление на ноль при вычислении Z1", x, 1);
    }
}

// функция для вычисления Z2
double calculate_z2(double x) {
    try {
        if (x == 2) {
            throw CustomException("Обнаружено деление на ноль при вычислении Z2", x, 2);
        }
        double z2 = (4 - x * x) / 2;
        return z2;
    }
    catch (const exception& e) {
        throw CustomException("Обнаружено деление на ноль при вычислении Z2", x, 2);
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    try {
        double x = 1;  // пример значения x
        double z1 = calculate_z1(x);
        double z2 = calculate_z2(x);
        cout << "Z1: " << z1 << ", Z2: " << z2 << endl;

        if (fabs(z1 - z2) < 1e-5) {  // проверка приближенности значений
            cout << "Значения Z1 и Z2 примерно равны." << endl;
        }
        else {
            cout << "Значения Z1 и Z2 не равны." << endl;
        }
    }
    catch (const CustomException& e) {
        cerr << "Произошла ошибка: " << e.what() << " (Значение: " << e.getValue() << ", код " << e.getCode() << ")" << endl;
    }

    return 0;
}