#include <iostream>
#include <initializer_list>
#include <stdexcept>

using namespace std;

namespace containers {

    template<typename T>
    class NameClass {
    public:
        struct Node {
            T value; // для хранения  значений
        private:
            Node* prev; //для связей
            Node* next;
            Node(const T& val) : value(val), prev(nullptr), next(nullptr) {}
            friend class NameClass;
        };

        // конструктор по умолчанию
        NameClass() : head(nullptr), tail(nullptr), size(0) {}

        // Конструктор от initializer_list<T>
        NameClass(initializer_list<T> initList) : head(nullptr), tail(nullptr), size(0) {
            for (const T& item : initList) {
                addToEnd(item);
            }
        }

        // конструктор копирования
        NameClass(const NameClass& other) {
            copyFrom(other);
        }

        // копирующий оператор присваивания
        NameClass& operator=(const NameClass& other) {
            if (this != &other) {
                clear();
                copyFrom(other);
            }
            return *this;
        }

        // конструктор перемещения
        NameClass(NameClass&& other) noexcept : head(other.head), tail(other.tail), size(other.size) {
            other.head = other.tail = nullptr;
            other.size = 0;
        }

        // перемещающий оператор присваивания
        NameClass& operator=(NameClass&& other) noexcept {
            if (this != &other) {
                clear();
                head = other.head;
                tail = other.tail;
                size = other.size;
                other.head = other.tail = nullptr;
                other.size = 0;
            }
            return *this;
        }

        // деструктор
        ~NameClass() {
            clear();
        }

        // метод добавления элемента в конец
        void addToEnd(const T& value) {
            Node* newNode = new Node(value);
            if (size == 0) {
                head = tail = newNode;
                head->next = head->prev = head;
            }
            else {
                newNode->prev = tail;
                newNode->next = head;
                tail->next = newNode;
                head->prev = newNode;
                tail = newNode;
            }
            ++size;
        }

        // мтод удаления элемента с конца
        void removeFromEnd() {
            if (size == 0) {
                throw underflow_error("Список пуст.");
            }
            else if (size == 1) {
                delete head;
                head = tail = nullptr;
            }
            else {
                Node* temp = tail;
                tail = tail->prev;
                tail->next = head;
                head->prev = tail;
                delete temp;
            }
            --size;
        }

        // операция индексирования
        T& operator[](size_t index) {
            if (index >= size) {
                throw out_of_range("Индекс вне диапазона.");
            }
            Node* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            return current->value;
        }

        size_t getSize() const {
            return size;
        }

    private:
        Node* head;
        Node* tail;
        size_t size;

        void clear() {
            while (size > 0) {
                removeFromEnd();
            }
        }

        void copyFrom(const NameClass& other) {
            Node* current = other.head;
            for (size_t i = 0; i < other.size; ++i) {
                addToEnd(current->value);
                current = current->next;
            }
        }
    };
}

int main() {
    containers::NameClass<int> intList{ 1, 2, 3, 4, 5 };
    intList.addToEnd(6);
    intList.removeFromEnd();
    for (size_t i = 0; i < intList.getSize(); ++i) {
        cout << intList[i] << " ";
    }
    cout << endl;

    return 0;
}
