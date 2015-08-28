#include <deque>
#include <set>
#include <iostream>

using namespace std;

template<typename InputIterator, typename OutputIterator, typename CriteriaFn>
OutputIterator CopyIf(InputIterator first, InputIterator last, OutputIterator destination, CriteriaFn criteriaFn) {
  // As long as we have more elements to process:
  while (first!=last) {
    // Only copy and advance destination if the test passes:
    if (criteriaFn(*first)) {
      *destination = *first;
      ++destination;
    }
    // Always advance the input range:
    ++first;
  }
  return destination;
}

// This is our criteria: only even numbers allowed.
bool IsEven(int value) {
  return value % 2 == 0;
}

int main() {
  // Populate a basic set
  set<int> source;
  for (int i = 0; i < 20; ++i) {
    source.insert(i);
  }

  // Copy over all even numbers from set into deque
  deque<int> results(10);
  CopyIf(source.begin(), source.end(), results.begin(), IsEven);

  for (size_t i = 0; i < results.size(); ++i) {
    cout << results[i] << ' ';
  }
  cout << endl;

  return 0;
}
