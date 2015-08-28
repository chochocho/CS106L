#include <iostream>
#include <string>
using namespace std;

string mostImportantOrders = "DO NOT LAUNCH THE MISSLES!";
void appendFour(int s) {
    cout << s + "4" << endl;
}

int main() {
    cout << "The total number of missiles is:" << endl;
    appendFour(44);
    cout << endl;
    return 0;
}

