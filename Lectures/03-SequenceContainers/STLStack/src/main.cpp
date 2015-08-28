#include <iostream>
#include <stack>

using namespace std;

int main() {
  // Note that the STL stack is used with a lower-case 's', different from the
  // CS 106B version.
  stack<int> myStack;
  for (int i = 0; i < 10; ++i)
    myStack.push(i);

  // We can ask for various properties of the stack. To look at the top-most
  // stack element without removing it, we call .top() rather than .peek().
  cout << "size: " << myStack.size() << endl;
  cout << "top element: " << myStack.top() << endl;

  // The function to check if the stack is empty is simply .empty() rather than
  // .isEmpty().
  while (!myStack.empty()) {
    // We check the top element and pop it off in two separate steps. This is
    // because the STL stack's version of .pop() does not return a value when
    // it is called.
    cout << myStack.top() << ' ';
    myStack.pop();
  }

  cout << endl;

  return 0;
}

