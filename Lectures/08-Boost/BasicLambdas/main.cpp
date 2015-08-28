#include <iostream>

using namespace std;

int main()
{
    // Declare a function which prints hello world
    auto helloWorldFn = [](){
        cout << "Hello world" << endl;
    };
    helloWorldFn();

    // Declare a function which takes a parameter
    auto printNumber = [](int param) {
        cout << "I  was given a parameter of: " << param << endl;
    };
    printNumber(2);

    // Declare a number which captures a parameter
    int x = 1;
    auto modifyViaCapture = [&x]() {
        x = 2;
    };

    cout << "Before running the function, x was: " << x << endl;
    modifyViaCapture();
    cout << "After running the function, x was: " << x << endl;

    return 0;
}

