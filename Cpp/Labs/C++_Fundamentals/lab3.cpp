#include <iostream>
using namespace std;

typedef int* (*callbackFunc)(int** array, int size, int* row_sizes, int (*CallbackFunction)(int*, int));

int* addArray(int** array, int size, int* row_sizes, int (*func)(int*, int)) {
    int* result = new int[size];
    for (int i = 0; i < size; ++i) {
        result[i] = func(array[i], row_sizes[i]);
    }
    return result;
}

int add(int* row, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += row[i];
    }
    return sum;
}

int main() {
    int size = 3;
    int row_sizes[] = {6, 3, 5};

    int** array = new int*[size];
    array[0] = new int[6]{5, 2, 6, 4, 3, 9};
    array[1] = new int[3]{7, 1, 6};
    array[2] = new int[5]{1, 6, 11, 3, 4};

    callbackFunc callbackFunction = addArray;

    int* results = callbackFunction(array, size, row_sizes, add);

    for (int i = 0; i < size; ++i) {
        cout << "sum of row " << i << ": " << results[i] << endl;
    }

    delete[] results;
    for (int i = 0; i < size; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}

