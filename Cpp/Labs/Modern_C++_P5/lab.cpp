#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    if (!input)
    {
        std::cerr << "Unable to open input file" << std::endl;
        return 1;
    }

    if (!output)
    {
        std::cerr << "Unable to open output file" << std::endl;
        return 1;
    }

    std::vector<int> numbers;
    int number;

    while (input >> number)
    {
        if (number > 100000)
        {
            std::cerr << "Error: Number exceeds 100000" << std::endl;
            return 1;
        }
        numbers.push_back(number);
    }
    input.close();

    if (numbers.empty())
    {
        std::cerr << "No valid numbers in input file" << std::endl;
        return 1;
    }

    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    double avg = static_cast<double>(sum) / numbers.size();
    int min = *std::min_element(numbers.begin(), numbers.end());
    int max = *std::max_element(numbers.begin(), numbers.end());

    output << std::fixed << std::setprecision(2);
    output << std::setw(49) << std::setfill('-') << "" << std::endl;
    output << "|" << std::setw(7) << std::setfill(' ') << "Sum" << std::setw(5) << std::setfill(' ') << "|" << std::setw(7) << std::setfill(' ') << "Avg" << std::setw(5) << std::setfill(' ') << "|" << std::setw(7) << std::setfill(' ') << "Min" << std::setw(5) << std::setfill(' ') << "|" << std::setw(7) << std::setfill(' ') << "Max" << std::setw(5) << std::setfill(' ') << "|" << std::endl;
    output << std::setw(49) << std::setfill('-') << "" << std::endl;
    output << "|" << std::setw(7) << std::setfill(' ') << sum << std::setw(5) << std::setfill(' ') << "|" << std::setw(8) << std::setfill(' ') << avg << std::setw(4) << std::setfill(' ') << "|" << std::setw(6) << std::setfill(' ') << min << std::setw(6) << std::setfill(' ') << "|" << std::setw(7) << std::setfill(' ') << max << std::setw(5) << std::setfill(' ') << "|" << std::endl;
    output << std::setw(49) << std::setfill('-') << "" << std::endl;

    output.close();

    return 0;
}