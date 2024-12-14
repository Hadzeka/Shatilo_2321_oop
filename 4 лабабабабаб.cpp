#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <locale>

using namespace std;

// Класс для обработки исключений
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

// Шаблонный класс уникального указателя
template<typename T>
class UniquePointer {
private:
    T* ptr;
public:
    explicit UniquePointer(T* p = nullptr) : ptr(p) {}

    ~UniquePointer() {
        delete ptr;
    }

    UniquePointer(const UniquePointer&) = delete;
    UniquePointer& operator=(const UniquePointer&) = delete;

    UniquePointer(UniquePointer&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    UniquePointer& operator=(UniquePointer&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T& operator*() {
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }

    T* get() {
        return ptr;
    }

    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }

    void swap(UniquePointer& other) {
        std::swap(ptr, other.ptr);
    }

    void release() {
        ptr = nullptr;
    }
};

// Шаблонный класс Vect
template <typename T>
class Vect {
private:
    T* data;
    size_t size;
    size_t capacity;

    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = std::move(data[i]);
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    Vect() : data(nullptr), size(0), capacity(0) {}

    Vect(initializer_list<T> init_list) : size(init_list.size()), capacity(init_list.size()) {
        data = new T[capacity];
        size_t i = 0;
        for (const T& item : init_list) {
            data[i++] = item;
        }
    }

    Vect(const Vect& other) : size(other.size), capacity(other.capacity) {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    Vect(Vect&& other) noexcept : data(other.data), size(other.size), capacity(other.capacity) {
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    Vect& operator=(const Vect& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Vect& operator=(Vect&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    ~Vect() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    void pop_back() {
        if (size > 0) {
            --size;
        }
        else {
            throw out_of_range("вект пустой");
        }
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw out_of_range("индекс вне диапазона");
        }
        return data[index];
    }

    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }
};

// Шаблонный класс Queue
template <typename T>
class Queue {
private:
    UniquePointer<Vect<T>> vect;

public:
    Queue() : vect(new Vect<T>()) {}

    void enqueue(const T& value) {
        vect->push_back(value);
    }

    void dequeue() {
        if (vect->getSize() == 0) {
            throw out_of_range("очередь пустая");
        }
        for (size_t i = 0; i < vect->getSize() - 1; ++i) {
            (*vect)[i] = std::move((*vect)[i + 1]);
        }
        vect->pop_back();
    }

    T& front() {
        if (vect->getSize() == 0) {
            throw out_of_range("очередь пустая");
        }
        return (*vect)[0];
    }

    size_t size() const {
        return vect->getSize();
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Queue<int> q;
    int choice, value;

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Добавить элемент в очередь (enqueue)\n";
        cout << "2. Удалить элемент из очереди (dequeue)\n";
        cout << "3. Показать передний элемент (front)\n";
        cout << "4. Выйти\n";
        cout << "Выберите действие: ";
        cin >> choice;

        try {
            switch (choice) {
            case 1:
                cout << "Введите значение для добавления: ";
                cin >> value;
                q.enqueue(value);
                cout << "Значение добавлено.\n";
                break;
            case 2:
                q.dequeue();
                cout << "Элемент удален из очереди.\n";
                break;
            case 3:
                cout << "Передний элемент: " << q.front() << endl;
                break;
            case 4:
                return 0;
            default:
                cout << "Неверный выбор, попробуйте снова.\n";
            }
        }
        catch (const out_of_range& e) {
            cerr << "Произошла ошибка: " << e.what() << endl;
        }
        catch (const CustomException& e) {
            cerr << "Произошла ошибка: " << e.what() << " (Значение: " << e.getValue() << ", Код: " << e.getCode() << ")" << endl;
        }
    }

    return 0;
}
