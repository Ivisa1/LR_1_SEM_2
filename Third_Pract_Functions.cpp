#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

// Словари
map <string, int> weights = {
        {"+", 1},
        {"-", 1},
        {"*", 2},
        {"/", 2},
        {"^", 3},
        {"(", 0},
        {")", 0}
};
map<string, int> variables = {};

// Структура стека
struct StackNode {
    string value;
    struct StackNode* next;
};

// Функции для работы со стеком
void stackPush(StackNode*& head, string data) {
    StackNode* first = new StackNode;
    first->value = data;
    first->next = head;
    head = first;
}

StackNode* stackLast(StackNode* head) {
    if (head == 0)
        return 0;
    while (head->next)
        head = head->next;
    return head;
}

void stackPushBack(StackNode* head, string data) {
    StackNode* last = stackLast(head);
    StackNode* next = new StackNode;
    next->value = data;
    next->next = 0;
    last->next = next;
}

string stackPop(StackNode*& head) {
    StackNode* prev = 0;
    if (head == 0)
        return 0;
    prev = head;
    string val = head->value;
    head = head->next;
    delete prev;
    return val;
}

StackNode* stackGetLastButOne(StackNode* head) {
    if (head == 0 || head->next == 0)
        return 0;
    while (head->next->next)
        head = head->next;
    return head;
}

string stackPopBack(StackNode* head) {
    string value;
    StackNode* lastbn = 0;
    if (!head)
        return 0;

    lastbn = stackGetLastButOne(head);
    value = lastbn->next->value;

    if (lastbn == 0) {
        delete head;
        head = 0;
    }
    else {
        delete lastbn->next;
        lastbn->next = 0;
    }
    return value;
}

