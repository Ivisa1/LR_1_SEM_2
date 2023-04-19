using namespace std;

// СТРУКТУРЫ
struct listItem{
    listItem *prev;
    listItem *next;
    int data;
};

// ФУНКЦИИ
listItem *Create_DefiniteList(int &length) {
    listItem *curr = 0, *next = 0;
    while(true) {
        cout << "Введите длину списка: ";
        if(cin >> length) {
            if (length <= 0) {
                cout << "Введено неверное значение, попробуйте ещё раз\n\n";
                cin.clear();
                cin.ignore();
                continue;
            }
            break;
        }
        else {
            cout << "Введено неверное значение, попробуйте ещё раз\n\n";
            cin.clear();
            cin.ignore();
            length = 0;
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

listItem *Create_IndefiniteList(int &length) {

}

listItem *AddElement(listItem *&list, int &length) {
    int pos = 0;
    listItem *item = new listItem;
    cout << "Введите значение элемента и его позицию в списке\n";
    while(true) {
        cout << "Значение: ";
        if(cin >> item->data) {
            cin.clear();
            cin.ignore();
            break;
        }
        else{
            cout << "\nВведено неверное значение, попробуйте ещё раз\n\n";
            cin.clear();
            cin.ignore();
            continue;
        }
    }
    while (true) {
        cout << "Позиция: ";
        if(cin >> pos) {
            if(pos >= length) {
                pos = length;
                cout << "Элемент будет вставлен в конец списка\n";
                cin.clear();
                cin.ignore();
                break;
            }
            if(pos <= 1) {
                pos = 1;
                cout << "Элемент будет вставлен в начало списка\n";
                cin.clear();
                cin.ignore();
                break;
            }
            break;
        }
        else{
            cout << "Введено неверное значение, попробуйте ещё раз\n\n";
            cin.clear();
            cin.ignore();
            continue;
        }
    }
    cout << '\n';
    if(pos == 1) {
        list->prev = item;
        item->prev = 0;
        item->next = list;
        list = item;
        length++;
        return item;
    }
    listItem *curr = list;
    if(pos == length) {
        for(int i = 1; i <= length; i++) {
            if(pos == i) {
                curr->next = item;
                item->next = 0;
                item->prev = curr;
                length++;
                return list;
            }
            curr = curr->next;
        }
    }
    for(int i = 1; i <= length; i++) {
        if(pos == i) {
            item->next = curr;
            item->prev = curr->prev;
            curr->prev->next = item;
            curr->prev = item;
            length++;
            return list;
        }
        curr = curr->next;
    }
}

int SwapElements(listItem *&list, int &length) {
    listItem *curr = list;
    int first, second;
    struct listItem *firstEl, *secondEl;
    firstEl = secondEl = curr;
    while(true) {
        cout << "Введите позицию первого элемента: ";
        if(cin >> first) {
            if(first < 1 || first > length) {
                cout << "Элемента с такой позицией не существует, введите значение ещё раз\n\n";
                cin.clear();
                cin.ignore();
                continue;
            }
            break;
        }
        else {
            cout << "Введено неверное значение, попробуйте ещё раз\n\n";
            cin.clear();
            cin.ignore();
            continue;
        }
    }
    while(true) {
        cout << "Введите позицию второго элемента: ";
        if(cin >> second) {
            if(second < 1 || second > length) {
                cout << "Элемента с такой позицией не существует, введите значение ещё раз\n\n";
                cin.clear();
                cin.ignore();
                continue;
            }
            cout << '\n';
            break;
        }
        else {
            cout << "Введено неверное значение, попробуйте ещё раз\n\n";
            cin.clear();
            cin.ignore();
            continue;
        }
    }
    if(first > second) {
        swap(first, second);
    }
    for(int i = 1; i < first; i++) {
        firstEl = firstEl->next;
    }
    secondEl = firstEl;
    for(; first < second; first++) {
        secondEl = secondEl->next;
    }
    swap(firstEl->data, secondEl->data);
}

int DeleteElementByValue(listItem *&list, int &length) {
    int element = 0;
    while(true) {
        cout << "Введите значение элемента: ";
        if(cin >> element) {
            cin.clear();
            cin.ignore();
            break;
        }
        else {
            cout << "Введено неверное значение, попробуйте ещё раз\n\n";
            cin.clear();
            cin.ignore();
            continue;
        }
    }
    listItem *curr = list;
    for(int i = 1; i <= length; i++) {
        if(curr->data == element) {
            cout << "Элемент со значением " << element << " удалён\n\n";
            if(curr->next) {
                curr->next->prev = curr->prev;
            }
            if(curr->prev) {
                curr->prev->next = curr->next;
            }
            delete curr;
            length--;
            return 0;
        }
        else {
            curr = curr->next;
        }
    }
    cout << "Элемент со значением " << element << " не найден\n\n";
    return 0;
}

int DeleteElementByPosition(listItem *&list, int &length) {
    int position = 0;
    while(true) {
        cout << "Введите позицию элемента: ";
        if(cin >> position) {
            if(position < 1 || position > length) {
                cout << "Элемента с такой позицией не существует\n\n";
                cin.clear();
                cin.ignore();
                return 0;
            }
            cin.clear();
            cin.ignore();
            break;
        }
        else {
            cout << "Введено неверное значение, попробуйте ещё раз\n\n";
            cin.clear();
            cin.ignore();
            continue;
        }
    }
    listItem *curr = list;
    for(int i = 1;; i++) {
        if(position == i) {
            if(curr->next) {
                curr->next->prev = curr->prev;
            }
            if(curr->prev) {
                curr->prev->next = curr->next;
            }
            delete curr;
            length--;
            cout << "Элемент на позиции " << position << " был удалён\n\n";
            return 0;
        }
        curr = curr->next;
    }
}

void DeleteList(int &length, listItem *&list) {
    listItem *curr = list, *next = 0;
    for(int i = 1; i <= length; i++) {
        next = curr->next;
        delete curr;
        curr = next;
    }
    length = 0;
}

void OutputList(listItem *&list) {
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
    int length = 0;
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
            OutputList(list);
            break;
        }
        case 2: {
            list = Create_IndefiniteList(length);
            OutputList(list);
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
                OutputList(list);
                break;
            }
            case 2: { // Создание списка с размерностью по количеству введённых элементов (Задание 1,б)
                OutputList(list);
                break;
            }
            case 3: { // Скорость создания списка из задания 1,б (Задание 2)
                break;
            }
            case 4: { // Вставка элемента (Задание 3.1)
                list = AddElement(list, length);
                OutputList(list);
                break;
            }
            case 5: { // Удаление элемента по значению (Задание 3.2)
                DeleteElementByValue(list, length);
                OutputList(list);
                break;
            }
            case 6: { // Удаление элемента по позиции (Задание 3.3)
                DeleteElementByPosition(list, length);
                OutputList(list);
                break;
            }
            case 7: { // Обмен элементов (Задание 3.4)
                SwapElements(list, length);
                OutputList(list);
                break;
            }
            case 8: { // Получение элемента по значению (Задание 3.4)
                break;
            }
            case 9: {
                break;
            }
            case 10: { // Скорость вставки, удаления и получения элемента (Задание 4)
                break;
            }
            default: {
                cout << "\nЗадания с таким номером не существует\n";
                break;
            }
        }
    }
}
