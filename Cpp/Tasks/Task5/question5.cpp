#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int largestAltitude(std::vector<int>& gain) {
        std::vector<int> altitudes;
        altitudes.push_back(0);
        int i=0;
        for(int g : gain)
        {
            altitudes.push_back(altitudes[i]+g);
            i++;
        }
        return *std::max_element(altitudes.begin(), altitudes.end());
    }
};

int main()
{
    Solution s;
    std::vector<int> gain{-5, 1, 5, 0, -7};
    int result = s.largestAltitude(gain);
    std::cout << result << std::endl;
}