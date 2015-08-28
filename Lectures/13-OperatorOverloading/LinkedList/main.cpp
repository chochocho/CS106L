#include "LinkedList.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    ifstream input("haiku.txt");
    LinkedList<string> list;

    string line;
    while (getline(input, line))
        list.insert(line);

    // We just want to iterate through the linked list and print everything out.
    // We implemented operator==, but not operator!=, but we would be able to use
    // itr != list.end() if we were to add the latter. The implementation is very
    // straightforward if you understand the implementation of operator==.
    for (LinkedList<string>::const_iterator itr = list.begin(); !(itr == list.end()); ++itr)
        cout << *itr << endl;

    // We would also like to support the "arrow" operator to access specific
    // fields and member functions in whatever the iterator is pointing at.
    for (LinkedList<string>::const_iterator itr = list.begin(); !(itr == list.end()); ++itr)
        cout << itr->size() << endl;

    return 0;
}
