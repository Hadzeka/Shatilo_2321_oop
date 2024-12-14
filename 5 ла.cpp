#include <iostream>
#include <string>

using namespace std;

class MyString {
private:
    string value;
public:
    void input() {
        cout << "Введите строку: ";
        getline(cin, value);
    }

    friend ostream& operator<<(ostream& os, const MyString& str);
};

ostream& operator<<(ostream& os, const MyString& str) {
    for (char ch : str.value) {
        if (!isupper(ch) && !isdigit(ch)) {
            os << ch;
        }
    }
    return os;
}

int main() {

    setlocale(LC_ALL, "rus");

    MyString myStr;
    myStr.input();
    cout << "Строка без заглавных букв и цифр: " << myStr << endl;

    return 0;
}