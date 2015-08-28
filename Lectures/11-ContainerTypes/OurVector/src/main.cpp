// We include our own Vector header file here:
#include "vector.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    // Our input is a file containing the lines to a haiku (sort of).
    Vector lines;

    for (int i = 0; i < 10; ++i) {
        lines.push_back(string(i, '2'));
    }

    // Iterate through the Vector and print everything out:
    for (size_t i = 0; i < lines.size(); ++i)
        cout << lines.at(i) << endl;
    cout << endl;

    // Notice that we can use iterators just like an STL vector!
    for (Vector::iterator start = lines.begin(); start != lines.end(); ++start) {
        cout << *start << endl;
    }

    return 0;
}
