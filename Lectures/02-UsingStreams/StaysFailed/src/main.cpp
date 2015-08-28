#include <iostream>
using namespace std;

int getInteger() {
  cout << "Please enter an integer value" << endl;
  int value;
  while (true) {
    cin >> value;
    if (!cin.fail()) break;

    cout << "Please re-enter an integer value: " << endl;
    // This solves the problem of unread data sitting on the stream.
    // Right?
    string s;
    getline(cin, s);
  }
  return value;

}

int main() {
  cout << "The user entered the number: " << getInteger() << endl;
}
