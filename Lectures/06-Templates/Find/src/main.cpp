#include <deque>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

template<typename IteratorType, typename ElemType>
IteratorType MyFind(IteratorType first, IteratorType last, ElemType target) {
  // Search until we hit the end of the range:
  while (first!=last) {
    // If we find the target element, quit and return the iterator:
    if (*first == target) return first;
    // Otherwise, keep looking:
    ++first;
  }

  // If we reach this point, just return the last value
  return last;
}

int main() {
  // Put 1-100 in a vector (or a deque!) in random order 
  deque<int> myContainer;
  ifstream numbers("numbers.txt");
  int number;

  while (numbers >> number) {
    myContainer.push_back(number);
  }
  
  // Search for the number 70 in our container (should suceed)
  deque<int>::iterator happyItr = MyFind(myContainer.begin(), myContainer.end(), 70);
  // Search for the number 120 in our container (should fail)
  deque<int>::iterator sadItr = MyFind(myContainer.begin(), myContainer.end(), 120);

  if (happyItr != myContainer.end()) {
    cout << "Found 70" << endl;
  } else {
    cout << "Didn't find 70" << endl;
  }

  if (sadItr != myContainer.end()) {
    cout << "Found 120" << endl;
  } else {
    cout << "Didn't find 120" << endl;
  }

  return 0;
}
