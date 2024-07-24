#include "Account.hpp"
#include <iostream>
#include <ctime>

int Account::m_noOfAccounts = 0;
int Account::m_totalAmount = 0;
int Account::m_totalNbDeposits = 0;
int Account::m_totalNbWithdrawals = 0;

int Account::getNoOfAccounts(void)
{
    return m_noOfAccounts;
}

int Account::getTotalAmount(void)
{
    return m_totalAmount;
}

int Account::getNbDeposits(void)
{
    return m_totalNbDeposits;
}

int Account::getNoOfWithdrawals(void)
{
    return m_totalNbWithdrawals;
}

void Account::displayAccountsInfos(void)
{
    m_displayTimestamp();
    std::cout << "Number of accounts: " << m_noOfAccounts << std::endl
              << "Total number of deposits: " << m_totalNbDeposits << std::endl
              << "Total number of withdrawals: " << m_totalNbWithdrawals << std::endl
              << "total amount of all accounts: " << m_totalAmount << std::endl;
}

Account::Account(int initial_deposit)
{
    m_amount = initial_deposit;
    m_noOfDeposits = 1;
    m_noOfWithdrawals = 0;
    m_noOfAccounts++;
    m_accountIndex = m_noOfAccounts;
    m_totalAmount += initial_deposit;
    m_totalNbDeposits++;
}

Account::~Account(void)
{
    m_noOfAccounts--;
}

void Account::makeDeposit(int deposit)
{
    m_amount += deposit;
    m_noOfDeposits++;
    m_totalAmount += deposit;
    m_totalNbDeposits++;
}

bool Account::makeWithdrawal(int withdrawal)
{
    if (withdrawal <= m_amount)
    {
        m_amount -= withdrawal;
        m_noOfWithdrawals++;
        m_totalAmount -= withdrawal;
        m_totalNbWithdrawals++;
        return true;
    }
    else
    {
        std::cout << "The amount in the account is not enough" << std::endl;
        return false;
    }
}

int Account::checkAmount(void) const
{
    return m_amount;
}
void Account::displayStatus(void) const
{
    std::cout << "Account Index: " << m_accountIndex << std::endl
              << "Amount: " << m_amount << std::endl
              << "Number of Deposits: " << m_noOfDeposits << std::endl
              << "Number of Withdrawals: " << m_noOfWithdrawals << std::endl;
}

void Account::m_displayTimestamp(void)
{
    std::time_t now = std::time(nullptr);
    std::tm* now_tm = std::localtime(&now);

    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", now_tm);
    
    std::cout << "Timestamp: " << buffer << std::endl;
}

Account::Account(void)
{
    m_amount = 0;
    m_noOfDeposits = 0;
    m_noOfWithdrawals = 0;
    m_noOfAccounts++;
    m_accountIndex = m_noOfAccounts;
}
