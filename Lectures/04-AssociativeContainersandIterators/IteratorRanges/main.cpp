#include <set>
#include <iostream>

using namespace std;

int main() {
    // We insert ONE MIIIILLION elements into the set, all multiples of five. This
    // set is large enough that we don't want to iterate through it, one element
    // at a time.
    set<int> mySet;
    for (int i = 0; i < 1000000; ++i)
        mySet.insert(5 * i);

    cout << "Done with setup!" << endl;

    // Instead of iterating through the entire set from mySet.begin() to
    // mySet.end(), we are going to iterate through a slice. lower_bound and
    // upper_bound help us find the beginning and end of that slice. By using
    // lower_bound for the begin iterator and upper_bound for the end iterator,
    // we have a range that's inclusive on both ends -- that is, if 297 and 323
    // were in the set, they would both be included in the loop.
    set<int>::iterator itrBegin = mySet.lower_bound(297);
    set<int>::iterator itrEnd = mySet.upper_bound(323);
    for (set<int>::iterator itr = itrBegin; itr != itrEnd; ++itr)
        cout << *itr << ' ';

    cout << endl;

    return 0;
}
