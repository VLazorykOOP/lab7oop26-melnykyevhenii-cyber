#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

// ==========================================
// ЗАВДАННЯ 1: Пошук мінімуму в масиві
// ==========================================
template <typename T>
T findMin(T arr[], int size) {
    T minVal = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }
    return minVal;
}

// Специфікація для char* (порівняння рядків лексикографічно)
template <>
char* findMin<char*>(char* arr[], int size) {
    char* minVal = arr[0];
    for (int i = 1; i < size; ++i) {
        if (strcmp(arr[i], minVal) < 0) {
            minVal = arr[i];
        }
    }
    return minVal;
}

// ==========================================
// ЗАВДАННЯ 2: Бінарний пошук та сортування
// ==========================================
template <typename T>
void bubbleSort(T arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

template <>
void bubbleSort<char*>(char* arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                char* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

template <typename T>
int binarySearch(T arr[], int size, T key) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) return mid;
        if (arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

template <>
int binarySearch<char*>(char* arr[], int size, char* key) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(arr[mid], key);
        if (cmp == 0) return mid;
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// ==========================================
// ЗАВДАННЯ 3: Шаблон класу Матриця
// ==========================================
template <typename T>
class Matrix {
private:
    int rows, cols;
    T** data;
public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new T * [rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols]();
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; ++i) delete[] data[i];
        delete[] data;
    }

    // Конструктор копіювання для коректного присвоєння
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new T * [rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; ++j) data[i][j] = other.data[i][j];
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (this == &other) return *this;
        for (int i = 0; i < rows; ++i) delete[] data[i];
        delete[] data;

        rows = other.rows; cols = other.cols;
        data = new T * [rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; ++j) data[i][j] = other.data[i][j];
        }
        return *this;
    }

    T* operator[](int index) { return data[index]; }

    Matrix operator+(const Matrix& other) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    void input() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << "Елемент [" << i << "][" << j << "]: ";
                cin >> data[i][j];
            }
        }
    }

    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << data[i][j] << "\t";
            }
            cout << endl;
        }
    }
};

// ==========================================
// ЗАВДАННЯ 4: Однозв'язний список з Ітератором
// ==========================================
template <typename T>
struct Node {
    T val;
    Node* next;
    Node(T v) : val(v), next(nullptr) {}
};

template <typename T>
class List {
private:
    Node<T>* head;
public:
    List() : head(nullptr) {}
    ~List() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(T val) {
        if (!head) {
            head = new Node<T>(val);
            return;
        }
        Node<T>* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = new Node<T>(val);
    }

    // Вкладений клас-ітератор
    class Iterator {
    private:
        Node<T>* curr;
    public:
        Iterator(Node<T>* node) : curr(node) {}

        T& operator*() { return curr->val; }

        Iterator& operator++() {
            if (curr) curr = curr->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return curr != other.curr;
        }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

// ==========================================
// Головна функція з меню користувача
// ==========================================
int main() {
    // Встановлення кодування для коректного відображення в консолі
    std::setlocale(LC_CTYPE, "ukr");

    int choice;
    do {
        cout << "\n=== МЕНЮ ЛАБОРАТОРНОЇ РОБОТИ (Варіант 12) ===\n";
        cout << "1. Завдання 1: Пошук мінімуму в масиві (Шаблон + Специфікація char*)\n";
        cout << "2. Завдання 2: Бінарний пошук у масиві (Шаблон + Специфікація char*)\n";
        cout << "3. Завдання 3: Робота з шаблоном класу Матриця\n";
        cout << "4. Завдання 4: Однозв'язний список List та Ітератор\n";
        cout << "0. Вихід\n";
        cout << "Введіть номер завдання: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int typeChoice, size;
            cout << "Оберіть тип даних (1 - int, 2 - С-рядок char*): ";
            cin >> typeChoice;
            cout << "Введіть розмір масиву: ";
            cin >> size;

            if (typeChoice == 1) {
                int* arr = new int[size];
                for (int i = 0; i < size; ++i) {
                    cout << "Елемент [" << i << "]: ";
                    cin >> arr[i];
                }
                cout << "Мінімальний елемент: " << findMin(arr, size) << endl;
                delete[] arr;
            }
            else {
                char** arr = new char* [size];
                for (int i = 0; i < size; ++i) {
                    arr[i] = new char[100];
                    cout << "Рядок [" << i << "]: ";
                    cin >> arr[i];
                }
                cout << "Мінімальний рядок (лексикографічно): " << findMin(arr, size) << endl;
                for (int i = 0; i < size; ++i) delete[] arr[i];
                delete[] arr;
            }
            break;
        }
        case 2: {
            int typeChoice, size;
            cout << "Оберіть тип даних (1 - int, 2 - С-рядок char*): ";
            cin >> typeChoice;
            cout << "Введіть розмір масиву: ";
            cin >> size;

            if (typeChoice == 1) {
                int* arr = new int[size];
                for (int i = 0; i < size; ++i) {
                    cout << "Елемент [" << i << "]: ";
                    cin >> arr[i];
                }
                bubbleSort(arr, size);
                cout << "Відсортований масив: ";
                for (int i = 0; i < size; ++i) cout << arr[i] << " ";
                cout << "\nВведіть ключ для бінарного пошуку: ";
                int key;
                cin >> key;
                int res = binarySearch(arr, size, key);
                if (res != -1) cout << "Знайдено за індексом: " << res << endl;
                else cout << "Елемент не знайдено!" << endl;
                delete[] arr;
            }
            else {
                char** arr = new char* [size];
                for (int i = 0; i < size; ++i) {
                    arr[i] = new char[100];
                    cout << "Рядок [" << i << "]: ";
                    cin >> arr[i];
                }
                bubbleSort(arr, size);
                cout << "Відсортовані рядки:\n";
                for (int i = 0; i < size; ++i) cout << arr[i] << "\n";

                char key[100];
                cout << "Введіть шуканий рядок: ";
                cin >> key;
                int res = binarySearch(arr, size, key);
                if (res != -1) cout << "Знайдено за індексом: " << res << endl;
                else cout << "Рядок не знайдено!" << endl;

                for (int i = 0; i < size; ++i) delete[] arr[i];
                delete[] arr;
            }
            break;
        }
        case 3: {
            int r, c;
            cout << "Введіть кількість рядків та стовпців матриць: ";
            cin >> r >> c;

            Matrix<int> M1(r, c);
            Matrix<int> M2(r, c);

            cout << "Введіть першу матрицю:\n";
            M1.input();
            cout << "Введіть другу матрицю:\n";
            M2.input();

            cout << "\nМатриця 1:\n"; M1.print();
            cout << "\nМатриця 2:\n"; M2.print();

            Matrix<int> M3 = M1 + M2;
            cout << "\nРезультат додавання (M1 + M2):\n";
            M3.print();
            break;
        }
        case 4: {
            List<double> myList;
            int count;
            cout << "Скільки дійсних чисел додати до списку? ";
            cin >> count;

            for (int i = 0; i < count; ++i) {
                double val;
                cout << "Значення: ";
                cin >> val;
                myList.push_back(val);
            }

            cout << "Виведення елементів списку за допомогою Ітератора:\n";
            for (List<double>::Iterator it = myList.begin(); it != myList.end(); ++it) {
                cout << *it << " -> ";
            }
            cout << "NULL\n";
            break;
        }
        case 0:
            cout << "Програма завершена.\n";
            break;
        default:
            cout << "Невірний вибір! Спробуйте ще раз.\n";
        }
    } while (choice != 0);

    return 0;
}