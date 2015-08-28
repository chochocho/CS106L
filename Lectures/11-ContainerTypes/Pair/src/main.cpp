#include <string>
#include <iostream>
using namespace std;

// Define our class template
// I used the name mypair, becuase pair is defined in the standard library!
template <typename L, typename R>
struct mypair {
    L first;
    R second;
};

// Define a function which will work only with a specific form of pair
void printIntStringPair(mypair<int, string>& p) {
    cout << "The first value is: " << p.first << endl;
    cout << "The second value is: " << p.second << endl;
}

// Define a function which will work with any form of the class template
template<typename PairType>
void printPair(PairType& p) {
    cout << "The first value is: " << p.first << endl;
    cout << "The second value is: " << p.second << endl;
}

// Define a quick program to test this
int main() {
    // Define a couple of differently typed pairs
    mypair<int, string> x = {8675309, "a pair of int and string"};
    mypair<string, char> y = {"a pair of a string and a character", 'y'};

    // Print out our first pair using the <int,string> specific function
    printIntStringPair(x);
    cout << endl;

    // Print out our second pair using a function which works for all pairs
    printPair(y);
}
