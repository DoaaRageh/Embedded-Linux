#include<iostream>
#include<string>

class ParkingSystem {
private:
    int Big;
    int Medium;
    int Small;
public:
    ParkingSystem(int big, int medium, int small) {
        Big = big;
        Medium = medium;
        Small = small;
    }
    
    bool addCar(int carType) {
        bool result;
        switch(carType)
        {
            case 1:
                if(Big > 0)
                {
                    result = true;
                    Big--;
                }
                else
                {
                    result = false;
                }
                break;
            case 2:
                if(Medium > 0)
                {
                    result = true;
                    Medium--;
                }
                else
                {
                    result = false;
                }
                break;
            case 3:
                if(Small > 0)
                {
                    result = true;
                    Small--;
                }
                else
                {
                    result = false;
                }
                break;
            default:
                break;
        }
        return result;
    }
};
