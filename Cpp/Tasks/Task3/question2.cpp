#include <iostream>
#include <cstdlib>
#include <ctime>

class Vertex
{
    private:
        int x;
        int y;

    public:
        Vertex()
        {
            srand(static_cast<unsigned int>(time(0)));
        }
        int getX()
        {
            return x;
        }
        int getY()
        {
            return y;
        }
        void setXY()
        {
            x = rand() % 201 - 100;
            y = rand() % 201 - 100;
        }
        std::string display()
        {
            return std::to_string(x) + ", " + std::to_string(y);
        }
};

int main()
{
    Vertex vertices[5];

    for (int i = 0; i < 5; i++)
    {
        vertices[i].setXY();
    }

    for (int i = 0; i < 5; i++)
    {
        std::cout << vertices[i].display() << std::endl;
    }
    
}