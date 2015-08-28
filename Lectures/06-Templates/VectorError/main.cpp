#include <vector>
#include <iostream>
using namespace std;

template <typename T>
void print(T& x) {
    cout << x << endl;
}

int main() {
    vector<int> v;
    print(v);
}
