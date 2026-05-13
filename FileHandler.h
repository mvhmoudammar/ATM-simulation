// FileHandler.h

#pragma once

#include "Account.h"
#include <string>
#include <vector>

using namespace std;

class FileHandler {
public:
    static const string INDEX_FILE;
    static string accountFilePath(const string& accNum);
    static vector<string> loadIndex();
    static void addToIndex(const string& accNum);
    static bool accountExists(const string& accNum);
    static bool saveAccount(const Account& acc);
    static bool loadAccount(const string& accNum, Account& out_acc);
};