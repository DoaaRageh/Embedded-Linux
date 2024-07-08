#include<iostream>

namespace DynamicAlloc
{
    int** create2DArray(int rows, int cols)
    {
        int **arr = new int*[rows];
        for(int i=0; i<rows; i++)
        {
            arr[i] = new int[cols];
        }
        return arr;
    }
    void delete2DArray(int **arr,int rows)
    {
        for(int i=0; i<rows; i++)
        {
            delete[] arr[i];
        }
        delete[] arr;
    }
}

int main()
{
    int rows=3, cols=2;
    int **arr = DynamicAlloc::create2DArray(3,2);
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            arr[i][j]=j;
        }
    }
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            std::cout<<arr[i][j];
        }
    }
    DynamicAlloc::delete2DArray(arr,rows);
}