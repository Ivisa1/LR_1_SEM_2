// https://github.com/Ivisa1/LR_1_SEM_2.git

#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include "First_Pract_Functions.cpp"
#include "Second_Pract_Functions.cpp"

using namespace std;

int main() {
    unsigned short number_of_pract_or_task = 0;
    while(true) {
        cout << "\nВведите номер практической, к которой хотите получить доступ\n"
                "Для выхода введите 0\n"
                "Для доступа к курсовой введите 4\n\n"
                "Номер: ";
        cin >> number_of_pract_or_task;

        if (number_of_pract_or_task == 0) { // выход
            cout << "\nВыход из программы...\n";
            break;
        }

        switch (number_of_pract_or_task) { // выбор практической
            case 1: { // 1 практическая
                // cout << "\nПервая практическая на данный момент в разработке\n";
                cout << "\nВключение первой практической...\n";
                Pract_Rab_1(number_of_pract_or_task);
                break;
            }
            case 2: { // 2 практическая
                cout << "\nВключение второй практической...\n";
                PractRab2(number_of_pract_or_task);
                break;
            }
            case 3: { // 3 практическая
                cout << "\nТретья практическая на данный момент в разработке\n";
                break;
            }
            case 4: { // курсовая
                cout << "\nКурсовая на данный момент в разработке\n";
                break;
            }
            default: { // несуществующая практическая
                cout << "\nПрактической с таким номером не существует\n";
                break;
            }
        }
    }
    return 0;
}
