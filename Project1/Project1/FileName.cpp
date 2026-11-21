#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>   
using namespace std;
// ============================================================
//  Установка цвета консоли по названию
// ============================================================
void setConsoleColor(const string& color) {
    if (color == "black")       system("color 0F");
    else if (color == "blue")   system("color 1F");
    else if (color == "green")  system("color 2F");
    else if (color == "cyan")   system("color 3F");
    else if (color == "red")    system("color 4F");
    else if (color == "purple") system("color 5F");
    else if (color == "yellow") system("color 6F");
    else if (color == "white")  system("color 7F");
    else                        system("color 0F"); // по умолчанию
}
// ============================================================
//  Проверка: является ли строка допустимым названием цвета
// ============================================================
bool isValidColor(const string& color) {
    string allowed[] = { "black", "blue", "green", "cyan",
                        "red", "purple", "yellow", "white" };
    for (int i = 0; i < 8; i++)
        if (color == allowed[i]) return true;
    return false;
}
// ============================================================
//  Читает имя из name.txt, если файла нет — спрашивает и сохраняет.
// ============================================================
string loadOrAskName() {
    string name;
    ifstream fin("name.txt");

    if (fin.is_open()) {
        getline(fin, name);   // имя может быть с пробелом
        fin.close();
    }

    if (name.empty()) {
        // файла нет или имя пустое — спрашиваем
        do {
            cout << "Введите ваше имя: ";
            getline(cin, name);

            if (name.empty())
                cout << "Имя не может быть пустым! Попробуйте снова.\n";
        } while (name.empty());

        ofstream fout("name.txt");
        fout << name;
        fout.close();
        cout << "Имя сохранено!\n";
    }
    else {
        cout << "Сохранённое имя: " << name << endl;
    }

    return name;
}
// ============================================================
//  Читает цвет из color.txt, если файла нет — спрашивает и сохраняет.
// ============================================================
string loadOrAskColor() {
    string color;
    ifstream fin("color.txt");

    if (fin.is_open()) {
        fin >> color;
        fin.close();
    }

    if (!isValidColor(color)) {
        // файла нет или цвет некорректный — спрашиваем
        do {
            cout << "Введите цвет текста "
                "(black, blue, green, cyan, red, purple, yellow, white): ";
            cin >> color;

            if (!isValidColor(color))
                cout << "Неверный цвет! Повторите ввод.\n";
        } while (!isValidColor(color));

        ofstream fout("color.txt");
        fout << color;
        fout.close();
        cout << "Цвет сохранён!\n";
    }
    else {
        cout << "Сохранённый цвет: " << color << endl;
    }

    return color;
}
// ============================================================
//  Меню изменения настроек (необязательно, но логично)
// ============================================================
void changeSettings(string& name, string& color) {
    char choice;
    cout << "\nХотите изменить настройки? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        cin.ignore();  // убрать '\n' после cin >> choice

        // меняем имя
        do {
            cout << "Введите новое имя: ";
            getline(cin, name);
            if (name.empty())
                cout << "Имя не может быть пустым!\n";
        } while (name.empty());

        ofstream foutName("name.txt");
        foutName << name;
        foutName.close();

        // меняем цвет
        do {
            cout << "Введите новый цвет "
                "(black, blue, green, cyan, red, purple, yellow, white): ";
            cin >> color;
            if (!isValidColor(color))
                cout << "Неверный цвет! Повторите.\n";
        } while (!isValidColor(color));

        ofstream foutColor("color.txt");
        foutColor << color;
        foutColor.close();

        cout << "Настройки обновлены!\n";
    }
}
int main() {
    setlocale(LC_ALL, "Russian");

    // 1. Работа с именем
    string name = loadOrAskName();

    // 2. Работа с цветом
    string color = loadOrAskColor();

    // Применяем цвет и выводим имя
    setConsoleColor(color);
    cout << "\nПривет, " << name << "!\n";

    // 3. Возможность изменить настройки
    changeSettings(name, color);

    // Применяем (возможно, новый) цвет и выводим итог
    setConsoleColor(color);
    cout << "\nИтоговые настройки:\n";
    cout << "Имя: " << name << endl;
    cout << "Цвет: " << color << endl;
    return 0;
}