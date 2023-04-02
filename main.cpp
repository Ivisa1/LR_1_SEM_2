#include <iostream>
#include <fstream>

using namespace std;

int Summ (int a, int b) {
    return a + b;
}

// СТРУКТУРЫ
struct Marks { //  информация об оценках
    short aig; // алгебра и геометрия
    short physics; // физика
    short math_an; // математический анализ
    short english; // английский
    short programming; // программирование
    short sport; // физкультура
    short philosophy; // философия
    short informatics; // информатика
    float mid_of_marks; // средняя оценка
};

struct Names { // информация о ФИО
    char first_name[30];// Имя
    char second_name[30]; // Фамилия
    char third_name[30]; // Отчество
};

struct AboutGroup { // информация о группе
    unsigned int group; // номер группы
    unsigned int number_in_group; // номер студента в группе
};

struct Student { // общая структура информации о студенте
    struct Names names;
    bool sex; // 1 - мужской, 0 - женский
    struct AboutGroup aboutGroup;
    struct Marks marks;
    int Summ (int a, int b) {
        return a + b;
    };
};

struct Idz {
    char FIO[90]; // ФИО
    bool sex; // Пол (1 - мужской, 0 - женский)
    unsigned short age; // Возраст
    unsigned short course; //Номер курса
    unsigned short razryad; // Номер разряда (0 - 4)
    unsigned short clothes_size; // Размер одежды (0 - XXS, 6 - XXL)
};

