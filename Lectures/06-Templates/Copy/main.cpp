#include <deque>
#include <set>
#include <iostream>

using namespace std;

template<typename InputIterator, typename OutputIterator>
OutputIterator MyCopy(InputIterator first, InputIterator last, OutputIterator destination) {
  // As long as we have more elements to process:
  while (first!=last) {
    // copy and advance destination:
    *destination = *first;
    ++destination;
    // advance the input range:
    ++first;
  }
  return destination;
}

int main() {
  // Populate a basic set
  set<int> source;
  for (int i = 0; i < 20; ++i) {
    source.insert(i);
  }

  //copy over contents of set into deque
  deque<int> results(20);
  MyCopy(source.begin(), source.end(), results.begin());

  //print out contents of new deque
  for (size_t i = 0; i < results.size(); ++i) {
    cout << results[i] << ' ';
  }
  cout << endl;

  return 0;
}
