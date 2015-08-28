#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> numbers;
    for (int i = 0; i < 10; ++i)
        numbers.push_back(i);

    // We want to iterate through everything in the vector and print each element
    // out, but we don't want to use bulky iterator syntax. Range based for offers
    // a clean syntax for iterating through each element in a container. The first
    // argument is the type and name of the variable we assign to each individual
    // element. The second argument is the name of the container we're iterating
    // over.
    for (int number : numbers)
        cout << number << ' ';
    cout << endl;

    // Unlike the CS 106B version of foreach, Range based for allows us to iterate
    // over the elements of the numbers container by reference. We can take
    // advantage of that property to modify a sequence as we're iterating over it.
    for (int& number : numbers)
        number *= 10;

    // Here, we print each number out again. This time, each number has been
    // multiplied by a factor of 10.
    for (int number : numbers)
        cout << number << ' ';
    cout << endl;
    return 0;
}
