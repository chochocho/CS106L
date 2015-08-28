#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int GetInteger();

// The WordLengthFn class defines objects that, when operator() is invoked, take
// in a string and return true if and only if that string's length matches the
// length stored in the object.
// 
// Basic usage involves creating an object of type WordLengthFn and using it as
// if it were the name of a function instead:
// 
//   WordLengthFn countFn(10);
//   if (countFn("Hello")) {
//     cout << "'Hello' is ten letters long." << endl;
//   } else {
//     cout << "'Hello' is NOT ten letters long." << endl;
//   }
class WordLengthFn {
public:
  // We need to add a constructor for the WordLengthFn class in order to set the
  // internal length value that strings are compared against.
  explicit WordLengthFn(int len) {
    length = len;
  }
  
  // Since we want to use it in the count_if algorithm, we'll have our
  // operator() match what count_if expects. Technically, calling operator()
  // doesn't change the WordLengthFn object itself, so we declare it as const.
  //
  // The reason we had to use a functor for this example is because we need
  // access to the length variable that the user entered earlier from within
  // this function. However, we can't pass it in as a second parameter since the
  // count_if algorithm is what's making the function calls, and it only applies
  // the function with one string as its argument.
  //
  // Alternatively, we could store length as a global variable. But we don't
  // take kindly to those sorts of thoughts around here.
  //
  // Since functors are objects, we solve the problem by making length an
  // instance variable of the WordLengthFn class. Then, we can simply specify
  // the length we want to use when creating the functor object, which stores it
  // until it is needed. This is stylisticallty perferable to using a global
  // variable since we restrict the scope of wordLength to just where it's
  // required.
  bool operator()(const string& word) const {
    return word.size() == length;
  }

private:
  int length;
};

int main() {
  ifstream input("dictionary.txt");
  vector<string> words;
  
  string line;
  while (getline(input, line))
    words.push_back(line);
  
  cout << "Enter a word length: ";
  int length = GetInteger();
  
  // In the line below, we are creating the WordLengthFn on the fly by
  // invoking its constructor that takes in an integer and passing it into
  // count_if directly, without storing it as a variable. Note: we are NOT
  // invoking the WordLengthFn class's operator() -- that will only be called
  // when we use () on a WordLengthFn OBJECT that has already been created.
  //
  // Equivalently, we could have written:
  //
  //   WordLengthFn countFn(length);
  //   size_t result = count_if(words.begin(), words.end(), countFn);
  size_t result = count_if(words.begin(), words.end(), WordLengthFn(length));
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
