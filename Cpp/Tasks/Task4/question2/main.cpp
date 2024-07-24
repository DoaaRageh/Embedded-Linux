#include "Account.hpp"
#include <iostream>

int main()
{
    Account A1(1700);
    Account A2(2000);

    A1.makeDeposit(500);
    A2.makeWithdrawal(400);

    std::cout << "Account 1 Status: " << std::endl;
    A1.displayStatus();

    std::cout << "Account 2 Status: " << std::endl;
    A2.displayStatus();

    std::cout << "Accounts Information: " << std::endl;
    A1.displayAccountsInfos();
}