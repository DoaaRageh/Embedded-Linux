#include<iostream>

namespace ArratPair
{
    std::pair<int, int>* createArray(int size)
    {
        std::pair<int, int> *arr = new std::pair<int, int>[size];
        return arr;
    }
    void deleteArray(std::pair<int, int>* arr)
    {
        delete[] arr;
    }
    void setPair(std::pair<int, int> *arr, std::pair<int, int> pair, int index)
    {
        arr[index] = pair;
    }
    std::pair<int, int> getPair(std::pair<int, int>* arr, int index)
    {
        return arr[index];        
    }
    void printArray(std::pair<int, int>* arr, int size)
    {
        for(int i=0; i<size; i++)
        {
            std::cout << arr[i].first << " : " << arr[i].second << std::endl;
        }
    }
}

int main()
{
    int size = 3;
    std::pair<int, int> pair;
    std::pair<int, int>* arr = ArratPair::createArray(size);
    ArratPair::setPair(arr,std::make_pair(1,3),0);
    ArratPair::setPair(arr,std::make_pair(4,1),1);
    ArratPair::setPair(arr,std::make_pair(2,5),2);
    ArratPair::printArray(arr, size);
    pair = ArratPair::getPair(arr, 1);
    std::cout << pair.first << " : " << pair.second << std::endl;
    ArratPair::deleteArray(arr);
}