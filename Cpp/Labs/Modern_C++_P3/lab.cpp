#include <iostream>
class Vector
{
private:
    int *arr;
    int capacity;
    int currentSize;

public:
    void resize()
    {
        capacity *= 2;
        int *array = new int[capacity];
        for (int i = 0; i < currentSize; i++)
        {
            array[i] = arr[i];
        }
        delete[] arr;
        arr = array;
    }
    void pushback(int value)
    {
        if (currentSize == capacity)
        {
            resize();
        }
        arr[currentSize] = value;
        currentSize++;
    }
    void popback()
    {
        if (currentSize != 0)
        {
            currentSize--;
            arr[currentSize] = 0;
        }
        else
        {
            std::cout << "The array is empty" << std::endl;
        }
    }
    void removeAt(int index)
    {
        if (currentSize != 0)
        {
            for (int i = index; i < currentSize - 1; i++)
            {
                arr[i] = arr[i + 1];
            }
            currentSize--;
        }
        else
        {
            std::cout << "The array is empty" << std::endl;
        }
    }
    void insertAt(int index, int value)
    {
        if (currentSize == capacity)
        {
            resize();
        }
        for (int i = currentSize; i > index; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[index] = value;
        currentSize++;
    }
    void insertMiddle(int value)
    {
        if (currentSize == capacity)
        {
            resize();
        }
        insertAt(currentSize / 2, value);
    }
    void removeMiddle()
    {
        removeAt(currentSize / 2);
    }
    int size()
    {
        return currentSize;
    }
    void print()
    {
        for (int i = 0; i < currentSize; i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
    Vector()
    {
        arr = new int[1];
        currentSize = 0;
        capacity = 1;
    }
    Vector(int size)
    {
        arr = new int[size];
        currentSize = 0;
        capacity = size;
    }
    Vector(int size, int value)
    {
        arr = new int[size];
        currentSize = size;
        capacity = size;
        for (int i = 0; i < size; i++)
        {
            arr[i] = value;
        }
    }
    Vector(int size, int *values)
    {
        arr = new int[size];
        currentSize = size;
        capacity = size;
        for (int i = 0; i < size; i++)
        {
            arr[i] = values[i];
        }
    }
    Vector(std::initializer_list<int> values)
    {
        capacity = values.size();
        currentSize = values.size();
        arr = new int[capacity];
        int i = 0;
        for (auto value : values)
        {
            arr[i] = value;
            i++;
        }
    }
    Vector(const Vector &array)
    {
        currentSize = array.currentSize;
        capacity = array.capacity;
        arr = new int[capacity];
        for (int i = 0; i < currentSize; i++)
        {
            arr[i] = array.arr[i];
        }
    }
    ~Vector()
    {
        delete[] arr;
    }
};

int main()
{
    int values[] = {1, 2, 3, 4, 5};
    Vector arr1(5, values);
    arr1.print();

    Vector arr2({6, 7, 8, 9, 10});
    arr2.print();

    Vector arr3(arr2);
    arr3.print();

    arr1.insertAt(1, 9);
    arr1.print();

    arr1.removeAt(2);
    arr1.print();

    arr1.insertMiddle(8);
    arr1.print();

    arr1.removeMiddle();
    arr1.print();

    arr1.popback();
    arr1.print();

    std::cout << "Size: " << arr1.size() << std::endl;
}