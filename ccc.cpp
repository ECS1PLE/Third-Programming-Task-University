#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>
using namespace std;

bool isValidNumber(const string& s) {
    if (s.empty()) return false;
    int dots = 0;
    int digits = 0;

    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        if (i == 0 && (c == '+' || c == '-')) continue;
        else if (isdigit(c)) digits++;
        else if (c == '.') {
            dots++;
            if (dots > 1 || i == 0 || i == s.size() - 1) return false;
        }
        else return false;
    }
    return digits > 0;
}

int main() {
    ifstream fin("igogo.txt");
    ofstream fout("in_dy.txt", ios::trunc);
    fout << fixed << setprecision(6);

    if (!fin.is_open()) {
        cout << "Ошибка: не удалось открыть igogo.txt\n";
        return 0;
    }
    if (!fout.is_open()) {
        cout << "Ошибка: не удалось открыть in_dy.txt\n";
        return 0;
    }

    int N;
    fin >> N;

    if (N <= 0) {
        fout << "Ошибка: некорректный размер массива N = " << N << "\n";
        return 0;
    }

    double* X = new double[N];
    int count = 0;
    string token;

    fout << "--- Чтение данных ---\n";
    while (fin >> token && count < N) {
        if (isValidNumber(token)) {
            X[count] = stod(token);
            fout << "X[" << count << "] = " << X[count] << "\n";
            count++;
        }
        else {
            fout << "Ошибка: \"" << token << "\" не является корректным числом\n";
        }
    }

    if (count < N) {
        fout << "Предупреждение: прочитано только " << count << " корректных элементов\n";
        N = count;
    }

    fout << "\n--- Формирование массива Y ---\n";
    double* Y = new double[N];
    int countY = 0;

    for (int i = 1; i < N - 1; i++) {
        if (X[i] > 0) {
            Y[countY] = fabs((X[i - 1] + X[i + 1]) / 2.0);
            fout << "Для X[" << i << "]=" << X[i]
                << " → Y[" << countY << "]=" << Y[countY] << "\n";
            countY++;
        }
    }

    if (countY == 0)
        fout << "Нет положительных элементов для вычисления.\n";
    else {
        fout << "\n--- Массив Y в обратном порядке ---\n";
        for (int i = countY - 1; i >= 0; i--)
            fout << "Y[" << i << "] = " << Y[i] << "\n";
        fout << "\nКоличество элементов в Y: " << countY << "\n";
    }

    delete[] X;
    delete[] Y;

    fin.close();
    fout.close();
    cout << "Обработка завершена. Результат в in_dy.txt\n";
    return 0;
}