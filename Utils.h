// Utils.h

#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cstdlib>

using namespace std;

// Clear the console screen (cross-platform)
inline void clearScreen() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux/macOS
#endif
}

// Pause execution until the user presses Enter
inline void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Print a formatted separator line
inline void printLine(char ch = '-', int width = 40) {
    cout << string(width, ch) << "\n";
}

// Format double values to a currency string (e.g., 2 decimal places)
inline string fmt(double v) {
    ostringstream ss;
    ss << fixed << setprecision(2) << v;
    return ss.str();

}

// Safely read an integer from user input
inline int readInt(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        cin >> val;
        if (cin.good()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.\n";
    }
}

// Safely read a positive double (e.g., for monetary amounts)
inline double readPositiveDouble(const string& prompt) {
    double val;
    while (true) {
        cout << prompt;
        cin >> val;
        if (cin.good() && val > 0.0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid amount.\n";
    }
}