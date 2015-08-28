#include <iostream>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
  // Open an ifstream representing a file full of integers:
  ifstream input("numbers.txt");
  
  // Construct an istream_iterator using our istream.  This will allow us to
  // iterate through the values we read from our istream as if we were given a
  // collection of elements instead of a stream.
  istream_iterator<int> fileItr(input);
  // This bit's a little tricky -- constructing an istream_iterator without an
  // istream will construct a magical "end of file" position iterator.  This is
  // the value you'll usually use as the "end", because it will compare equal
  // with an istream_iterator when the other iterator has consumed all the
  // values it can.
  istream_iterator<int> endItr;
  // Now that we can access our collection in terms of iterators instead of in
  // terms of streams we can use all of the tools found in the <algorithm>
  // header.  This lets us do a lot of fun things:
  int sum = accumulate(fileItr, endItr, 0);
  
  cout << "Sum: " << sum << endl;
  
  return 0;
}
