#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// функция для генерации входного файла
void generateInputFile(const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Ошибка открытия файла для записи." << endl;
        return;
    }

    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < 100; ++i) {
        int num = rand() % 101 - 50; // случайное число от -50 до +50
        outFile << num << endl;
    }

    outFile.close();
}

// функция для обработки файлов
void processFiles(const string& inputFilename, const string& outputFilename) {
    ifstream inFile(inputFilename);
    ofstream outFile(outputFilename);

    if (!inFile || !outFile) {
        cerr << "Ошибка открытия файлов." << endl;
        return;
    }

    int* numbers = new int[100];
    int num, count = 0, firstNegative = 0;
    bool foundNegative = false;

    // чтение чисел из входного файла
    while (inFile >> num && count < 100) {
        if (!foundNegative && num < 0) {
            firstNegative = num;
            foundNegative = true;
        }
        numbers[count] = num;
        count++;
    }

    // обработка чисел и запись в выходной файл
    for (int i = 0; i < count; ++i) {
        if (numbers[i] % 2 == 0 && foundNegative) {
            outFile << numbers[i] * firstNegative << endl;
        }
        else {
            outFile << numbers[i] << endl;
        }
    }

    delete[] numbers;
    inFile.close();
    outFile.close();
}

int main() {
    setlocale(LC_ALL, "rus");
    // Работа с файлами
    string inputFilename = "input.txt";
    string outputFilename = "output.txt";

    generateInputFile(inputFilename);
    processFiles(inputFilename, outputFilename);

    cout << "Файлы обработаны." << endl;

    return 0;
}