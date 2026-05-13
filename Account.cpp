// account.cpp
#include "Account.h"
#include "Utils.h"

BankAccount::BankAccount(string accNum, double bal) : accountNumber(accNum), balance(bal) {}
string BankAccount::getAccountNumber() const { return accountNumber; }
double BankAccount::getBalance() const { return balance; }

Account::Account() : BankAccount("", 0.0), failedAttempts(0), isLocked(false) {}
Account::Account(const string& accNum, const string& userPin, double initialBalance)
    : BankAccount(accNum, initialBalance), pin(userPin), failedAttempts(0), isLocked(false) {}

void Account::printAccountType() const { cout << "Standard Personal Account\n"; }
bool Account::getIsLocked() const { return isLocked; }

bool Account::verifyPin(const string & attempt) {
    if (isLocked) return false;
    if (attempt == pin) {
        failedAttempts = 0;
        return true;
    }
    ++failedAttempts;
    if (failedAttempts >= 3) isLocked = true;
    return false;
}

void Account::deposit(double amount) {
    balance += amount;
    transactions.push_back("Credit: +$" + fmt(amount) + " | New Balance: $" + fmt(balance));
}

bool Account::withdraw(double amount) {
    double fee = 2.00;
    if (amount + fee > balance) return false;
    balance -= (amount + fee);
    transactions.push_back("Debit: -$" + fmt(amount) + " (Fee: $2.00) | New Balance: $" + fmt(balance));
    return true;
}

void Account::receiveTransfer(double amount, const string& fromAcc) {
    balance += amount;
    transactions.push_back("TRF IN: +$" + fmt(amount) + " FROM " + fromAcc + " | Bal: $" + fmt(balance));
}

bool Account::sendTransfer(double amount, const string& toAcc) {
    double fee = 5.00;
    if (amount + fee > balance) return false;
    balance -= (amount + fee);
    transactions.push_back("TRF OUT: -$" + fmt(amount) + " TO " + toAcc + " | Bal: $" + fmt(balance));
    return true;
}

void Account::printTransactionHistory() const {
    if (transactions.empty()) {
        cout << "No recent activity found.\n";
        return;
    }
    cout << "Date/Time | Description | Amount | Balance\n";
    printLine('-', 60);
    for (size_t i = 0; i < transactions.size(); ++i) {
        cout << (i + 1) << ". " << transactions[i] << "\n";
    }
}