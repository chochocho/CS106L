#include "Vector.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    // First, we'll read our poem into a Vector one line at a time.
    Vector<string> haiku;
    ifstream input("haiku.txt");

    string line;
    while (getline(input, line))
        haiku.push_back(line);

    // We want to iterate through the haiku and print out its contents. Before, we
    // would have used the .at(...) function. The STL supports the [] operator,
    // as shown below, so we'd like to be able to use that.
    for (size_t i = 0; i < haiku.size(); ++i)
        cout << haiku[i] << endl;

    // Now, we'll make a new Vector full of numbers:
    Vector<int> numbers;
    for (int i = 0; i < 10; ++i)
        numbers.push_back(i);

    // We would like to overload the << operator so that we can just print out the
    // Vector directly, as shown below:
    cout << numbers << endl;

    return 0;
}
