#include <iostream>

enum class Datatype
{
    INT,
    DOUBLE,
    CHAR
};

struct Data
{
    void* value;
    Datatype type;
};

class vPointerArray
{
    private:
        Data* arr;
        int size;

    public:
        vPointerArray(int s)
        {
            size = s;
            arr = new Data[size];
        }
        ~vPointerArray()
        {
            delete[] arr;
        }
        void setValue(void* value, int index, Datatype type)
        {
            arr[index].value = value;
            arr[index].type = type;
        }
        void* getValue(int index)
        {
            return arr[index].value;
        }
        int getSize()
        {
            return size;
        }
        Datatype getType(int index)
        {
            return arr[index].type;
        }
        void print()
        {
            for(int i=0; i<size; i++)
            {
                //std::cout << arr[i].value  << ":" << arr[i].type << std::endl;
                switch (arr[i].type)
                {
                case Datatype::INT:
                    std::cout << "Value " << *static_cast<int*>(arr[i].value) << " at index " << i  << " is int" << std::endl;
                    break;
                case Datatype::DOUBLE:
                    std::cout << "Value " << *static_cast<double*>(arr[i].value) << " at index " << i << " is double"  << std::endl;
                    break;
                case Datatype::CHAR:
                    std::cout << "Value " << *static_cast<char*>(arr[i].value) << " at index " << i << " is char"  << std::endl;
                    break;
                default:
                    break;
                }
            }
        }
};

int main()
{
    vPointerArray arr(3);
    int num1 = 5;
    double num2 =3.14;
    arr.setValue(&num1, 0, Datatype::INT);
    arr.setValue(&num2, 1, Datatype::DOUBLE);
    arr.print();
}