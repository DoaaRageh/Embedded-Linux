#include<iostream>
#include<string>
#include<cmath>
using namespace std;

string decimal_to_binary(int number)
{
    string binary = "";
    if(number == 0)
    {
        binary = "0";
    }
    else
    {
        while (number > 0)
        {
            if(number % 2 == 0)
            {
                binary = "0" + binary;
            }
            else
            {
                binary = "1" + binary;
            }
            number/=2;
        } 
    }
    return binary;
}

int binary_to_decimal(string binary)
{
    int number=0;
    int length = binary.length();
    for(int i=0; i<length; i++)
    {
        if(binary[length-1-i] == '1')
        {
            number+=pow(2,i);
        }
    }
    return number;
}

int main()
{
    int number;
    string binary = decimal_to_binary(7);
    cout << "Binary of 7 is: ";
    cout << binary << endl;
    number = binary_to_decimal("1101");
    cout << "Decimal of 1101 is: ";
    cout << number;
}

