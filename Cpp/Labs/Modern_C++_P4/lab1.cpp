#include<iostream>
#include<string>
int main()
{
    std::string text = "The cycle of life is a cycle of cycles.";
    int position = text.find("cycle");
    while(position!=std::string::npos)
    {
        text.replace(position,5,"circle");
        position = text.find("cycle");
    }
    std::cout << text <<std::endl;

    text.insert(text.find("circle"),"great ");
    std::cout << text <<std::endl;

    position = text.find("circle");
    position = text.find("circle",position+5);
    text.insert(position,"never-ending ");
    std::cout << text <<std::endl;
}