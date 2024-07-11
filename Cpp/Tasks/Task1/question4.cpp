#include<iostream>
using namespace std;

void calculateYears( double population, int year)
{
    if(population > 1000000)
    {
        std::cout << "It will take " << year << " Years" << endl;
    }
    else
    {
        std::cout << "Year " << year << ": " << population << endl;
        population *= 1.065;
        calculateYears(population, year+1);
    }
}

int main()
{
    double population = 162100;

    calculateYears(population, 0);
}
