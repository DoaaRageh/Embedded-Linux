#include<iostream>
#include<math.h>
#include<string.h>
#include <algorithm>
namespace MathFunctions
{
    void print(double number)
    {
        std::cout << "The square of number " << number << " is " << sqrt(number) << std::endl;
    }
}

namespace StringFunctions
{
    void print(char *word)
    {
        int size = strlen(word);
        char arr[size];
        if(word[0] > 'a' && word[0] < 'z')
        {
            std::cout << "Upper: ";
            for(int i=0; i<size; i++)
            {
                arr[i] = toupper(word[i]);
            }
        }
        else
        {
            std::cout << "Lower: ";
            for(int i=0; i<size; i++)
            {
                arr[i] = tolower(word[i]);
            }
        }
        for(int i=0; i<size; i++)
        {
            std::cout << arr[i];
        }
        std::cout << std::endl;
    }
}

namespace ArrayFunctions
{
    void print(int *numbers, int size)
    {
        std::reverse(numbers, numbers+size);
        std::cout << "Reversed Array: ";
        for(int i=0; i<size; i++)
        {
            std::cout << numbers[i] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    int arr[5] = {1,2,3,4,5} ;
    int size = sizeof(arr)/sizeof(arr[0]);
    char word[] = "doaa";
    MathFunctions::print(16);
    StringFunctions::print(word);
    ArrayFunctions::print(arr, size);
}
