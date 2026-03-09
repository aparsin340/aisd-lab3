#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "LinkedList.h"
#include <iostream>

struct stats { 
    size_t comparison_count = 0; 
    size_t copy_count = 0; 
};

std::ostream& operator<<(std::ostream& os, stats stat) {
    os << "(Сравнения: " << stat.comparison_count << ", Копирования: " << stat.copy_count << ")";
    return os;
}

template<typename T>
stats insertion_sort(LinkedList<T>& list) {
    stats stats;
    if (list.size() < 2) return stats;

    auto main = list.head_->next;
    auto key = list.head_;

    while (main) {
        key = main;
        main = main->next;
        auto it = list.head_;

        while(key->value > it->value && it != key) { it = it->next; stats.comparison_count++;}
        stats.comparison_count++;

        if (it != key) { // Перевязывание элементов списка
            auto it_prev = it->prev;
            if (it->prev) { it->prev->next = key;}
            if (it == list.head_) { list.head_ = key;}
            it->prev = key; // [it_prev]->|key|<-[it]

            key->prev->next = key->next;
            if (key->next) { key->next->prev = key->prev;} // [key->prev]<->[key->next]
            if (key == list.tail_) { list.tail_ = key->prev;}
            
            key->next = it; 
            key->prev = it_prev; // [it_prev]<->[key]<->[it]

            stats.copy_count += 3;
        }
    }

    return stats; 
}

template<typename T>
stats shaker_sort(std::vector<T>& vec) { 
    stats stats;
    if (vec.size() < 2) return stats;

    size_t L = 0; size_t R = vec.size() - 1;
    size_t ops = 0;
    for (size_t i = 0; i < vec.size() / 2; i++) {
        ops = 0;
        for (size_t l = L; l < R; l++) {
            if (vec[l] > vec[l+1]) {
                ops++;
                std::swap(vec[l], vec[l+1]);
                stats.copy_count += 3;
            }
            stats.comparison_count++;
        }
        R--;
        for (size_t r = R; r > L; r--) {
            if (vec[r] < vec[r - 1]) {
                ops++;
                std::swap(vec[r], vec[r - 1]);
                stats.copy_count += 3;
            }
            stats.comparison_count++;
        }
        L++;
        if (ops == 0) break;
    }
    return stats; 
}

template<typename T>
stats quick_sort(std::vector<T>& vec) {
    if (vec.size() < 2) return stats();
    
    struct qsort {
        static void qsort_step(std::vector<T>& vec, size_t l, size_t r, stats& stats) {
            if (l >= r) return;
            T pivot = vec[(l + r) / 2]; stats.copy_count++;
            size_t i = l;
            size_t j = r;
            while (i < j) {
                while (vec[i] < pivot) {i++; stats.comparison_count++;}
                while (vec[j] > pivot) {j--; stats.comparison_count++;}
                stats.comparison_count += 2;
                if (i >= j) break;
                std::swap(vec[i++], vec[j--]);
                stats.comparison_count += 3;
            }
            qsort_step(vec, l, j, stats);
            qsort_step(vec, j + 1, r, stats);
        }
    };

    stats stats;
    qsort::qsort_step(vec, 0, vec.size() - 1, stats);

    return stats;
}

#endif /* FUNCTIONS_H */
