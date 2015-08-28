#include <ctime>
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

// These constants dictate how many elements we insert, and how many times we
// run the test:
static const int kNumElems = 200000;
static const int kNumTests = 500;

void RunVectorTest() {
  clock_t start = clock();
  vector<int> myVector;

  for (int h = 0; h < kNumTests; h++) {
    // Add all elements to the back of the vector:
    for (int i = 0; i < kNumElems; i++) {
      myVector.push_back(i);
    }

    // Remove all elements from the back of the vector:
    for (int i = 0; i < kNumElems; i++) {
      myVector.pop_back();
    }
  }

  start = clock() - start;

  cout << "Vector test completed in ";
  cout << (static_cast<double>(start) / CLOCKS_PER_SEC);
  cout << " seconds." << endl;
}

void RunDequeTest() {
  clock_t start = clock();
  deque<int> myDeque;

  for (int h = 0; h < kNumTests; h++) {
    // Add all elements to the back of th deque:
    for (int i = 0; i < kNumElems; i++) {
      myDeque.push_back(i);
    }

    // Remove all elements from the back of the deque:
    for (int i = 0; i < kNumElems; i++) {
      myDeque.pop_back();
    }
  }

  start = clock() - start;

  cout << "Deque test completed in ";
  cout << (static_cast<double>(start) / CLOCKS_PER_SEC);
  cout << " seconds." << endl;
}
