#include "MagicHelper.h"
#include <vector>
#include <iostream>
using namespace std;

bool IsValidMagicSquare(vector<int>& square) {
  // Make sure the diagonals sum to the same value:
  int rightDiagonal = square[0] + square[4] + square[8];
  int leftDiagonal = square[2] + square[4] + square[6];
  if (leftDiagonal != rightDiagonal)
    return false;

  // Check all three rows and columns:
  for (int i = 0; i < 3; ++i) {
    int rowSum = 0;
    int colSum = 0;
    for (int j = 0; j < 3; ++j) {
      rowSum += square[i * 3 + j];
      colSum += square[j * 3 + i];
    }

    if (rowSum != leftDiagonal || colSum != leftDiagonal)
      return false;
  }

  return true;
}

void PrintSquare(vector<int>& square) {
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col)
      cout << square[row * 3 + col] << ' ';
    cout << endl;
  }
}
