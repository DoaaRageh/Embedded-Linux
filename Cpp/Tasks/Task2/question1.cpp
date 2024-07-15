#include<iostream>
#include<string>
class Car
{
    private:
        std::string company;
        std::string model;
        int year;
    
    public:
        void setCompany(std::string c)
        {
            company = c;
        } 
        std::string getCompany()
        {
            return company;
        }
        void setModel(std::string m)
        {
            model = m;
        } 
        std::string getModel()
        {
            return model;
        }
        void setYear(int y)
        {
            year = y;
        } 
        int getYear()
        {
            return year;
        }
};

int main()
{
    Car car;
    car.setCompany("Toyota");
    car.setModel("Camry");
    car.setYear(2005);
    std::cout << "Company: "<< car.getCompany() << std::endl;
    std::cout << "Model: "<< car.getModel() << std::endl;
    std::cout << "Year: "<< car.getYear() << std::endl;
}