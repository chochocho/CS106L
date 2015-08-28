#include <iostream>
#include <map>

using namespace std;

int main() {
    // We first populate this map of integers with the numbers from 0 to 9,
    // inclusive with the associated values 0 to 90.
    map<int, int> container;
    for (int i = 0; i < 10; ++i)
        container[i] = 10 * i;

    // Now, we iterate through the container and print each element one at a time.
    // We do this using an iterator object which starts at the container's
    // beginning. We keep looping as long as we haven't hit the end of the
    // container yet. Inside the loop, we ask for the current value (*itr), and
    // then instruct the iterator to move to the next location (++itr). Note that
    // using a map results in an iterator of pairs, hence the .first and .second
    map<int, int>::iterator itr = container.begin();
    while (itr != container.end()) {
        cout << "10 * " << (*itr).first << " = " << (*itr).second << endl;
        ++itr;
    }

    return 0;
}
