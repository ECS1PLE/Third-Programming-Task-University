#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    int len_real, all_elements;
    string filenumstr, line;
    ofstream shaurmmeow("shaurmmeow.txt", ios::trunc);

    if (!shaurmmeow.is_open())
    {
        cout << "Не удалось открыть файл для записи.\n";
        return 0;
    }

    shaurmmeow << "Автор: Вавилов Артём Константинович \n";
    shaurmmeow << "Группа: 5353 \n";
    shaurmmeow << "Версия: 1 \n";
    shaurmmeow << "Дата начала: 10.10.2025 \n";
    shaurmmeow << "Дата окончания: xx.10.2025 \n";

    const int size = 150;
    double X[size], g;

    for (int filenum = 1; filenum <= 12; filenum++)
    {
        filenumstr = "in" + to_string(filenum) + ".txt";
        shaurmmeow << "===================== " << filenumstr << " =====================\n";

        ifstream in(filenumstr);
        if (!in.is_open())
        {
            shaurmmeow << "Ошибка: не удалось открыть файл " << filenumstr << "\n\n";
            continue;
        }
        if (in.peek() == EOF)
        {
            shaurmmeow << "Файл пустой\n\n";
            in.close();
            continue;
        }

        int count_elements = 0;
        string tmp;
        while (in >> tmp) count_elements++;
        in.clear();
        in.seekg(0, ios::beg);

        if (count_elements < 2)
        {
            shaurmmeow << "В файле указана только длина. Пустой массив \n";
            shaurmmeow << "Массив: []\n\n";
            in.close();
            continue;
        }

        len_real = 0;
        all_elements = 0;

        if (!(in >> line))
        {
            shaurmmeow << "Файл пустой\n\n";
            in.close();
            continue;
        }

        bool first_invalid = false;
        for (char c : line)
        {
            if (c < '0' || c > '9')
            {
                first_invalid = true;
                break;
            }
        }

        if (first_invalid || line.empty())
        {
            shaurmmeow << "Некорректная длина файла: первый элемент должен быть положительным целым числом\n\n";
            in.close();
            continue;
        }

        g = stod(line);
        if (g < 0 || floor(g) != g)
        {
            shaurmmeow << "Некорректная длина файла: первый элемент должен быть положительным целым числом\n\n";
            in.close();
            continue;
        }

        if(g==0){
            shaurmmeow << "Массив: []\n\n";
            shaurmmeow << "Длина массива 0, поэтому пустой массив \n";
            in.close();
            continue;
        }

        int max_elements = (int)g;
        shaurmmeow << "Первое корректное число (количество элементов): " << max_elements << "\n";

        while (in >> line)
        {
            all_elements++;
            int i = 0, kol_chis = 0, dot_count = 0, norma = 1;

            if (line[0] == '-' || line[0] == '+') i++;

            for (; i < (int)line.size(); i++)
            {
                if (line[i] == '.')
                {
                    dot_count++;
                    if (dot_count > 1)
                    {
                        norma = 0;
                        shaurmmeow << "Число \"" << line << "\" не обработано: лишняя точка\n";
                        break;
                    }
                }
                else if (isdigit(line[i])) kol_chis++;
                else
                {
                    norma = 0;
                    shaurmmeow << "Число \"" << line << "\" не обработано: неверный символ '" << line[i] << "'\n";
                    break;
                }
            }

            if (norma == 1)
            {
                bool valid = false;
                if (kol_chis > 0) valid = true;
                else if (dot_count == 1 && line.size() > 1)
                {
                    if (!(line == "." || line == "+." || line == "-."))
                        valid = true;
                }

                if (valid)
                {
                    g = stod(line);
                    if (len_real < max_elements && len_real < size)
                    {
                        X[len_real++] = g;
                        shaurmmeow << fixed << setprecision(2);
                        shaurmmeow << "Число \"" << line << "\" обработано: " << g << "\n";
                    }
                    else if (len_real >= max_elements)
                        shaurmmeow << "Ошибка. Индекс числа " << line << " больше максимальной длины\n";
                    else
                    {
                        shaurmmeow << "Достигнут предел массива (" << size << "), оставшиеся числа пропущены\n";
                        break;
                    }
                }
                else
                    shaurmmeow << "Число \"" << line << "\" не обработано: некорректный формат\n";
            }
        }

        in.close();

        if (len_real == 0)
        {
            shaurmmeow << "Нет корректных чисел для обработки после первого.\n\n";
            continue;
        }

        shaurmmeow << "Количество корректных элементов: " << len_real << "\n";

        shaurmmeow << "Исходный массив: [";
        for (int i = 0; i < len_real; i++)
        {
            shaurmmeow << fixed << setprecision(2) << X[i];
            if (i != len_real - 1) shaurmmeow << ", ";
        }
        shaurmmeow << "]\n";

        int k;
        cout << "Файл " << filenumstr << " — введите индекс (0.." << len_real - 1 << "): ";
        cin >> k;
        shaurmmeow << "Введенный индекс: " << k << "\n";

        if (k < 0 || k >= len_real)
        {
            shaurmmeow << "Ошибка: индекс вне диапазона.\n\n";
            continue;
        }

        double leftSum = 0, rightSum = 0;
        for (int i = 0; i < k; i++) leftSum += X[i];
        for (int i = k + 1; i < len_real; i++) rightSum += X[i];

        shaurmmeow << fixed << setprecision(2);
        shaurmmeow << "Сумма элементов слева от индекса " << k << ": " << leftSum << "\n";
        shaurmmeow << "Сумма элементов справа от индекса " << k << ": " << rightSum << "\n";

        if (leftSum <= rightSum)
            len_real = k + 1;
        else
        {
            int newN = len_real - k;
            for (int i = 0; i < newN; i++) X[i] = X[k + i];
            len_real = newN;
        }

        shaurmmeow << "Результат (число под индексом " << k << " остаётся): [";
        for (int i = 0; i < len_real; i++)
        {
            shaurmmeow << fixed << setprecision(2) << X[i];
            if (i != len_real - 1) shaurmmeow << ", ";
        }
        shaurmmeow << "]\n-----------------------------------\n\n";
    }

    shaurmmeow.close();
    cout << "Результаты записаны в shaurmmeow.txt\n";
    return 0;
}
