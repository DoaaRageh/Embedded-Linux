#include<iostream>
using namespace std;

int main()
{
    int num, result=0;
    cout << "Please Enter Number: ";
    cin >> num;
    while(num!=0)
    {
        result+=num;
        cout << "Please Enter New Number: ";
        cin >> num;
    }
    cout << "result = " << result << endl;
}