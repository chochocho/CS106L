#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    // C++ will assume that x is an integer, since the constant 2 is considered
    // an int.  In general, C++ will look at the expression on the right hand
    // side of the equals to determine the type of the variable on the left
    // hand side when auto is used.
    auto x = 2;
    cout << "The value of x is: " << x << endl;

    // Since 2.4 is a double, y will be given type double.
    auto y = 2.4;
    cout << "The value of y is: " << y << endl;

    // We can use auto anywhere we would declare a variable, including inside
    // the loop variable.
    std::map<int, string> v;
    for (auto i = 0; i < 5; ++i)
        v[i] = "Hello!";

    // The syntax for using an iterator with a map can be extremely verbose,
    // since we need to write out the full type of the map and add ::iterator.
    for (std::map<int, string>::iterator i = v.begin(); i != v.end(); ++i)
        cout << i->first << endl;

    // We can simplify things a lot by using auto to infer the type of 'i'
    for (auto i = v.begin(); i != v.end(); ++i)
        cout << i->first << endl;

    return 0;
}
