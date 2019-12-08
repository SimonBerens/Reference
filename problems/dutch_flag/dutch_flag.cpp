#include <iostream>
#include <vector>

using namespace std;

void dutch_flag_partition_linear(vector<int> &A, uint pivot_index) {
    int pivot = A[pivot_index];
    uint next_less = 0, next_equal = 0;
    for (int i = 0; i < (int) A.size(); ++i) {
        if (A[i] < pivot) {
            swap(A[i], A[next_equal]);
            swap(A[next_equal], A[next_less]);
            ++next_equal;
            ++next_less;
        } else if (A[i] == pivot) {
            swap(A[i], A[next_equal]);
            ++next_equal;
        }
    }
}

void dutch_flag_partition_convergent(vector<int> &A, uint pivot_index) {
    int pivot = A[pivot_index];
    uint next_less = 0, next_equal = 0, next_greater = (int) A.size() - 1;
    while (next_equal <= next_greater) {
        if (A[next_equal] < pivot) {
            swap(A[next_equal], A[next_less]);
            ++next_less;
            ++next_equal;
        } else if (A[next_equal] == pivot) {
            ++next_equal;
        } else {
            swap(A[next_equal], A[next_greater]);
            --next_greater;
        }
    }
}


int main() {}