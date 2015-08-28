#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int GetInteger();

bool isWordLengthFive(const string& word) {
  return word.size() == 5;
}

int main() {
  ifstream input("dictionary.txt");
  vector<string> words;
  
  string line;
  while (getline(input, line))
    words.push_back(line);
  
  //cout << "Enter a word length: ";
  //int length = GetInteger();
  int length = 5;
  
  size_t result = count_if(words.begin(), words.end(), isWordLengthFive);
  cout << "There are " << result << " words of length " << length << "." << endl;
  
  return 0;
}

int GetInteger() {
  string input;
  int value;
  
  while (true) {
    getline(cin, input);
    stringstream converter(input);
    converter >> value;
    if (converter.fail()) {
      cout << "Input invalid. Retry: ";
      continue;
    }
    
    char junk;
    converter >> junk;
    if (converter.fail())
      return value;
    
    cout << "Unexpected character found: '" << junk << "'. Retry: ";
  }
}
