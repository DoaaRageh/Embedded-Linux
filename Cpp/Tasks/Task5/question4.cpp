#include <iostream>
#include <string>
#include <algorithm>

class Solution {
public:
    bool isAnagram(std::string s, std::string t) {
        if(s.size() != t.size())
        {
            return false;
        }
        std::sort(s.begin(), s.end());
        std::sort(t.begin(), t.end());
        
        return s == t;
    }
};

int main()
{
    Solution s;
    bool result = s.isAnagram("anagram", "nagaram");
    std::cout << std::boolalpha << result << std::endl;
}