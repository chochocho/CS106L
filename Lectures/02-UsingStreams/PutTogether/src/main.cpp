#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// We define a small helper function to simplify the process of reading a line
string getLine() {
  string line;
  getline(cin, line);
  return line;
}

int main() {
  while (true) {
    // By reading an entire line at once we avoid problems with extra data on the stream.
    cout << "How many cookies do you have? ";
    string line = getLine();
    stringstream converter;
    converter << line;

    // We can read data from our stringstream just like any other stream
    int numCookies;
    converter >> numCookies;

    // If we couldn't read an int, then the user entered bad data
    if (converter.fail()) {
      // We clear our error state and read what the user DID enter as a string
      converter.clear();
      string badInput;
      converter >> badInput;
      cout << "Not an integer: " << badInput << endl;
    } else {
      // Even if we were successfully able to read in one integer, we still need
      // to make sure that there isn't any remaining input. We do this by trying
      // to read in another character.
      char junk;
      converter >> junk;

      // If we read more input, then there was garbage data at the end of our
      // string
      if (!converter.fail()) {
        cout << "Extra character found: " << junk << endl;
      } else {
        cout << "Well, I have " << (2 * numCookies) << " cookies." << endl;
      }
    }
  }

  return 0;
}
