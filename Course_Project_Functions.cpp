#include <iostream>
#include <iomanip>
#include <ctime>
#include <queue>

#define output_tree "/Users/lemeshkoaleksey/!C++ Projects/2023/Pract_rabs_2_sem_2023/output_tree.txt"

using namespace std;

struct Tree
{
    int value;       //ключ – значение узла, типа int
    Tree* left;    //указатель на левого потомка
    Tree* right;   //указатель на правого потомка
};

Tree* CreateTree(int value) {
    Tree* root = (Tree*)malloc(sizeof(Tree));
    root->left = root->right = NULL;
    root->value = value;
    return root;
}

int SearchElement(int key, Tree* tree) {
    if (tree != NULL)
    {
        if (key == tree->value) {
            cout << "Искомое число найдено. ";
            return 0;
        }
        else if (key < tree->value) {
            return SearchElement(key, tree->left);
        }
        else {
            return SearchElement(key, tree->right);
        }
    }
    else {
        cout << "Искомое число не найдено. ";
        return 0;
    }
}

Tree* DeleteElement(int key, Tree* tree) {
    if(tree == NULL) {
        cout << "Искомое число не найдено. ";
        return tree;
    }
    else if(key == tree->value) {
        cout << "Искомое число удалено. ";
        Tree* tmp;
        if(tree->right == NULL)
            tmp = tree->left;
        else {
            Tree* ptr = tree->right;
            if(ptr->left == NULL){
                ptr->left = tree->left;
                tmp = ptr;
            }
            else {
                Tree* pmin = ptr->left;
                while(pmin->left != NULL){
                    ptr  = pmin;
                    pmin = ptr->left;
                }
                ptr->left   = pmin->right;
                pmin->left  = tree->left;
                pmin->right = tree->right;
                tmp = pmin;
            }
        }
        delete tree;
        return tmp;
    }
    else if (key < tree->value) {
        tree->left = DeleteElement(key, tree->left);
    }
    else {
        tree->right = DeleteElement(key, tree->right);
    }
    return tree;
}

void InsertElement(int key, Tree* root) {        // (новое ключевое значение, указатель на текущий узел)
    if (key < root->value)            // если новое ключевое значение меньше чем ключевое значение в узле
    {
        if (root->left!= NULL)           // и если левый указатель узла инициализирован
            InsertElement(key, root->left);      // функция вызывает саму себя, для левого узла потомка
        else                              // иначе (если левый потомок не инициализирован)
        {
            root->left = new Tree;        // функция создаст и поместит новый элемент на место левого потомка.
            root->left->value = key;  // внесёт новое ключевое значение в элемент.
            root->left->left = NULL;      // установит левый дочерний указатель
            root->left->right = NULL;     // и правый дочерний указатель в NULL.
        }
    }
    else if (key >= root->value) {     // иначе, если новое ключевое значение не меньше ключевого значения в узле

        if (root->right != NULL)          // и если правый указатель инициализирован,
            InsertElement(key, root->right);     // то функция вызывает саму себя, для правого потомка
        else                              // иначе(если правый потомок не инициализирован)
        {
            root->right = new Tree;       // функция создаст и поместит новый элемент на место правого потомка.
            root->right->value = key; // внесёт новое ключевое значение в элемент.
            root->right->left = NULL;     // установит левый дочерний указатель
            root->right->right = NULL;    // и правый дочерний указатель в NULL.
        }
    }
}

void PrintTree(Tree *tree, int level, bool isConsole)
{
    if(tree)
    {
        PrintTree(tree->left,level + 1, isConsole);
        if(isConsole) {
            for (int i = 0; i < level; i++) cout << "         ";
            cout << "---> " << setw(3) << tree->value << endl;
        }
        else {
            ofstream File;
            File.open(output_tree, ios::app);
            for (int i = 0; i < level; i++) File << "         ";
            File << "---> " << setw(3) << tree->value << endl;
            File.close();
        }
        PrintTree(tree->right,level + 1, isConsole);
    }
}

//void sizeTree(Tree* root, int &size_count) {
//    if (root) {
//        size_count++;
//        sizeTree(root->left, size_count);
//        sizeTree(root->right, size_count);
//    }
//}

//функция выводит узлы дерева, вызывает функцию вывода связей
//void printTree(Tree* tree, Tree* prev, bool isRight, ofstream& f2) {
//    if (tree == NULL)//пустое дерево
//        return;
//    string prev_str = "    ";//отступ по уровням (длина как для стрелки)
//    Tree* tmp = new Tree;//новая связь
//    printTree(tree->right, tmp, 1, f2);//правое поддерево
//    if (!prev)//если нет предыдущего узла (предка) -> корень дерева
//        tmp->str = "-->";//связь корня дерева
//    else if (isRight) {//если правое поддерево
//        tmp->str = ".-->";//связь правого поддерева
//        prev_str = "   |";//в отступ по уровням добавляем черту (дерево идет вширь)
//    }
//    else {//в противном случае - левое поддерево
//        tmp->str = "`-->";//левое поддерево
//        prev->str = prev_str;//отступ по уровням не меняется
//    }
//    int count = 0;//уровень узла
//    showTrunk(tmp, count, f2);//выводим связи дерева - стебли
//    f2 << tree->val << endl;//выводим значение узла
//    if (prev)//задаем строку отступов для узла, если есть поддеревья
//        prev->str = prev_str;
//    tmp->str = "   |";//в отступ по уровням добавляем черту (дерево идет вширь)
//    printTree(tree->left, tmp, 0, f2);//левое поддерево
//}

