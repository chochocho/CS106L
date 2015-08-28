#include <iostream>
#include <string>
#include <map>

using namespace std;

// GetLine asks the user to type in a response at the command line. It returns
// the user input as a string.
string GetLine() {
    string response;
    getline(cin, response);
    return response;
}

int main() {
    // We will use a map to count the appearances of words, as well as how many
    // times we encounter them.
    map<string, int> frequencyMap;

    cout << "Enter words." << endl;
    while (true) {
        cout << "> ";
        string response = GetLine();
        if (response.empty()) break;

        // This single line is doing a ton of work. The square bracket notation for
        // accessing values in maps will return a reference to the value associated
        // with the specified key. We can then modify it with ++ directly.
        //
        // However, if response is not already a key in the map, the square brackets
        // do a bit of extra work first. They automatically insert a new key-value
        // pair into the map, where the key is response and the value is a
        // reasonable default value -- in the case of integers, 0.
        frequencyMap[response]++;
    }

    cout << "Enter words to look up." << endl;
    while (true) {
        cout << "> ";
        string response = GetLine();
        if (response.empty()) break;

        // We use count just like with the STL set to determine if an entry is in
        // the map.
        if (frequencyMap.count(response)) {
            cout << frequencyMap[response] << " entries found." << endl;
        } else {
            cout << "None." << endl;
        }
    }

    return 0;
}
