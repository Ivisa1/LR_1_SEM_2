using namespace std;

// СТРУКТУРЫ
struct listItem{
    listItem *prev;
    listItem *next;
    int data;
};

// ФУНКЦИИ
listItem *Create_DefiniteList(unsigned short &length) {
    listItem *curr = 0, *next = 0;
    while(true) {
        cout << "Введите длину списка: ";
        if(cin >> length) {
            if (length <= 0) {
                cout << "\nВведено неверное значение, введите число ещё раз\n\n";
                continue;
            } else {break;}
        }
        else {
            cout << "\nВведено неверное значение, попробуйте ещё раз\n\n";
            continue;
        }
    }
    for (unsigned i = 1; i <= length; ++i)
    {
        curr = new listItem;
        curr->data = random()%100;
        curr->next = next;
        if (next) {
            next->prev = curr;
        }
        next = curr;
    }
    curr->prev = 0;
    return curr;
}

listItem *Create_IndefiniteList(unsigned short &length) {

}

void DeleteList(unsigned short &length, listItem *list) {
    listItem *next = 0;
    for(int i = 1; i <= length; i++) {
        if(list->next) {
            next = list->next;
        }
        delete list;
        list = next;
    }
    delete next;
    length = 0;
}

void OutputList(listItem *list, unsigned short &length) {
    struct listItem *curr = list;
    while (true) {
        cout << curr->data << ' ';
        if(curr->next) {
            curr = curr->next;
        }
        else {break;}
    }
    cout << endl;
}

int Pract_Rab_2(unsigned short number_of_task) {
    unsigned short length = 0;
    listItem *list;
    cout << "\nКаким способом вы хотите создать двусвязный список?\n"
            "1. Задать размерность, рандомные значения\n"
            "2. Задать значения, размерность по их количеству\n"
            "Для возвращения в предыдущее меню введите 0\n\n"
            "Номер: ";
    cin >> number_of_task;

    switch(number_of_task) {
        case 0: {
            cout << "\nВозвращение в предыдущее меню...\n";
            return 0;
        }
        case 1: {
            list = Create_DefiniteList(length);
            OutputList(list, length);
            break;
        }
        case 2: {
            list = Create_IndefiniteList(length);
            break;
        }
    }
    while (true) {
        cout << "\nВыберите номер задания, к которому хотите получить доступ\n"
                "Для возвращения в предыдущее меню введите 0\n\n"
                "Номер: ";
        cin >> number_of_task;

        switch (number_of_task) {
            case 0: {
                cout << "\nВозвращение в предыдущее меню...\n";
                return 0;
            }
            case 1: { // Создание списка с заданной размерностью и рандомными значениями (Задание 1,а)
                DeleteList(length, list);
                list = Create_DefiniteList(length);
                break;
            }
            case 2: { // Создание списка с размерностью по количеству введённых элементов (Задание 1,б)
                break;
            }
            case 3: { // Скорость создания списка из задания 1,б (Задание 2)
                break;
            }
            case 4: { // Вставка элемента (Задание 3.1)
                break;
            }
            case 5: { // Удаление элемента (Задание 3.2)
                break;
            }
            case 6: { // Обмен элементов (Задание 3.3)
                break;
            }
            case 7: { // Получение элемента (Задание 3.4)
                break;
            }
            case 8: { // Скорость вставки, удаления и получения элемента (Задание 4)
                break;
            }
            default: {
                cout << "\nЗадания с таким номером не существует\n";
                break;
            }
        }
    }
}