// ФУНКЦИИ
    // ПЕРВАЯ ПРАКТИЧЕСКАЯ

    bool IdzFromPract1 (char * FileName) {
        unsigned short number;
        int temp = 0;
        struct Idz idz[10];
        ifstream File;
        string data;
        File.open(FileName);
        if(!File.is_open()) {
            cout << "\nФайл открыть не удалось\n";
            return 0;
        }
        else {
            for(int i = 0; !File.eof(); i++) {
                File >> idz[i].FIO;
                File >> idz[i].sex;
                File >> idz[i].age;
                File >> idz[i].course;
                File >> idz[i].razryad;
                File >> idz[i].clothes_size;
                temp++;
            }
        }
        File.close();
        cout << "\nС разрядом по волейболу:\n";
        for(int i = 0; i < temp; i++) {
            if (idz[i].razryad > 0) {
                cout << idz[i].FIO << ' ';
                cout << idz[i].sex << ' ';
                cout << idz[i].age << ' ';
                cout << idz[i].course << ' ';
                cout << idz[i].razryad << ' ';
                cout << idz[i].clothes_size << '\n';
            }
        }
        cout << "\nВ женской волейбольной секции:\n";
        for(int i = 0; i < temp; i++) {
            if (idz[i].sex == 0) {
                cout << idz[i].FIO << ' ';
                cout << idz[i].sex << ' ';
                cout << idz[i].age << ' ';
                cout << idz[i].course << ' ';
                cout << idz[i].razryad << ' ';
                cout << idz[i].clothes_size << '\n';
            }
        }
        cout << "\nВведите курс: ";
        cin >> number;
        cout << "\nИгроки с " << number << " курса:\n";
        for(int i = 0; i < temp; i++) {
            if (idz[i].course == number) {
                cout << idz[i].FIO << ' ';
                cout << idz[i].sex << ' ';
                cout << idz[i].age << ' ';
                cout << idz[i].course << ' ';
                cout << idz[i].razryad << ' ';
                cout << idz[i].clothes_size << '\n';
            }
        }
        cout << "\nИгроки мужского пола с размером одежды больше S (4): \n";
        for(int i = 0; i < temp; i++) {
            if (idz[i].course > 2 && idz[i].sex == 1) {
                cout << idz[i].FIO << ' ';
                cout << idz[i].sex << ' ';
                cout << idz[i].age << ' ';
                cout << idz[i].course << ' ';
                cout << idz[i].razryad << ' ';
                cout << idz[i].clothes_size << '\n';
            }
        }
    }

    bool ReworkFileWithStudents(struct Student students[], char * FileName, unsigned short temp) {
        ofstream File;
        File.open(FileName);
        if(!File.is_open()) {
            cout << "\nФайл открыть не удалось\n";
            return 0;
        }
        else {
            for(int i = 0; i < temp; i++) {
                if(i != 0) {
                    File << '\n';
                }
                File << students[i].names.first_name << ' ';
                File << students[i].names.second_name << ' ';
                File << students[i].names.third_name << ' ';
                File << students[i].sex << ' ';
                File << students[i].aboutGroup.group << ' ';
                File << students[i].aboutGroup.number_in_group << ' ';
                File << students[i].marks.aig << ' ';
                File << students[i].marks.english << ' ';
                File << students[i].marks.informatics << ' ';
                File << students[i].marks.math_an << ' ';
                File << students[i].marks.philosophy << ' ';
                File << students[i].marks.physics << ' ';
                File << students[i].marks.programming << ' ';
                File << students[i].marks.sport;
            }
        }
        File.close();
    }

    void CheckStudentsMarks(struct Student students[], unsigned short temp) {
        unsigned short noMoney[10];
        unsigned short noMoneyCount = 0;
        unsigned short midMoney[10];
        unsigned short midMoneyCount = 0;
        unsigned short bigMoney[10];
        unsigned short bigMoneyCount = 0;

        for(int i = 0; i < temp; i++) {
            if(students[i].marks.aig < 5 || students[i].marks.english < 5 || students[i].marks.philosophy < 5
            || students[i].marks.physics < 5 || students[i].marks.programming < 5 || students[i].marks.informatics < 5
            || students[i].marks.sport < 5 || students[i].marks.math_an < 5) {
                if(students[i].marks.aig < 4 || students[i].marks.english < 4 || students[i].marks.philosophy < 4
                || students[i].marks.physics < 4 || students[i].marks.programming < 4 || students[i].marks.informatics < 4
                || students[i].marks.sport < 4 || students[i].marks.math_an < 4) {
                    noMoney[noMoneyCount] = i;
                    noMoneyCount++;
                }
                else {
                    midMoney[midMoneyCount] = i;
                    midMoneyCount++;
                }
            }
            else {
                bigMoney[bigMoneyCount] = i;
                bigMoneyCount++;
            }
        }
        cout << "\nУчащиеся без стипендии:\n";
        for(int i = 0; i < noMoneyCount; i++) {
            cout << students[noMoney[i]].names.first_name << ' ' << students[noMoney[i]].names.second_name
            << ' ' << students[noMoney[i]].names.third_name << '\n';
        }
        cout << "\nУчащиеся хорошисты:\n";
        for(int i = 0; i < midMoneyCount; i++) {
            cout << students[midMoney[i]].names.first_name << ' ' << students[midMoney[i]].names.second_name
                 << ' ' << students[midMoney[i]].names.third_name << '\n';
        }
        cout << "\nУчащиеся отличники:\n";
        for(int i = 0; i < bigMoneyCount; i++) {
            cout << students[bigMoney[i]].names.first_name << ' ' << students[bigMoney[i]].names.second_name
                 << ' ' << students[bigMoney[i]].names.third_name << '\n';
        }
    }

    bool ReadDataAboutStudents(struct Student students[], char * FileName, unsigned short &temp) {
        ifstream File;
        string data;
        File.open(FileName);
        if(!File.is_open()) {
            cout << "\nФайл открыть не удалось\n";
            return 0;
        }
        else {
            for(int i = 0; !File.eof(); i++) {
                File >> students[i].names.first_name;
                File >> students[i].names.second_name;
                File >> students[i].names.third_name;
                File >> students[i].sex;
                File >> students[i].aboutGroup.group;
                File >> students[i].aboutGroup.number_in_group;
                File >> students[i].marks.aig;
                File >> students[i].marks.sport;
                File >> students[i].marks.programming;
                File >> students[i].marks.physics;
                File >> students[i].marks.philosophy;
                File >> students[i].marks.math_an;
                File >> students[i].marks.informatics;
                File >> students[i].marks.english;
                temp++;
            }
        }
        File.close();
    }

    void PrintListOfStudents(struct Student students[], unsigned short temp) {
        for(int i = 0; i < temp; i++) {
            cout << "\n";
            cout << students[i].names.first_name;
            cout << ' ';
            cout << students[i].names.second_name;
            cout << ' ';
            cout << students[i].names.third_name;
            cout << ' ';
            cout << students[i].sex;
            cout << ' ';
            cout << students[i].aboutGroup.group;
            cout << ' ';
            cout << students[i].aboutGroup.number_in_group;
            cout << ' ';
            cout << students[i].marks.aig;
            cout << ' ';
            cout << students[i].marks.english;
            cout << ' ';
            cout << students[i].marks.informatics;
            cout << ' ';
            cout << students[i].marks.math_an;
            cout << ' ';
            cout << students[i].marks.philosophy;
            cout << ' ';
            cout << students[i].marks.physics;
            cout << ' ';
            cout << students[i].marks.programming;
            cout << ' ';
            cout << students[i].marks.sport;
            cout << "\n";
        }
    }

    void CountMenAndWomen(struct Student students[], unsigned short temp) {
        unsigned short men = 0;
        unsigned short women = 0;
        for(int i = 0; i < temp; i++) {
            if(students[i].sex == 1) {
                men++;
            }
            else {
                women++;
            }
        }
        cout << "\nВ списке студентов:\n"
                "Мужчин - " << men << "\nЖенщин - " << women;
    }

    void PrintStudentsFromGroup(struct Student students[], unsigned short number) {
        cout << "Введите номер группы, студентов которой хотите увидеть\n"
                "Номер: ";
        cin >> number;
        cout << "\n";
        cout << "Студенты группы " << number << " :\n";
        for(int i = 0; i < 10; i++) {
            if(number == students[i].aboutGroup.group) {
                cout << students[i].names.first_name;
                cout << ' ';
                cout << students[i].names.second_name;
                cout << ' ';
                cout << students[i].names.third_name;
                cout << ' ';
                cout << students[i].sex;
                cout << ' ';
                cout << students[i].aboutGroup.group;
                cout << ' ';
                cout << students[i].aboutGroup.number_in_group;
                cout << ' ';
                cout << students[i].marks.aig;
                cout << ' ';
                cout << students[i].marks.english;
                cout << ' ';
                cout << students[i].marks.informatics;
                cout << ' ';
                cout << students[i].marks.math_an;
                cout << ' ';
                cout << students[i].marks.philosophy;
                cout << ' ';
                cout << students[i].marks.physics;
                cout << ' ';
                cout << students[i].marks.programming;
                cout << ' ';
                cout << students[i].marks.sport;
                cout << "\n";
            }
        }
    }

    void PrintStudentsWithNumber(struct Student students[], unsigned short number) {
        cout << "Введите номер студентов в группе\n"
                "Номер: ";
        cin >> number;
        cout << "\nСтуденты с номером в группе " << number << " :\n";
        for(int i = 0; i < 10; i++) {
            if(number == students[i].aboutGroup.number_in_group) {
                cout << students[i].names.first_name;
                cout << ' ';
                cout << students[i].names.second_name;
                cout << ' ';
                cout << students[i].names.third_name;
                cout << ' ';
                cout << students[i].sex;
                cout << ' ';
                cout << students[i].aboutGroup.group;
                cout << ' ';
                cout << students[i].aboutGroup.number_in_group;
                cout << ' ';
                cout << students[i].marks.aig;
                cout << ' ';
                cout << students[i].marks.english;
                cout << ' ';
                cout << students[i].marks.informatics;
                cout << ' ';
                cout << students[i].marks.math_an;
                cout << ' ';
                cout << students[i].marks.philosophy;
                cout << ' ';
                cout << students[i].marks.physics;
                cout << ' ';
                cout << students[i].marks.programming;
                cout << ' ';
                cout << students[i].marks.sport;
                cout << "\n";
            }
        }
    }

    bool AddNewStudent(struct Student students[], unsigned short &temp, char * FileName) {
        ofstream File;
        File.open(FileName, ios::app);
        if(!File.is_open()) {
            cout << "\nФайл открыть не удалось\n";
            return 0;
        }
        else {
            File << '\n';
            cout << "\nВведите фамилию, имя и отчество студента (по очереди)\n";
            cout << "\nФамилия: ";
            cin >> students[temp].names.first_name;
            File << students[temp].names.first_name << ' ';
            cout << "Имя: ";
            cin >> students[temp].names.second_name;
            File << students[temp].names.second_name << ' ';;
            cout << "Отчество: ";
            cin >> students[temp].names.third_name;
            File << students[temp].names.third_name << ' ';;
            cout << "\nВведите пол студента (1 - мужской, 0 - женский)\n";
            cout << "Пол: ";
            cin >> students[temp].sex;
            File << students[temp].sex << ' ';;
            cout << "\nВведите номер группы и номер в группе студента (по очереди)\n";
            cout << "Номер группы: ";
            cin >> students[temp].aboutGroup.group;
            File << students[temp].aboutGroup.group << ' ';;
            cout << "Номер в группе: ";
            cin >> students[temp].aboutGroup.number_in_group;
            File << students[temp].aboutGroup.number_in_group << ' ';;
            cout << "\nВведите оценки студента (по очереди)\n";
            cout << "Алгебра и Геометрия: ";
            cin >> students[temp].marks.aig;
            File << students[temp].marks.aig << ' ';;
            cout << "Английский: ";
            cin >> students[temp].marks.english;
            File << students[temp].marks.english << ' ';;
            cout << "Информатика: ";
            cin >> students[temp].marks.informatics;
            File << students[temp].marks.informatics << ' ';;
            cout << "Математический анализ: ";
            cin >> students[temp].marks.math_an;
            File << students[temp].marks.math_an << ' ';;
            cout << "Философия: ";
            cin >> students[temp].marks.philosophy;
            File << students[temp].marks.philosophy << ' ';;
            cout << "Физика: ";
            cin >> students[temp].marks.physics;
            File << students[temp].marks.physics << ' ';;
            cout << "Программирование: ";
            cin >> students[temp].marks.programming;
            File << students[temp].marks.programming << ' ';;
            cout << "Физкультура: ";
            cin >> students[temp].marks.sport;
            File << students[temp].marks.sport << ' ';;
        }
        File.close();
        temp++;
        cout << "\nНовый студент в списке теперь под номером " << temp <<'\n';
    }

    void EditStudent(struct Student students[], unsigned short temp) {
        int temp_for_choose = 0;
        cout << "\nВыберите студента, данные о котором хотите изменить\n"
                "Номер: ";
        cin >> temp_for_choose;
        temp_for_choose--;
        cout << "\nВведите фамилию, имя и отчество студента (по очереди)\n";
        cout << "\nФамилия: ";
        cin >> students[temp_for_choose].names.first_name;
        cout << "Имя: ";
        cin >> students[temp_for_choose].names.second_name;
        cout << "Отчество: ";
        cin >> students[temp_for_choose].names.third_name;
        cout << "\nВведите пол студента (1 - мужской, 0 - женский)\n";
        cout << "Пол: ";
        cin >> students[temp_for_choose].sex;
        cout << "\nВведите номер группы и номер в группе студента (по очереди)\n";
        cout << "Номер группы: ";
        cin >> students[temp_for_choose].aboutGroup.group;
        cout << "Номер в группе: ";
        cin >> students[temp_for_choose].aboutGroup.number_in_group;
        cout << "\nВведите оценки студента (по очереди)\n";
        cout << "Алгебра и Геометрия: ";
        cin >> students[temp_for_choose].marks.aig;
        cout << "Английский: ";
        cin >> students[temp_for_choose].marks.english;
        cout << "Информатика: ";
        cin >> students[temp_for_choose].marks.informatics;
        cout << "Математический анализ: ";
        cin >> students[temp_for_choose].marks.math_an;
        cout << "Философия: ";
        cin >> students[temp_for_choose].marks.philosophy;
        cout << "Физика: ";
        cin >> students[temp_for_choose].marks.physics;
        cout << "Программирование: ";
        cin >> students[temp_for_choose].marks.programming;
        cout << "Физкультура: ";
        cin >> students[temp_for_choose].marks.sport;
        ReworkFileWithStudents(students, "/Users/lemeshkoaleksey/!C++ Projects/2023/Pract_rabs_2_sem_2023/students.txt",
                               temp);
    }

    void MaxMidMark(struct Student students[], unsigned short temp) {
        for(int i = 0; i < temp; i++) {
            students[i].marks.mid_of_marks = (students[i].marks.aig + students[i].marks.english + students[i].marks.math_an + students[i].marks.physics +
                    students[i].marks.philosophy + students[i].marks.sport + students[i].marks.programming + students[i].marks.informatics) / 8;
        }
        for (int j = 0; j < temp - 1; j++) {
            // loop to compare array elements
            for (int i = 0; i < temp - j - 1; ++i) {
                // compare two adjacent elements
                // change > to < to sort in descending order
                if (students[i].marks.mid_of_marks < students[i + 1].marks.mid_of_marks) {
                    // swapping elements if elements
                    // are not in the intended order
                    swap(students[i], students[i + 1]);
                }
            }
        }
        cout << "Топ студентов по среднему баллу:\n";
        for(int i = 0; i < 5 && i < temp; i++) {
            cout << students[i].names.first_name << ' ' << students[i].names.second_name << ' ' << students[i].names.third_name << '\n';
        }
        ReworkFileWithStudents(students, "/Users/lemeshkoaleksey/!C++ Projects/2023/Pract_rabs_2_sem_2023/students.txt",
                               temp);
    }

    int Pract_Rab_1(unsigned short number_of_task) {
        struct Student students[100];
        unsigned short temp = 0;
        while(true) {
            cout << "\nВыберите номер задания, к которому хотите получить доступ\n"
                    "Для чтения данных из файла введите 9\n"
                    "Для возвращения в предыдущее меню введите 0\n\n"
                    "Номер: ";
            cin >> number_of_task;

            if (number_of_task == 0) { // возвращение в предыдущее меню
                cout << "\nВозвращение в предыдущее меню...\n";
                break;
            }
            switch (number_of_task) {
                case 1: { // Создание новой записи о студенте (Задание 1)
                    AddNewStudent(students, temp, "/Users/lemeshkoaleksey/!C++ Projects/2023/Pract_rabs_2_sem_2023/students.txt");
                    break;
                }
                case 2: { // Редактирование записи о студенте (Задание 2)
                    EditStudent(students, temp);
                    break;
                }
                case 3: { // Вывод списка студентов (Задание 3)
                    PrintListOfStudents(students, temp);
                    break;
                }
                case 4: { // Вывод данных о студентах группы N (Задание 4)
                    PrintStudentsFromGroup(students, number_of_task);
                    break;
                }
                case 5: { // Вывод студентов с наивысшим средним баллом (Задание 5)
                    MaxMidMark(students, temp);
                    break;
                }
                case 6: { // Подсчет количества мужчин и женщин в списке (Задание 6)
                    CountMenAndWomen(students, temp);
                    break;
                }
                case 7: { // Вывод данных о студентах без стипендии, со стипендией и отличников (Задание 7)
                    CheckStudentsMarks(students, temp);
                    break;
                }
                case 8: { // вывод данных о студентах, у которых одинаковый номер (Задание 8)
                    PrintStudentsWithNumber(students, number_of_task);
                    break;
                }
                case 9: {
                    ReadDataAboutStudents(students, "/Users/lemeshkoaleksey/!C++ Projects/2023/Pract_rabs_2_sem_2023/students.txt",
                                          temp);
                    break;
                }
                case 10: {
                    IdzFromPract1("/Users/lemeshkoaleksey/!C++ Projects/2023/Pract_rabs_2_sem_2023/voleyball.txt");
                    break;
                }
                default: {
                    cout << "\nЗадания с таким номером не существует\n";
                    break;
                }
            }
        }
        return 0;
    }

int main() {
        cout << sizeof(Student);
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
                cout << "\nВторая практическая на данный момент в разработке\n";
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
