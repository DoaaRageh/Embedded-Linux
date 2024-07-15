#include <iostream>
#include <vector>

void transpose(std::vector<std::vector<int>> &matrix)
{
    int rows = matrix[0].size();
    int i;

    std::vector<std::vector<int>> temp(rows);
    for (const auto &row : matrix)
    {
        i = 0;
        for (const auto &element : row)
        {
            temp[i].push_back(element);
            i++;
        }
    }
    matrix = temp;
}

void print(std::vector<std::vector<int>> matrix)
{

    for (const auto &row : matrix)
    {
        for (const auto &element : row)
        {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::vector<std::vector<int>> matrix;
    matrix.push_back({1, 2, 3});
    matrix.push_back({4, 5, 6});
    matrix.push_back({7, 8, 9});
    print(matrix);
    std::cout << std::endl;
    transpose(matrix);
    print(matrix);
}