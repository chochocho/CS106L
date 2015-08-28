#include <ctime>
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

// These constants dictate how many elements we insert, and how many times we
// run the test:
static const int kNumElems = 10000;
static const int kNumTests = 200;

void RunVectorTest() {
  clock_t start = clock();
  vector<int> myContainer;

  for (int h = 0; h < kNumTests; h++) {
    // Insert all elements at the beginning:
    for (int i = 0; i < kNumElems; i++) {
      myContainer.insert(myContainer.begin(), i);
    }

    // Erase all elements from the beginning:
    for (int i = 0; i < kNumElems; i++) {
      myContainer.erase(myContainer.begin());
    }
  }

  start = clock() - start;

  cout << "Vector finished in ";
  cout << (static_cast<double>(start) / CLOCKS_PER_SEC);
  cout << " seconds." << endl;
}

void RunDequeTest() {
  clock_t start = clock();
  deque<int> myContainer;

  for (int h = 0; h < kNumTests; h++) {
    // Push all elements at the front:
    for (int i = 0; i < kNumElems; i++) {
      myContainer.push_front(i);
    }

    // Pop all elements from the front:
    for (int i = 0; i < kNumElems; i++) {
      myContainer.pop_front();
    }
  }

  start = clock() - start;

  cout << "Deque finished in ";
  cout << (static_cast<double>(start) / CLOCKS_PER_SEC);
  cout << " seconds." << endl;
}

int main() {
  RunVectorTest();
  RunDequeTest();

  return 0;
}
