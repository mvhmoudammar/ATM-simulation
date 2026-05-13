// FileHandler.cpp

#include "FileHandler.h"
#include "Utils.h"
#include <fstream>
#include <algorithm>

// Index file storing all account numbers
const string FileHandler::INDEX_FILE = "All_Customers.txt";

// Generate file path for a specific account
string FileHandler::accountFilePath(const string& accNum) {
    return accNum + ".txt";
}

// Load all account numbers from the index file
vector<string> FileHandler::loadIndex() {
    vector<string> list;
    ifstream in(INDEX_FILE);
    if (!in.is_open()) return list;

    string line;
    while (getline(in, line)) {
        if (!line.empty()) list.push_back(line);
    }
    return list;
}

// Add a new account number to the index file
void FileHandler::addToIndex(const string& accNum) {
    auto existing = loadIndex();
    if (find(existing.begin(), existing.end(), accNum) != existing.end()) return;

    ofstream out(INDEX_FILE, ios::app);
    if (out.is_open()) out << accNum << "\n";
}

// Check if an account already exists
bool FileHandler::accountExists(const string& accNum) {
    auto list = loadIndex();
    return find(list.begin(), list.end(), accNum) != list.end();
}

// Save account data to a text file
bool FileHandler::saveAccount(const Account& acc) {
    // We use Getters for inherited protected attributes
    ofstream out(accountFilePath(acc.getAccountNumber()));
    if (!out.is_open()) return false;

    out << "ACCOUNT:" << acc.getAccountNumber() << "\n";
    out << "PIN:" << acc.pin << "\n"; // Allowed because FileHandler is a friend
    out << "BALANCE:" << fmt(acc.getBalance()) << "\n";
    out << "FAILED_ATTEMPTS:" << acc.failedAttempts << "\n";
    out << "LOCKED:" << (acc.isLocked ? 1 : 0) << "\n";
    
    out << "TRANSACTIONS_BEGIN\n";
    for (const auto& t : acc.transactions) {
        out << t << "\n";
    }
    out << "TRANSACTIONS_END\n";

    return true;
}

// Load account data from a text file
bool FileHandler::loadAccount(const string& accNum, Account& out_acc) {
    ifstream in(accountFilePath(accNum));
    if (!in.is_open()) return false;

    out_acc = Account();
    string line;
    bool inTransactions = false;

    while (getline(in, line)) {
        if (line == "TRANSACTIONS_BEGIN") {
            inTransactions = true;
            continue;
        }
        if (line == "TRANSACTIONS_END") {
            inTransactions = false;
            continue;
        }

        if (inTransactions) {
            if (!line.empty()) out_acc.transactions.push_back(line);
            continue;
        }

        auto colon = line.find(':');
        if (colon == string::npos) continue;

        string key = line.substr(0, colon);
        string value = line.substr(colon + 1);

        // Assigning values directly (allowed because FileHandler is a friend)
        if (key == "ACCOUNT") out_acc.accountNumber = value;
        else if (key == "PIN") out_acc.pin = value;
        else if (key == "BALANCE") out_acc.balance = stod(value);
        else if (key == "FAILED_ATTEMPTS") out_acc.failedAttempts = stoi(value);
        else if (key == "LOCKED") out_acc.isLocked = (value == "1");
    }

    return !out_acc.accountNumber.empty();
}
