#include <iostream>
#include <string>
#include <utility>

using namespace std;

// Шаблонный класс ScPtrArr для работы с массивами
template <typename T>
class ScPtrArr {
private:
    T* ptr; // Указатель на массив

public:
    // Конструктор по умолчанию
    ScPtrArr() : ptr(nullptr) {}

    // Конструктор с выделением памяти для массива
    ScPtrArr(size_t size) : ptr(new T[size]) {}

    // Деструктор
    ~ScPtrArr() {
        delete[] ptr;
    }

    // Метод для обнуления указателя
    void reset() {
        delete[] ptr;
        ptr = nullptr;
    }

    // Метод для обмена указателями с другим объектом ScPtrArr
    void swap(ScPtrArr& other) {
        std::swap(ptr, other.ptr);
    }

    // Метод для получения "сырого" указателя
    T* get() const {
        return ptr;
    }

    // Оператор индексации для доступа к элементам массива
    T& operator[](size_t index) const {
        return ptr[index];
    }

    // Проверка на пустоту (nullptr)
    bool isNull() const {
        return ptr == nullptr;
    }
};

// Функция для демонстрации работы с массивами разных типов
void demonstrateIntArray() {
    ScPtrArr<int> intArray(5);
    cout << "Массив int: ";
    for (int i = 0; i < 5; ++i) {
        intArray[i] = i * 10;
        cout << intArray[i] << " ";
    }
    cout << endl;
}

void demonstrateDoubleArray() {
    ScPtrArr<double> doubleArray(5);
    cout << "Массив double: ";
    for (int i = 0; i < 5; ++i) {
        doubleArray[i] = i * 0.1;
        cout << doubleArray[i] << " ";
    }
    cout << endl;
}

void demonstrateStringArray() {
    ScPtrArr<string> stringArray(3);
    stringArray[0] = "пупупупупу";
    stringArray[1] = "ляляляля";
    stringArray[2] = ">.<";
    cout << "Массив string: ";
    for (int i = 0; i < 3; ++i) {
        cout << stringArray[i] << " ";
    }
    cout << endl;
}

// Главное меню программы
void menu() {
    int choice;
    do {
        cout << "Меню:\n";
        cout << "1. Демонстрация массива int\n";
        cout << "2. Демонстрация массива double\n";
        cout << "3. Демонстрация массива string\n";
        cout << "4. Выход\n";
        cout << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1:
            demonstrateIntArray();
            break;
        case 2:
            demonstrateDoubleArray();
            break;
        case 3:
            demonstrateStringArray();
            break;
        case 4:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }
    } while (choice != 4);
}

// Точка входа в программу
int main() {
    setlocale(LC_ALL, "rus");
    menu();
    return 0;
}