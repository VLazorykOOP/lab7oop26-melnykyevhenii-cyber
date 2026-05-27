#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

// Підключаємо заголовок для роботи з кодуванням Windows консолі
#ifdef _WIN32
#include <windows.h>
#endif

// ============================================================================
// КОРИСТУВАЦЬКИЙ ТИП ДАНИХ (Аналог TLong з методичних вказівок)
// ============================================================================
class TLong {
    long long hi, lo;
public:
    TLong() : hi(0), lo(0) {}
    TLong(long long h, long long l) : hi(h), lo(l) {}

    TLong(const TLong& s) : hi(s.hi), lo(s.lo) {}

    TLong& operator=(const TLong& s) {
        hi = s.hi;
        lo = s.lo;
        return *this;
    }

    bool operator>(const TLong& s) const {
        if (hi > s.hi) return true;
        if (hi == s.hi && lo > s.lo) return true;
        return false;
    }

    bool operator==(const TLong& s) const {
        return (hi == s.hi && lo == s.lo);
    }

    friend std::ostream& operator<<(std::ostream& os, const TLong& s) {
        os << "H" << s.hi << ":L" << s.lo;
        return os;
    }
};

// ============================================================================
// ЗАВДАННЯ 1: Шаблони функцій 1 (Задача 1.2)
// ============================================================================
template <typename T>
T find_max_and_count(const T* arr, int size, int& count) {
    T max_val = arr[0];
    count = 1;
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
            count = 1;
        }
        else if (arr[i] == max_val) {
            count++;
        }
    }
    return max_val;
}

template <>
char* find_max_and_count<char*>(char* const* arr, int size, int& count) {
    char* max_val = arr[0];
    count = 1;
    for (int i = 1; i < size; ++i) {
        if (strcmp(arr[i], max_val) > 0) {
            max_val = arr[i];
            count = 1;
        }
        else if (strcmp(arr[i], max_val) == 0) {
            count++;
        }
    }
    return max_val;
}

