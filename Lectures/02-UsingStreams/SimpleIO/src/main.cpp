#include <string>
#include <iostream>
#include <sstream>
using namespace std;

/*
 * Implementation notes: getInteger, getReal
 * -----------------------------------------
 * Each of these functions reads a complete input line and then uses the
 * <sstream> library to parse that line into a value of the desired type.
 * If that fails, the implementation asks the user for a new value.
 */

int getInteger(string prompt) {
    int value;
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        istringstream stream(line);
        stream >> value >> ws;
        if (!stream.fail() && stream.eof()) break;
        cout << "Illegal integer format. Try again." << endl;
        if (prompt == "") prompt = "Enter an integer: ";
    }
    return value;
}

double getReal(string prompt) {
    double value;
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        istringstream stream(line);
        stream >> value >> ws;
        if (!stream.fail() && stream.eof()) break;
        cout << "Illegal numeric format. Try again." << endl;
        if (prompt == "") prompt = "Enter a number: ";
    }
    return value;
}

/*
 * Implementation notes: getLine
 * -----------------------------
 * The getLine function simply combines the process of displaying a
 * prompt and reading an input line into a single call.  The primary
 * reason for including this function in the library is to ensure
 * that the process of reading integers, floating-point numbers, and
 * strings remains as consistent as possible.
 */

string getLine(string prompt) {
    string line;
    cout << prompt;
    getline(cin, line);
    return line;
}

// Make the compiler happy
int main() {
    return 0;
}