int stackSize(StackNode* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

StackNode* stackCreate(const string& data) {
    StackNode* node = new StackNode;
    node->value = data;
    node->next = 0;
    return node;
}

void stackAdd(StackNode*& head, const string& data) {
    if (!head)
        stackPush(head, data);
    else
        stackPushBack(head, data);
}

string stackTake(StackNode*& head) {
    return stackSize(head) > 1 ? stackPopBack(head) : stackPop(head);
}

void stackClear(StackNode* head) {
    StackNode* prev = 0;
    while (head->next) {
        prev = head;
        head = head->next;
        delete prev;
    }
    delete head;
}

void stackPrint(StackNode* head, ostream& sout) {
    while (head) {
        sout << head->value << " ";
        head = head->next;
    }
}

/*
*   Функция для ввода данных в терминал
*   При вызове функции нужно указать получаемые данные в скобках,
*   т.е. readValue<int>() - получить число.
*   prompt - текст перед вводом
*   value - значение для заполнения
*/
template <typename T>
T readValue(const char* prompt = "") {
    T value = 0;
    cout << prompt;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cout << "Некорректный ввод. Введите значение: ";
            cin.clear();
            // numeric_limits<streamsize> это предел количества знаков в streamsize (вернёт число)
            // нужно чтобы очистить максимальное количество оставшихся символов в буфере до новой строки
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

bool isOperation(const string& str) {
    auto res = weights.find(str);
    return res != weights.end();
}

bool isNumber(const string& str) {
    string::const_iterator it = str.begin();
    while (it != str.end() && isdigit(*it)) ++it;
    return !str.empty() && it == str.end();
}

vector<string> tokenize(const string& text) {
    vector<string> tokens{};
    istringstream input(text);

    for (string token; getline(input, token, ' ');)
        tokens.push_back(token);
    return tokens;
}

bool shouldMoveOperation(string token, StackNode* opstack) {
    StackNode* last = stackLast(opstack);
    return weights.find(last->value)->second >= weights.find(token)->second;
}

void print(string str, ostream& os1, ofstream& os2) {
    os1 << str;
    if(os2.is_open()) {
        os2 << str;
    }
    os2.close();
}

string reversePolishNotation(string& inpt_str, ofstream& ofs, bool silent = false) {
    variables.clear();
    string current_str;
    vector<string> str_tokens = tokenize(inpt_str);
    StackNode* outStack = 0;
    StackNode* opStack = 0;
    for (const auto& token : str_tokens) {
        if (!silent) {
            print("Токен: " + token + "\nВывод: ", cout, ofs);
            stackPrint(outStack, cout); stackPrint(outStack, ofs);
            print("\nОпс: ", cout, ofs);
            stackPrint(opStack, cout); stackPrint(opStack, ofs);
            print("\n\n", cout, ofs);
        }
        if (isNumber(token))
            stackAdd(outStack, token);
        else if (isOperation(token)) {
            if (!opStack)
                stackPush(opStack, token);
            else if (token == "(")
                stackAdd(opStack, token);
            else if (token == ")") {
                while (opStack && current_str != "(") {
                    current_str = stackTake(opStack);
                    stackAdd(outStack, current_str);
                    StackNode* last = stackLast(opStack);
                    if (!last)
                        throw "Обнаружена непарная скобка";
                    current_str = last->value;
                }
                if (!opStack)
                    throw "Обнаружена непарная скобка";
                current_str.clear();
                stackTake(opStack);
            } else if (shouldMoveOperation(token, opStack)) {
                stackPushBack(outStack, stackTake(opStack));
                stackAdd(opStack, token);
            } else
                stackPushBack(opStack, token);
        }
        else {
            if (silent) {
                stackAdd(outStack, "1");
            } else {
                auto found = variables.find(token);
                if (found == variables.end()) {
                    print("Введите значение для " + token + ": ", cout, ofs);
                    int var = readValue<int>();
                    ofs << var << endl;
                    variables[token] = var;
                    stackAdd(outStack, to_string(var));
                } else {
                    stackAdd(outStack, to_string(found->second));
                }
            }
        }
    }
    if (!silent)
        print("Перемещение операций в основной стек.\n", cout, ofs);
    while (opStack)
        stackPushBack(outStack, stackTake(opStack));
    if (!silent) {
        print("Результат: ", cout, ofs);
        stackPrint(outStack, cout); stackPrint(outStack, ofs);
        print("\n", cout, ofs);
    }
    string outp;
    while (outStack) {
        outp += outStack->value + ' ';
        outStack = outStack->next;
    }
    outp.pop_back();
    return outp;
}

void polishNotation(string& inpt_str, ofstream& ofs) {
    string inp;
    for(int i = inpt_str.length() - 1; i >= 0; i--) {
        if (inpt_str[i] == '(')
            inp.push_back(')');
        else if (inpt_str[i] == ')')
            inp.push_back('(');
        else
            inp.push_back(inpt_str[i]);
    }
    reverse(inpt_str.begin(), inpt_str.end());
    print("Инверсия инициализированной строки: " + inp + "\n", cout, ofs);
    string outp = reversePolishNotation(inp, ofs);
    reverse(outp.begin(), outp.end());
    print("Инверсия строки завершена.\nФинальный результат: " + outp + "\n", cout, ofs);
}

int computeRpn(string& rpn, ofstream& ofs, bool inverted = false, bool silent = false) {
    istringstream reader(rpn);
    StackNode* outStack = 0;
    string token;
    while (!reader.eof()) {
        reader >> token;
        if (isNumber(token)) {
            stackAdd(outStack, token);
        } else {
            if (stackSize(outStack) < 2)
                throw "Неверный порядок выполнения операций";
            int left, right;
            if (inverted) {
                left = stoi(stackTake(outStack));
                right = stoi(stackTake(outStack));
            }
            else {
                right = stoi(stackTake(outStack));
                left = stoi(stackTake(outStack));
            }

            switch (token[0]) {
                case '+':
                    if (!silent) {
                        print(to_string(left) + " + " + to_string(right) + " = " + to_string(left + right) + '\n', cout, ofs);
                        stackAdd(outStack, to_string(left + right));
                    }
                    break;
                case '-':
                    if (!silent) {
                        print(to_string(left) + " - " + to_string(right) + " = " + to_string(left - right) + '\n', cout, ofs);
                        stackAdd(outStack, to_string(left - right));
                    }
                    break;
                case '/':
                    if (!silent) {
                        if (right == 0) {
                            throw "Деление на 0";
                        }
                        print(to_string(left) + " / " + to_string(right) + " = " + to_string(left / right) + '\n', cout, ofs);
                        stackAdd(outStack, to_string(left / right));
                    }
                    break;
                case '*':
                    if (!silent) {
                        print(to_string(left) + " * " + to_string(right) + " = " + to_string(left * right) + '\n', cout, ofs);
                        stackAdd(outStack, to_string(left * right));
                    }
                    break;
                case '^':
                    if (!silent) {
                        print(to_string(left) + " ^ " + to_string(right) + " = " + to_string((int)pow(left, right)) + '\n', cout, ofs);
                        stackAdd(outStack, to_string(pow(left, right)));
                    }
                    break;
                default:
                    string errt = "Неизвестный оператор " + token;
                    throw errt.c_str();
            }
        }
    }
    if (stackSize(outStack) != 1)
        throw "Неверный размер стека";
    return stoi(stackPop(outStack));
}

int computePn(string& rpn, ofstream& ofs, bool silent = false) {
    vector<string> tokens = tokenize(rpn);
    reverse(tokens.begin(), tokens.end());
    string rev;
    for(const auto& token : tokens)
        rev += token + ' ';
    rev.pop_back();
    return computeRpn(rev, ofs, true, silent);
}

int checkStandartNotation(string& rpn) {
    istringstream reader(rpn);
    bool isbracket = false;
    int curritem = -1, count = 0; // Если число - 2, если скобка - 0, если операнд - 1
    string token;
    while(!reader.eof()) {
        reader >> token;
        if(token == "+" || token == "-" || token == "*" || token == "/") {
            if(curritem == 1) {
                throw "Неверный порядок операндов и операций";
            } else {
                curritem = 1;
                count++;
            }
        }
        else if(token == "(") {
            if(curritem == 0) {
                throw "Неверный порядок операндов и операций";
            } else {
                isbracket = true;
                curritem = 0;
                count++;
            }
        }
        else if(token == ")") {
            if(curritem == 0) {
                throw "Неверный порядок операндов и операций";
            } else {
                isbracket = false;
                curritem = 0;
                count++;
            }
        }
        else if(stoi(token)) {
            if(curritem == 2) {
                throw "Неверный порядок операндов и операций";
            }
            else {curritem = 2; count++;}
        }
        else {
            throw "Введён неизвестный операнд или операция";
        }
    }
    if(count % 2 == 0) {
        throw "Неправильное количество операндов";
    }
    if(curritem == 1) {
        throw "Неправильное количество операндов";
    }
    if(isbracket == true) {
        throw "Скобка не закрыта";
    }
}

int PractRab3(unsigned short number_of_task)
{
    ofstream ofs ("/Users/lemeshkoaleksey/!C++ Projects/2023/Pract_rabs_2_sem_2023/output.txt");
    while (true) {
        cout << "\nВыберите номер задания, к которому хотите получить доступ:\n"
                "1. Конвертировать выражение в польскую запись\n"
                "2. Конвертировать выражение в обратную польскую запись\n"
                "3. Проверка правильности введённого выражения в обычной записи\n"
                "4. Проверка правильности введённого выражения в польской записи\n"
                "5. Проверка правильности введённого выражения в обратной польской записи\n"
                "6. Посчитать значение выражения в польской записи\n"
                "7. Посчитать значение выражения в обратной польской записи\n"
                "Для возвращения в предыдущее меню введите 0\n\n"
                "Номер: ";
        cin >> number_of_task;
        switch (number_of_task) {
            case 0:
                return 0;
            case 1: {
                string yourInput;
                cout << "Введите выражение в обычной записи: ";
                cin.clear();
                cin.ignore();
                getline(cin, yourInput);
                try {
                    polishNotation(yourInput, ofs);
                } catch (const char* data) {
                    cout << "Ошибка: " << data << endl;
                }
                break;
            }
            case 2: {
                string yourInput;
                cout << "Введите выражение в обычной записи: ";
                cin.clear();
                cin.ignore();
                getline(cin, yourInput);
                try {
                    reversePolishNotation(yourInput, ofs);
                } catch (const char* data) {
                    cout << "Ошибка: " << data << endl;
                }
                break;
            }
            case 3: {
                string yourInput;
                cout << "Введите выражение в обычной записи: ";
                cin.clear();
                cin.ignore();
                getline(cin, yourInput);
                try {
                    checkStandartNotation(yourInput);
                    cout << "Выражение введено верно\n";
                } catch (...) {
                    cout << "Выражение введено неверно" << endl;
                }
                break;
            }
            case 4: {
                string yourInput;
                cout << "Введите выражение в польской записи: ";
                cin.clear();
                cin.ignore();
                getline(cin, yourInput);
                try {
                    computePn(yourInput, ofs, true);
                    cout << "Выражение введено верно\n";
                } catch (const char* data) {
                    cout << "Выражение введено неверно: " << data << endl;
                }
                break;
            }
            case 5: {
                string yourInput;
                cout << "Введите выражение в обратной польской записи: ";
                cin.clear();
                cin.ignore();
                getline(cin, yourInput);
                try {
                    computeRpn(yourInput, ofs, false, true);
                    cout << "Выражение введено верно\n";
                } catch (const char* data) {
                    cout << "Выражение введено неверно: " << data << endl;
                }
                break;
            }
            case 6: {
                string yourInput;
                cout << "Введите выражение в польской записи: ";
                cin.clear();
                cin.ignore();
                getline(cin, yourInput);
                try {
                    cout << "Результат: " << computePn(yourInput, ofs) << endl;
                } catch (const char* data) {
                    cout << "Ошибка разбора строки: " << data << endl;
                }
                break;
            }
            case 7: {
                string yourInput;
                cout << "Введите выражение в обратной польской записи: ";
                cin.clear();
                cin.ignore();
                getline(cin, yourInput);
                try {
                    cout << "Результат: " << computeRpn(yourInput, ofs) << endl;
                } catch (...) {
                    cout << "Ошибка разбора строки " << endl;
                }
                break;
            }
            default:
                cout << "\nЗадания с таким номером не существует\n";
                break;
        }
    }
}