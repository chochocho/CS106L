#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <functional>

using namespace std;

string GetLine() {
  string response;
  getline(cin, response);
  return response;
}

// ZombifyFn is a functor class which defines how to determine whether a person
// should be a zombie. This will be based on the length of user's own name. In
// other functor examples, we stored the desired name length as an instance
// variable to avoid the problem of not having access to it in a one-argument
// function. Here, we take a different approach: we make it a binary function
// (which is much more intuitive), and later, we'll use bind to pass in the same
// value for the second argument every time it's used. In order to use bind1st
// and bind2nd, we need our functor class to extend binary_function (the
// template arguments are based on our operator()'s argument and return types).
class ZombifyFn : public binary_function<string, string, string> {
public:
  string operator()(const string& input, const string& name) const {
    if (input.size() < name.size()) {
      return "ZOMBIE " + input;
    } else {
      return input;
    }
  }
};

int main() {
  ifstream input("names.txt");
  vector<string> names;
  
  string line;
  while (getline(input, line))
    names.push_back(line);
  
  cout << "What is your name? ";
  string name = GetLine();
  
  // The results of this transformation will be written directly to the console
  // using the ostream_iterator, an iterator adaptor where output goes to the
  // specified stream. Each element of the names vector is transformed using a
  // functor of type ZombifyFn. The reason we use bind2nd (in the <functional>
  // header) is because transform expects a single argument (the string to
  // transform), but functor expects two. We know that we want name to be passed
  // in as the second argument whenever the ZombifyFn functor is used by the
  // transform algorithm. bind2nd is our way of saying "treat ZombifyFn() as a
  // one-argument function where the second 'hidden' argument always has the
  // value 'name' whenever transform uses it."
  cout << "\nResidents of EARTH\n------------------" << endl;
  transform(names.begin(), names.end(),
            ostream_iterator<string>(cout, "\n"),
            bind2nd(ZombifyFn(), name));
  
  return 0;
}