//void showTrunk(Tree* p, int &count, ofstream& f2) {//функция вывода связей дерева
//    if (p == NULL)//если нет поддеревьев
//        return;
//    showTrunk(p->prev, count, f2);//выводим предыдущий узел
//    count++;//увеличиваем уровень
//    f2 << p->str;//выводим отступы и связи
//}

void PreOrderTravers(Tree* tree) {
    if (tree) {
        cout << tree->value << " ";
        PreOrderTravers(tree->left);
        PreOrderTravers(tree->right);
    }
}

void PostOrderTravers(Tree* tree) {
    if (tree) {
        PostOrderTravers(tree->left);
        PostOrderTravers(tree->right);
        std::cout << tree->value << " ";
    }
}

void BreadthFirstSearch(Tree *tree){
    queue<Tree *> nodeQueue;
    Tree* root = new Tree;
    root = tree;
    nodeQueue.push(root);
    while (!nodeQueue.empty()) {
        root = nodeQueue.front();
        cout << root->value << " ";
        nodeQueue.pop();
        if (root->left) {
            nodeQueue.push (root-> left); // Сначала поместите левое поддерево в команду
        }
        if (root->right) {
            nodeQueue.push (root-> right); // Поместить правильное поддерево в команду
        }
    }
}

void DestroyTree(Tree *tree)
{
    if(tree != NULL)	    	        // если узел дерева существует
    {					// функция вызовет сама себя
        DestroyTree(tree->left);	// сначала для левого потомка,
        DestroyTree(tree->right);  	// после для правого потомка.
        delete tree;			// если потомков нет, она удалит
    }
}

int CourseProject(unsigned short &number_of_task) {
    Tree *tree = new Tree;
    int key;
    while(true) {
        cout << "\nВыберите номер задания, к которому хотите получить доступ:\n"
                "1. Создание бинарного дерева с рандомными элементами\n"
                "2. Создание бинарного дерева с определёнными элементами\n"
                "3. Создание бинарного дерева с числами из файла\n"
                "4. Вывод дерева в консоль\n"
                "5. Вывод дерева в файл\n"
                "6. Вставка элемента и время вставки\n"
                "7. Удаление элемента и время удаления\n"
                "8. Получение элемента и время получения\n"
                "9. Прямой обход\n"
                "10. Обратный обход\n"
                "11. Обход в ширину\n"
                "12. Генерация и выполнение файловых заданий\n"
                "Для возвращения в предыдущее меню введите 0\n\n"
                "Номер: ";
        cin >> number_of_task;
        switch (number_of_task) {
            case 0: {
                cout << "\nВозвращение в предыдущее меню...\n";
                DestroyTree(tree);
                return 0;
            }
            case 1: {
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                PrintTree(tree, 0, 1);
                break;
            }
            case 5: {
                ofstream File;
                File.open(output_tree);
                File.clear();
                File.close();
                PrintTree(tree, 0, 0);
                break;
            }
            case 6: {
                cout << "Введите число, которое хотите добавить в дерево: ";
                cin >> key;
                unsigned int start_time =  clock();
                InsertElement(key, tree);
                unsigned int end_time = clock(); // конечное время
                unsigned int search_time = end_time - start_time; // искомое время
                cout << "Число добавлено. Время выполнения: " << search_time << " милисекунд\n";
                break;
            }
            case 7: {
                cout << "Введите число, которое хотите удалить из дерева: ";
                cin >> key;
                unsigned int start_time =  clock();
                tree = DeleteElement(key, tree);
                unsigned int end_time = clock(); // конечное время
                unsigned int search_time = end_time - start_time; // искомое время
                cout << "Время выполнения: " << search_time << " милисекунд\n";
                break;
            }
            case 8: {
                cout << "Введите число, которое хотите найти в дереве: ";
                cin >> key;
                unsigned int start_time =  clock();
                SearchElement(key, tree);
                unsigned int end_time = clock(); // конечное время
                unsigned int search_time = end_time - start_time; // искомое время
                cout << "Время выполнения: " << search_time << " милисекунд\n";
                break;
            }
            case 9: {
                PreOrderTravers(tree);
                cout << "\n";
                break;
            }
            case 10: {
                PostOrderTravers(tree);
                cout << "\n";
                break;
            }
            case 11: {
                BreadthFirstSearch(tree);
                cout << "\n";
                break;
            }
            case 12: {
                break;
            }
            default: {
                cout << "\nЗадания с таким номером не существует\n";
                break;
            }
        }
    }
}
