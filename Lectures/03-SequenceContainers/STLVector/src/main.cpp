#include <iostream>
#include <vector>

using namespace std;

void PrintVector(vector<int>& myVector) {
  // To iterate through each element of the vector, we use a for loop. The
  // iterating variable is of type size_t since myVector.size() also returns an
  // integer of type size_t. size_t is an integer type that is unsigned -- that
  // is, it cannot be negative, and its smallest possible value is 0.
  for (size_t i = 0; i < myVector.size(); ++i)
    cout << myVector[i] << ' ';
  cout << endl;
}

int main() {
  // We can initialize myVector to be a certain size by declaring it with the
  // size specified as a parameter. If we specify two arguments, the second
  // argument is what each element of the vector is initialized as. If we leave
  // that second argument out, then each element is initialized to a reasonable
  // default value -- in the case of numbers, 0 is used.
  vector<int> myVector(10);
  cout << "size: " << myVector.size() << endl;

  // We can both read and write elements of the vector using square bracket
  // notation.
  for (size_t i = 0; i < myVector.size(); ++i)
    myVector[i] = i;

  PrintVector(myVector);

  // .push_back(...) adds the specified value to the end of the vector.
  myVector.push_back(777);
  PrintVector(myVector);

  // .pop_back() removes the last element in the vector. It is similar to the
  // stack and the queue's .pop() functions in that it has no return value.
  myVector.pop_back();
  PrintVector(myVector);

  // We can also initialize a vector to have an initial value for all elements
  vector<int> otherVector(10, 3);
  PrintVector(otherVector);

  return 0;
}
