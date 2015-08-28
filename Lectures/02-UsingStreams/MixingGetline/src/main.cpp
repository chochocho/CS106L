#include <iostream>

using namespace std;

int main() {
    // Let's first try to read an integer with cin >>
    cout << "How many units are you taking?" << endl;
    int numberOfClasses;
    cin >> numberOfClasses;

    // Make sure everyone knows their best class
    cout << "Which class is your favorite?" << endl;
    string response;
    getline(cin, response);
    if (response == "cs106l") {
        cout << "Good choice!" << endl;
    } else {
        cout << "Really? You like " << response << "?" << endl;
    }
    return 0;
}

