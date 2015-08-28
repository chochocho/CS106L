#include <ctime>
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

// These constants dictate how many elements we insert, and how many times we
// run the test:
static const int kNumElems = 100000;
static const int kNumTests = 1000;

void RunVectorTest() {
  clock_t start = clock();
  vector<int> myContainer(kNumElems);

  for (int h = 0; h < kNumTests; h++) {
    // Assign to elements using indexing:
    for (int i = 0; i < kNumElems; i++) {
      myContainer[i] = i;
    }
  }

  start = clock() - start;

  cout << "Vector test completed in ";
  cout << (static_cast<double>(start) / CLOCKS_PER_SEC);
  cout << " seconds." << endl;
}

void RunDequeTest() {
  clock_t start = clock();
  deque<int> myContainer(kNumElems);

  for (int h = 0; h < kNumTests; h++) {
    // Assign to elements using indexing:
    for (int i = 0; i < kNumElems; i++) {
      myContainer[i] = i;
    }
  }

  start = clock() - start;

  cout << "Deque test completed in ";
  cout << (static_cast<double>(start) / CLOCKS_PER_SEC);
  cout << " seconds." << endl;
}

int main() {
  RunVectorTest();
  RunDequeTest();

  return 0;
}
