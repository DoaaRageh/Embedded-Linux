#include<iostream>
using namespace std;

int main()
{
    int input_seconds, hours, minutes, seconds;
    cout << "Input Seconds: ";
    cin >> input_seconds;
    hours = input_seconds / 3600;
    minutes = (input_seconds / 60) % 60;
    seconds = input_seconds % 60;
    cout << "H:M:S - " << hours << ":" << minutes << ":" << seconds << endl;
}