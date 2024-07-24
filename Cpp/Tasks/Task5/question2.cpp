#include <iostream>

class Solution {
public:
    int addDigits(int num) {
        int result;
        while(num >= 10)
        {
            result = 0;
            while(num != 0)
            {
                result += num% 10;
                num /= 10;
            }
            num = result;
        }
        return num;
    }
};

int main()
{
    Solution solution;
    int result = solution.addDigits(38);
    std::cout << result <<std::endl;
}