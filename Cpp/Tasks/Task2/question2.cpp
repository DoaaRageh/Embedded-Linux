#include<iostream>
#include<cmath>
class Calculator
{
    private:
        double sum(double num1, double num2)
        {
            return num1 + num2;
        }
        double sub(double num1, double num2)
        {
            return num1 - num2;
        }
        double mul(double num1, double num2)
        {
            return num1 * num2;
        }
        double div(double num1, double num2)
        {
            if(num2 == 0)
            {
                std::cout << "Error: Division by zero" << std::endl;
                return 0;
            }
            return num1 / num2;;
        }
        double power(double num1, double num2)
        {
            return pow(num1, num2);
        }
        double square(double num)
        {
            if(num<0)
            {
                std::cout << "Error: Square root of a negative number" << std::endl;
                return 0;
            }
            return sqrt(num);;
        }

    public:
        void calculate()
        {
            double num1, num2, result;
            char op;
            std::cout << "Enter Number 1: ";
            std::cin >> num1;
            std::cout << "Enter The Operation: ";
            std::cin >> op;
            if(op != 'S')
            {
                std::cout << "Enter Number 2: ";
                std::cin >> num2;
            }
            switch(op)
            {
                case '+':
                    result = sum(num1, num2);
                    break;
                case '-':
                    result = sub(num1, num2);
                    break;
                case '*':
                    result = mul(num1, num2);
                    break;
                case '/':
                    result = div(num1, num2);
                    break;
                case '^':
                    result = power(num1, num2);
                    break;
                case 'S':
                    result = sqrt(num1);
                    break;
                default:
                    std::cout << "Invalid Option" << std::endl;
                    break;
            }
            std::cout << "The result is: " << result << std::endl;
        }
};

int main()
{
    Calculator calc;
    calc.calculate();
}