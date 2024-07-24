#include<iostream>
#include<string>
#include <algorithm>

class Solution {
public:
    std::string addStrings(std::string num1, std::string num2) {
        int sum = 0;
        int i = num1.size()-1;
        int j = num2.size()-1;
        std::string result = "";

        while (i >= 0 || j >= 0 || sum)
        {
            if(i >= 0)
            {
                sum += (num1[i] - '0');
                i--;
            }
            if(j >= 0)
            {
                sum += (num2[j] - '0');
                j--;
            }
            result += (sum % 10) + '0';
            sum /= 10;
        }
        
        std::reverse(result.begin(), result.end());

        return result;
    }
};

int main()
{
    Solution s;
    std::string result = s.addStrings("11", "123");
    std::cout << result << std::endl;
}