#include<iostream>
#include<string>

std::string replace(std::string haystack, std::string needle, std::string replacement)
{
    int length = replacement.size();
    int position = haystack.find(replacement);
    while(position != std::string::npos)
    {
        haystack.replace(position, length, needle);
        position = haystack.find(replacement);
    }
    return haystack;
}

int main()
{
    std::string haystack;
    std::string replacement = "cycle";
    std::string needle = "circle";

    std::cout << "Enter String Please: ";
    std::getline(std::cin,haystack);

    haystack = replace(haystack, needle, replacement);
    std::cout << haystack;
}