// ============================================================================
// ЗАВДАННЯ 2: Шаблони функцій 2 (Задача 2.2)
// ============================================================================
template <typename T>
void shell_sort(T* arr, int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; ++i) {
            T temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

template <>
void shell_sort<char*>(char** arr, int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; ++i) {
            char* temp = arr[i];
            int j;
            for (j = i; j >= gap && strcmp(arr[j - gap], temp) > 0; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// ============================================================================
// ЗАВДАННЯ 3: Шаблони класів (Задача 3.2)
// ============================================================================
template <typename T, int SIZE = 50>
class stack_n {
    T m_stk[SIZE];
    int tos;
public:
    stack_n() : tos(0) {}

    void push(T obj) {
        if (tos == SIZE) {
            std::cout << "Стек повний.\n";
            return;
        }
        m_stk[tos++] = obj;
    }

    T pop() {
        if (tos == 0) {
            std::cout << "Стек порожній.\n";
            return T();
        }
        return m_stk[--tos];
    }

    bool is_empty() const { return tos == 0; }
};

// ============================================================================
// ЗАВДАННЯ 4: Ітератори (Задача 4.2)
// ============================================================================
template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class ListIterator {
    Node<T>* current;
public:
    ListIterator(Node<T>* node) : current(node) {}

    T& operator*() { return current->data; }

    ListIterator& operator++() {
        if (current) current = current->next;
        return *this;
    }

    bool operator!=(const ListIterator& other) const {
        return current != other.current;
    }
};

template <typename T>
class ForwardList {
    Node<T>* head;
public:
    ForwardList() : head(nullptr) {}
    ~ForwardList() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_front(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = head;
        head = newNode;
    }

    ListIterator<T> begin() { return ListIterator<T>(head); }
    ListIterator<T> end() { return ListIterator<T>(nullptr); }
};

// ============================================================================
// ГОЛОВНА ТЕСТОВА ПРОГРАМА
// ============================================================================
int main() {
    // НАЛАШТУВАННЯ УКРАЇНСЬКОЇ ЛОКАЛІ ТА КОДУВАННЯ ДЛЯ WINDOWS CONSOLE
#ifdef _WIN32
    SetConsoleCP(1251);       // Налаштування кодування введення (Кирилиця Windows)
    SetConsoleOutputCP(1251); // Налаштування кодування виведення (Кирилиця Windows)
    setlocale(LC_ALL, "Ukrainian"); // Системна локаль для коректного сортування і виведення
#else
    setlocale(LC_ALL, "uk_UA.UTF-8");
#endif

    // Налаштування генератора випадкових чисел
    std::srand(static_cast<unsigned int>(std::time(0)));

    std::cout << "ЛАБОРАТОРНА РОБОТА. ВАРІАНТ 2\n";
    std::cout << "Виконав: Мельник Євгеній, група 141Б\n\n";

    // ------------------------------------------------------------------------
    // Тестування Завдання 1 & 2
    // ------------------------------------------------------------------------
    std::cout << "=== ЗАВДАННЯ 1 ТА 2: Функції-шаблони ===\n";

    // 1. Датчик випадкових чисел (Тип int)
    const int rand_size = 8;
    int rand_arr[rand_size];
    std::cout << "1. Випадковий масив (int): ";
    for (int i = 0; i < rand_size; ++i) {
        rand_arr[i] = std::rand() % 6;
        std::cout << rand_arr[i] << " ";
    }
    int count_int = 0;
    int max_int = find_max_and_count(rand_arr, rand_size, count_int);
    std::cout << "\n   Максимум: " << max_int << " (знайдено " << count_int << " раз(ів))\n";

    shell_sort(rand_arr, rand_size);
    std::cout << "   Після сортування Шелла: ";
    for (int i = 0; i < rand_size; ++i) std::cout << rand_arr[i] << " ";
    std::cout << "\n\n";

    // 2. Введення з файлу (Тип double)
    const char* filename = "input_data.txt";
    std::ofstream out_f(filename);
    if (out_f.is_open()) {
        out_f << "12.4 5.6 19.8 19.8 3.1 14.2";
        out_f.close();
    }

    std::ifstream in_f(filename);
    if (in_f.is_open()) {
        double file_arr[6];
        std::cout << "2. Масив з файлу '" << filename << "' (double): ";
        for (int i = 0; i < 6; ++i) {
            in_f >> file_arr[i];
            std::cout << file_arr[i] << " ";
        }
        in_f.close();

        int count_dbl = 0;
        double max_dbl = find_max_and_count(file_arr, 6, count_dbl);
        std::cout << "\n   Максимум: " << max_dbl << " (знайдено " << count_dbl << " раз(ів))\n";

        shell_sort(file_arr, 6);
        std::cout << "   Після сортування Шелла: ";
        for (int i = 0; i < 6; ++i) std::cout << file_arr[i] << " ";
        std::cout << "\n\n";
    }

    // 3. Специфікація для типу char*
    const int words = 4;
    char* string_arr[words];
    string_arr[0] = (char*)"Volodymyr";
    string_arr[1] = (char*)"Yevhenii";
    string_arr[2] = (char*)"Andrii";
    string_arr[3] = (char*)"Yevhenii";

    std::cout << "3. Масив рядків (char*): ";
    for (int i = 0; i < words; ++i) std::cout << string_arr[i] << " ";

    int count_str = 0;
    char* max_str = find_max_and_count(string_arr, words, count_str);
    std::cout << "\n   Лексикографічний максимум: " << max_str << " (зустрічається " << count_str << " раз(ів))\n";

    shell_sort(string_arr, words);
    std::cout << "   Після сортування Шелла (за алфавітом): ";
    for (int i = 0; i < words; ++i) std::cout << string_arr[i] << " ";
    std::cout << "\n\n";

    // ------------------------------------------------------------------------
    // Тестування Завдання 3
    // ------------------------------------------------------------------------
    std::cout << "=== ЗАВДАННЯ 3: Параметризований стек (Об'єкти TLong) ===\n";
    stack_n<TLong, 5> stk;
    stk.push(TLong(10, 100));
    stk.push(TLong(45, 900));
    stk.push(TLong(5, 12));

    std::cout << "Виштовхуємо елементи зі стеку:\n";
    while (!stk.is_empty()) {
        std::cout << "  " << stk.pop() << "\n";
    }
    std::cout << "\n";

    // ------------------------------------------------------------------------
    // Тестування Завдання 4
    // ------------------------------------------------------------------------
    std::cout << "=== ЗАВДАННЯ 4: Однозв'язний список та Ітератор ===\n";
    ForwardList<int> my_list;
    my_list.push_front(99);
    my_list.push_front(88);
    my_list.push_front(77);

    std::cout << "Елементи списку, знайдені за допомогою ітератора: ";
    for (ListIterator<int> it = my_list.begin(); it != my_list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Надійна затримка консольного вікна Windows
    std::cout << "\nНатисніть Enter для завершення програми...";
    std::cin.ignore(32767, '\n');
    std::cin.get();

    return 0;
}