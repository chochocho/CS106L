#include <memory>
#include <iostream>
using namespace std;

int main() {
  shared_ptr<int> x(new int(4));
  cout << *x << endl;
  shared_ptr<int> y = x;
  *y = 8;
  cout << *x << endl;
}
