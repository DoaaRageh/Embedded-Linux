#include <iostream>
#include <cstdlib>
#include <ctime>

struct Vertex
{
    int x;
    int y;
};

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    Vertex vertices[5];

    for (int i = 0; i < 5; i++)
    {
        vertices[i].x = rand() % 201 - 100;
        vertices[i].y = rand() % 201 - 100;
    }

    for (int i = 0; i < 5; i++)
    {
        std::cout << vertices[i].x << ", " << vertices[i].y << std::endl;
    }
}