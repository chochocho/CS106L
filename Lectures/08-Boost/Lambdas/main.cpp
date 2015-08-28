#include <vector>
#include <algorithm>
#include <typeinfo>
#include <iostream>
#include <iterator>
#include <iomanip>

using namespace std;

// PrintRightAlignedVector prints the numbers in the specified vector, except
// flushed right. This is useful later on when we sort the vector by the last
// digit.
void PrintRightAlignedVector(vector<int>& numbers) {
    for (size_t i = 0; i < numbers.size(); ++i)
        cout << setw(10) << numbers[i] << endl;
}

// PrintVector simply prints each number in the specified vector, one on a line.
void PrintVector(vector<int>& numbers) {
    for (size_t i = 0; i < numbers.size(); ++i)
        cout << numbers[i] << endl;
}

// When ReverseCompare is used as a comparison function for sort, it will leave
// the resulting range sorted in descending order. Note that there is a
// significant amount of "setup" code, while the interesting bit is extremely
// short: rhs < lhs.
bool ReverseCompare(int lhs, int rhs) {
    return rhs < lhs;
}

int main() {
    // Seed the random number generator and fill the vector with random integers:
    srand(time(NULL));
    vector<int> numbers(30);
    generate(numbers.begin(), numbers.end(), rand);

    // Sort the numbers in ascending order:
    sort(numbers.begin(), numbers.end());

    // Sort the numbers in descending order without lambda functions:
    sort(numbers.begin(), numbers.end(), ReverseCompare);

    // Sort the numbers in descending order using a lambda function. The idea is
    // that we want to use this function once, and the body of the function is
    // extremely simple. It seems like overkill to declare a function like
    // ReverseCompare just to pass it in here. Instead, we can create a function
    // on the fly and forego giving it a name by passing in a lambda function.
    sort(numbers.begin(), numbers.end(), [](int l, int r){return r < l;});

    // Sort the numbers in ascending order of their one's digits:
    sort(numbers.begin(), numbers.end(), [](int l, int r){return l % 10 < r %10;});

    //PrintRightAlignedVector(numbers);

    // If you want to use a lambda as a variable, auto is your friend
    // Don't try to figure out the type here
    auto smallerThanFirst = [&numbers](int v){return v < numbers[0];};
  
    // Shuffle the numbers
    random_shuffle(numbers.begin(), numbers.end());
    cout << "First number is: " << numbers[0] << endl;
    vector<int> small;  

    // Copy all the numbers that are smaller than the first one
    copy_if(numbers.begin(), numbers.end(), back_inserter(small), smallerThanFirst);
    PrintRightAlignedVector(small);

    return 0;
}
