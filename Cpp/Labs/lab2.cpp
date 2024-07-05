#include <iostream>
#include <cstdlib>

using namespace std;

struct vector {
    int *arr;
    int size;
    int capacity;
};

void initArray(vector *vec, int size) {
    vec->arr = (int *)malloc(size * sizeof(int));
    vec->size = size;
    vec->capacity = 0;
}

void freeArray(vector *vec) {
    free(vec->arr);
    vec->size = 0;
    vec->capacity = 0;
}

void printArray(vector *vec) {
    cout << "Array Elements: ";
    for (int i = 0; i < vec->capacity; i++) {
        cout << vec->arr[i] << " ";
    }
    cout << endl;
}

void printElement(vector *vec, int index) {
    if (index >= 0 && index < vec->capacity) {
        cout << "The " << index << " Element is : " << vec->arr[index] << endl;
    }
    else {
        cout << "Out Of Boundary" << endl;
    }
}

void insertElement(vector *vec, int value, int index) {
    if (vec->capacity >= vec->size) {
        vec->size *= 2;
        int *newArr = (int *)realloc(vec->arr, vec->size * sizeof(int));
        if (newArr == NULL) {
            cout << "Memory allocation failed" << endl;
            return;
        }
        vec->arr = newArr;
    }

    for (int i = vec->capacity; i > index; i--) {
        vec->arr[i] = vec->arr[i - 1];
    }

    vec->arr[index] = value;
    vec->capacity++;
}

void deleteElement(vector *vec, int index) {
    if (index < 0 || index >= vec->capacity) {
        cout << "Out of Boundary" << endl;
        return;
    }

    for (int i = index; i < vec->capacity - 1; i++) {
        vec->arr[i] = vec->arr[i + 1];
    }

    vec->capacity--;

    // Reduce size if necessary
    if (vec->capacity < vec->size / 2) {
        vec->size /= 2;
        int *newArr = (int *)realloc(vec->arr, vec->size * sizeof(int));
        if (newArr == NULL) {
            cout << "Memory allocation failed" << endl;
            return;
        }
        vec->arr = newArr;
    }
}

int main() {
    vector array;
    initArray(&array, 3);
    insertElement(&array, 5, 0);
    insertElement(&array, 7, 1);
    insertElement(&array, 11, 2);

    printArray(&array);

    insertElement(&array, 1, 2);
    printArray(&array);

    deleteElement(&array, 0);
    printArray(&array);

    freeArray(&array);

    return 0;
}
