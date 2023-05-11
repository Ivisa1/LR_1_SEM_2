#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

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
    if (head == NULL)
        return NULL;
    while (head->next)
        head = head->next;
    return head;
}

void stackPushBack(StackNode* head, string data) {
    StackNode* last = stackLast(head);
    StackNode* next = new StackNode;
    next->value = data;
    next->next = NULL;
    last->next = next;
}

string stackPop(StackNode*& head) {
    StackNode* prev = NULL;
    if (head == NULL)
        return NULL;
    prev = head;
    string val = head->value;
    head = head->next;
    delete prev;
    return val;
}

StackNode* stackGetLastButOne(StackNode* head) {
    if (head == NULL || head->next == NULL)
        return NULL;
    while (head->next->next)
        head = head->next;
    return head;
}

string stackPopBack(StackNode* head) {
    string value;
    StackNode* lastbn = NULL;
    if (!head)
        return NULL;

    lastbn = stackGetLastButOne(head);
    value = lastbn->next->value;

    if (lastbn == NULL) {
        delete head;
        head = NULL;
    }
    else {
        delete lastbn->next;
        lastbn->next = NULL;
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
    node->next = NULL;
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
    StackNode* prev = NULL;
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

bool isLiteral(const string& str) {
    auto res = variables.find(str);
    return res != variables.end();
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

void print(string str, ostream& os1, ostream& os2) {
    os1 << str;
    os2 << str;
}

string reversePolishNotation(string& inpt_str, ofstream& ofs, bool silent = false) {
    variables.clear();
    string current_str;
    vector<string> str_tokens = tokenize(inpt_str);
    StackNode* outStack = NULL;
    StackNode* opStack = NULL;
    for (const auto& token : str_tokens) {
        if (!silent) {
            print("Token: " + token + "\nOut: ", cout, ofs);
            stackPrint(outStack, cout); stackPrint(outStack, ofs);
            print("\nOps: ", cout, ofs);
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
                        throw "Unpaired bracket encountered";
                    current_str = last->value;
                }
                if (!opStack)
                    throw "Unpaired bracket encountered";
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
                    print("Enter value for " + token + ": ", cout, ofs);
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
        print("Moving operations to main stack.\n", cout, ofs);
    while (opStack)
        stackPushBack(outStack, stackTake(opStack));
    if (!silent) {
        print("Result: ", cout, ofs);
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
    print("Reversed initial string: " + inp + "\n", cout, ofs);
    string outp = reversePolishNotation(inp, ofs);
    reverse(outp.begin(), outp.end());
    print("Reversing back.\nFinal result: " + outp + "\n", cout, ofs);
}

int computeRpn(string& rpn, ofstream& ofs, bool inverted = false, bool silent = false) {
    istringstream reader(rpn);
    StackNode* outStack = NULL;
    string token;
    while (!reader.eof()) {
        reader >> token;
        if (isNumber(token)) {
            stackAdd(outStack, token);
        } else {
            if (stackSize(outStack) < 2)
                throw "Invalid operation order";
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
                    if (!silent)
                        print(to_string(left) + " + " + to_string(right) + " = " + to_string(left + right) + '\n', cout, ofs);
                    stackAdd(outStack, to_string(left + right));
                    break;
                case '-':
                    if (!silent)
                        print(to_string(left) + " - " + to_string(right) + " = " + to_string(left - right) + '\n', cout, ofs);
                    stackAdd(outStack, to_string(left - right));
                    break;
                case '/':
                    if (!silent)
                        print(to_string(left) + " / " + to_string(right) + " = " + to_string(left / right) + '\n', cout, ofs);
                    stackAdd(outStack, to_string(left / right));
                    break;
                case '*':
                    if (!silent)
                        print(to_string(left) + " * " + to_string(right) + " = " + to_string(left * right) + '\n', cout, ofs);
                    stackAdd(outStack, to_string(left * right));
                    break;
                case '^':
                    if (!silent)
                        print(to_string(left) + " ^ " + to_string(right) + " = " + to_string((int)pow(left, right)) + '\n', cout, ofs);
                    stackAdd(outStack, to_string(pow(left, right)));
                    break;
                default:
                    string errt = "Unknown operator " + token;
                    throw errt.c_str();
            }
        }
    }
    if (stackSize(outStack) != 1)
        throw "Invalid stack size";
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

int PractRab3(unsigned short number_of_task)
{
    ofstream ofs ("output.txt");
    while (true) {
        cout <<
             "Choose a category from below:\n"
             "0. Exit\n"
             "1. Convert expression into polish notation\n"
             "2. Convert expression into reverse polish notation\n"
             "3. Validate mathematical expression\n"
             "4. Validate polish notation expression\n"
             "5. Validate reverse polish notation expression\n"
             "6. Compute expression given in polish notation\n"
             "7. Compute expression given in reverse polish notation\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
            case 0:
                return 0;
            case 1: {
                string inp;
                cout << "Enter mathematical expression: ";
                getline(cin, inp);
                try {
                    polishNotation(inp, ofs);
                } catch (const char* data) {
                    cout << "Error! " << data << endl;
                }
            }
                break;
            case 2: {
                string yourInput;
                cout << "Введите выражение в обычной записи: ";
                getline(cin, yourInput);
                try {
                    reversePolishNotation(yourInput, ofs);
                } catch (const char* data) {
                    cout << "Ошибка " << data << endl;
                }
            }
                break;
            case 3: {
                string yourInput;
                cout << "Введите выражение в обычной записи: ";
                getline(cin, yourInput);
                try {
                    string outp = reversePolishNotation(yourInput, ofs, true);
                    computeRpn(outp, ofs, false, true);
                    cout << "Выражение введено верно\n";
                } catch (...) {
                    cout << "Выражение введено неверно" << endl;
                }
            }
                break;
            case 4: {
                string yourInput;
                cout << "Введите выражение в польской записи: ";
                getline(cin, yourInput);
                try {
                    computePn(yourInput, ofs, true);
                    cout << "Выражение введено верно\n";
                } catch (const char* data) {
                    cout << "Выражение введено неверно " << data << endl;
                }
            }
                break;
            case 5: {
                string yourInput;
                cout << "Введите выражение в обратной польской записи: ";
                getline(cin, yourInput);
                try {
                    computeRpn(yourInput, ofs, false, true);
                    cout << "Выражение введено верно\n";
                } catch (const char* data) {
                    cout << "Выражение введено неверно " << data << endl;
                }
            }
                break;
            case 6: {
                string yourInput;
                cout << "Введите выражение в польской записи: ";
                getline(cin, yourInput);
                try {
                    cout << "Результат: " << computePn(yourInput, ofs) << endl;
                } catch (const char* data) {
                    cout << "Ошибка разбора строки " << data << endl;
                }
            }
                break;
            case 7: {
                string yourInput;
                cout << "Введите выражение в обратной польской записи: ";
                getline(cin, yourInput);
                try {
                    cout << "Результат: " << computeRpn(yourInput, ofs) << endl;
                } catch (const char* data) {
                    cout << "Ошибка разбора строки " << data << endl;
                }
            }
                break;
            default:
                cout << "\nЗадания с таким номером не существует\n";
                break;
        }
    }
}