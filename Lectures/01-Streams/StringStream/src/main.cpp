#include <iostream>
#include <string>
#include <sstream> // notice the dumb name
using namespace std;

int main() {

    int kevinsFavoriteNumber = 8675309;
    string kevinsFavoriteNumberString = "8675309";

    stringstream inputStringStream;
    int intRepresentation;
    inputStringStream << kevinsFavoriteNumberString;
    inputStringStream >> intRepresentation;
    cout << "Result when converting a string to an int:" << endl;
    cout << intRepresentation << endl;



    stringstream outputStringStream;
    outputStringStream << kevinsFavoriteNumber;
    string stringRepresentation = outputStringStream.str();
    cout << "Result when converting an int to a string:" << endl;
    cout << stringRepresentation << endl;

}
