#include <string>
#include <iostream>

using namespace std;

// We can devise a regular function, Greet, which takes in a string parameter
// and prints it out.
void Greet(const string& greeting) {
  cout << greeting << " function!" << endl;
}

// Alternatively, if we create a class that overloads operator(), we call that a
// functor. We can then invoke operator() on objects of that class using
// function syntax.
class GreetFn {
public:
  // operator() can take any combination of parameters (any number, any type),
  // and can return any type or no type at all.
  void operator()(const string& greeting) const {
    cout << greeting << " functor!" << endl;
  }
};

int main() {
  // Before we use the GreetFn functor, we have to actually create an object of
  // type GreetFn. Then, we can use the object as if it were a function.
  GreetFn greet;
  greet("Hello");
  greet("Get out of my house");
  
  return 0;
}








