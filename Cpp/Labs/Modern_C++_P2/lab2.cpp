#include<iostream>
template<typename T>
class Pair
{
    private:
        T first;
        T second;

    public:
        T getFirst()
        {
            return first;
        }
        void setFirst(T f)
        {
            first = f;
        }
        T getSecond()
        {
            return second;
        }
        void setSecond(T s)
        {
            second = s;
        }
        void setPair(T f, T s)
        {
            first = f;
            second = s;
        }
        void swap()
        {
            T temp = first;
            first = second;
            second = temp;
        }
        void print()
        {
            std::cout << first << ":" << second <<std::endl;
        }

        Pair()
        {
            first = 0;
            second = 0;
        }

        Pair(T f, T s)
        {
            first = f;
            second = s;
        }
};

int main()
{
    Pair<int> pair1(6, 1);
    pair1.print();
    Pair<std::string> pair2("1","doaa");
    pair2.print();
}