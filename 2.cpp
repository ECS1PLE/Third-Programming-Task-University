#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>
/* Добавил комментарий */
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    ifstream fin("in_din.txt");
    ofstream fout("out_din.txt", ios::trunc);

    if (!fin.is_open()) {
        cout << "Ошибка: не удалось открыть in_din.txt\n";
        return 0;
    }
    if (!fout.is_open()) {
        cout << "Ошибка: не удалось открыть out_din.txt\n";
        fin.close();
        return 0;
    }

    fin.seekg(0, ios::end);
    if (fin.tellg() == 0) {
        cout << "Ошибка: входной файл пустой\n";
        fin.close();
        fout.close();
        return 0;
    }
    fin.seekg(0, ios::beg);

    fout << "Автор: Вавилов Артём Константинович \n";
    fout << "Группа: 5353 \n";
    fout << "Версия: 2 \n";
    fout << "Дата начала: 10.10.2025 \n";
    fout << "Дата окончания: xx.10.2025 \n";
    fout << "========================================== \n";


    string line;
    int count = 0;

    while (fin >> line) {
        bool valid = true;
        int dots = 0, digits = 0;
        int start = 0;
        if (line.empty()) continue;
        if (line[0] == '+' || line[0] == '-') start = 1;
        for (int i = start; i < (int)line.size(); i++) {
            if (line[i] == '.') {
                dots++;
                if (dots > 1) {
                    valid = false;
                    break;
                }
            } else if (isdigit(line[i])) {
                digits++;
            } else {
                valid = false;
                break;
            }
        }
        if (digits == 0) valid = false;
        if (valid) {
            count++;
        } else {
            fout << "Пропущено некорректное число: " << line << "\n";
        }
    }

    if (count == 0) {
        fout << "Нет корректных чисел для обработки\n";
        fin.close();
        fout.close();
        return 0;
    }

    fin.clear();
    fin.seekg(0, ios::beg);

    double *A = new double[count];
    int index = 0;

    while (fin >> line) {
        bool valid = true;
        int dots = 0, digits = 0;
        int start = 0;
        if (line.empty()){
            continue;
        }
        if (line[0] == '+' || line[0] == '-'){
            start = 1;
        }
        for (int i = start; i < (int)line.size(); i++) {
            if (line[i] == '.') {
                dots++;
                if (dots > 1) {
                    valid = false;
                    break;
                }
            } else if (isdigit(line[i])) {
                digits++;
            } else {
                valid = false;
                break;
            }
        }
        if (digits == 0) valid = false;
        if (valid) *(A + index++) = stod(line);
    }
    fin.close();

    fout << fixed << setprecision(2);
    fout << "========================================== \n";
    fout << "Исходный массив (" << count << " элементов): [";
    for (int i = 0; i < count; i++) {
        fout << *(A + i);
        if (i < count - 1){
            fout << ", ";
        }
    }
    fout << "]\n";

    int k;
    cout << "Введите индекс (0.." << count - 1 << "): ";
    cin >> k;

    if (k < 0 || k >= count) {
        fout << "Ошибка: индекс вне диапазона\n";
        delete[] A;
        fout.close();
        return 0;
    }

    double leftSum = 0, rightSum = 0;
    for (int i = 0; i < k; i++){
        leftSum += *(A + i);
    }
    for (int i = k + 1; i < count; i++){
        rightSum += *(A + i);
    } 

    fout << "Сумма элементов слева от индекса " << k <<": " << leftSum << " \n";
    fout << "Сумма элементов справа от индекса " << k <<": " << rightSum << " \n";

    if (leftSum <= rightSum) {
        count = k + 1;
    } else {
        int newN = count - k;
        for (int i = 0; i < newN; i++){
            *(A + i) = *(A + k + i);
        }
        count = newN;
    }

    fout << "Результат (число под индексом " << k << " остаётся): [";
    for (int i = 0; i < count; i++) {
        fout << *(A + i);
        if (i < count - 1){
            fout << ", ";
        }
    }
    fout << "]\n";

    delete[] A;
    fout.close();

    cout << "Результаты записаны в out_din.txt\n";
    return 0;
}
