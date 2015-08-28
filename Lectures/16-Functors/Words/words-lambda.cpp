#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int GetInteger();

int main() {
  ifstream input("dictionary.txt");
  vector<string> words;
  
  string line;
  while (getline(input, line))
    words.push_back(line);
  
  cout << "Enter a word length: ";
  int length = GetInteger();
  
  // Here we define a lambda function, or closure, which will compare a words
  // size against the 'length' variable.  You can think of this as a shorthand
  // for the functor defined in words.cpp -- they accomplish the same thing but
  // C++11 makes things a lot shorter.
  auto SizeFn = [length](const string& word) {return word.size() == length;};
  size_t result = count_if(words.begin(), words.end(), SizeFn);
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
