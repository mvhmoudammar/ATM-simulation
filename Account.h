//Account.h
#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Abstract Base Class
class BankAccount {
protected:
    string accountNumber;
    double balance;

public:
    BankAccount(string accNum = "", double bal = 0.0);
    virtual ~BankAccount() {}
    virtual void printAccountType() const = 0;
    virtual bool withdraw(double amount) = 0;
    string getAccountNumber() const;
    double getBalance() const;
};

// Derived Class
class Account : public BankAccount {
    friend class FileHandler;
     friend class MainWindow;
private:
    string pin;
    int failedAttempts;
    bool isLocked;
    vector<string> transactions;

public:
    Account();
    Account(const string &accNum, const string &userPin, double initialBalance = 0.0);
    void printAccountType() const override;
    bool withdraw(double amount) override;
    bool getIsLocked() const;
    bool verifyPin(const string &attempt);
    void deposit(double amount);
    void receiveTransfer(double amount, const string &fromAcc);
    bool sendTransfer(double amount, const string &toAcc);
    void printTransactionHistory() const;
};