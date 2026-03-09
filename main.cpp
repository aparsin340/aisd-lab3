#include <iostream>
#include <random>
#include "functions.h"

void setup_io() {
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif
    std::ios::sync_with_stdio(false);
}

class VectorMaker {
private:
    inline static std::random_device rd;
    inline static std::mt19937 rand_int = std::mt19937(rd());
public:
    static std::vector<int> make_random(size_t size) {
        std::vector<int> res;
        res.reserve(size);
        for (size_t i =0 ; i < size; i++) 
            res.push_back(rand_int());
        return res;
    }

    static std::vector<int> make_sorted(size_t size) {
        std::vector<int> res;
        res.reserve(size);
        for (size_t i = 0 ; i < size; i++) {
            res.push_back((int) i);
        }
        return res;
    }

    static std::vector<int> make_reverse_sorted(size_t size) {
        std::vector<int> res;
        res.reserve(size);
        for (size_t i = 0 ; i < size; i++) {
            res.push_back((int) (size - i));
        }
        return res;
    }
};

void display_results(const std::vector<stats>& results, std::string name) {
    double avg_comparison_count = 0;
    double avg_copy_count = 0;
    std::cout << name << "\n";
    for (stats el: results) {
        avg_comparison_count += el.comparison_count;
        avg_copy_count += el.copy_count;
    }
    avg_comparison_count /= results.size();
    avg_copy_count /= results.size();
    std::cout << "\tСравнения: " << avg_comparison_count << "\n";
    std::cout << "\tКопирования: " << avg_copy_count << "\n";
}

void task_a(size_t size, size_t tests_count = 100) {
    std::vector<stats> insertion_results;
    std::vector<stats> shaker_results;
    std::vector<stats> qsort_results;

    std::vector<int> temp_vec;
    LinkedList<int> temp_list;
    for (size_t test = 0; test < tests_count; test++) {
        temp_list = VectorMaker::make_random(size);
        insertion_results.push_back(insertion_sort(temp_list));

        temp_vec = VectorMaker::make_random(size);
        shaker_results.push_back(shaker_sort(temp_vec));

        temp_vec = VectorMaker::make_random(size);
        qsort_results.push_back(quick_sort(temp_vec));
    }

    display_results(insertion_results, "Сортировка вставками (LinkedList)");
    display_results(shaker_results, "Шейкерная сортировка");
    display_results(qsort_results, "Быстрая сортировка");
}

void task_b(size_t size) {
    std::vector<int> temp_vec;
    LinkedList<int> temp_list;

    temp_list = VectorMaker::make_sorted(size);
    display_results({insertion_sort(temp_list)}, "Сортировка вставками (LinkedList)");

    temp_vec = VectorMaker::make_sorted(size);
    display_results({shaker_sort(temp_vec)}, "Шейкерная сортировка");

    temp_vec = VectorMaker::make_sorted(size);
    display_results({quick_sort(temp_vec)}, "Быстрая сортировка");
}

void task_c(size_t size) {
    std::vector<int> temp_vec;
    LinkedList<int> temp_list;

    temp_list = VectorMaker::make_reverse_sorted(size);
    display_results({insertion_sort(temp_list)}, "Сортировка вставками (LinkedList)");

    temp_vec = VectorMaker::make_reverse_sorted(size);
    display_results({shaker_sort(temp_vec)}, "Шейкерная сортировка");

    temp_vec = VectorMaker::make_reverse_sorted(size);
    display_results({quick_sort(temp_vec)}, "Быстрая сортировка");
}



int main() {
    setup_io();
    std::cout << "Случайный неупорядоченный:\n";
    task_a(1000);
    std::cout << "-------------------------\n";
    std::cout << "Отсортированный:\n";
    task_b(1000);
    std::cout << "-------------------------\n";
    std::cout << "Обратно отсортированный:\n";
    task_c(1000);
    std::cout << "-------------------------\n";
}
