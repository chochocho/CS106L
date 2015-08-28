#ifndef _MAGICHELPER_H
#define _MAGICHELPER_H
#include <vector>
using namespace std;

// This is in a separate file because the operation of these functions isn't
// critical to understanding how the algorithm works.

// IsValidMagicSquare accepts a magic square in the form of a vector and returns
// true if and only if that vectore represents a valid magic square.
bool IsValidMagicSquare(vector<int>& square);

// PrintSquare accepts a vector representing a magic square and prints it out in
// a nice, 3x3 square format.
void PrintSquare(vector<int>& square);

#endif
