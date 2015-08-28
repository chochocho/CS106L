#include <iostream>
#include <vector>
#include <algorithm>
#include "MagicHelper.h"

using namespace std;

int main() {
  // We start off by creating a vector of integers containing the numbers 1-9.
  // This ordering is very important, because it's the "lexicographically
  // smallest" ordering of the numbers 1-9.
  //
  // You can think of the "lexicographically smallest" ordering as the ordering
  // which would be produced if you sorted your elements.
  vector<int> arrangement;
  for (int i = 1; i <= 9; i++)
    arrangement.push_back(i);

  // We'll loop over all permutations of our vector...
  while (true) {
    // If we find a valid magic square, print it
    if (IsValidMagicSquare(arrangement)) {
      cout << "Found a solution!" << endl;
      PrintSquare(arrangement);
    }
    // These two lines are the really fun part of this algorithm.
    //
    // The next_permutation function will rearrange the elements inside of
    // 'arrangement', so that they represent a new and unique permutation of
    // the elements 1-9.  The function will do all of the reordering for us,
    // and the boolean return value will indicate whether or not there are more
    // values to consider.
    //
    // By repeatedly calling this function in a loop, we end up iterating over
    // all of the possible permutations of the numbers 1-9, and hence all magic
    // square candidates which use each of the numbers 1-9 only once.
    bool another = next_permutation(arrangement.begin(), arrangement.end());
    if (!another) break;
  }

  return 0;
}
