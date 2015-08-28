#include "Bird.h"
#include <iostream>

using namespace std;

Bird::Bird(string type):type(type){}

string Bird::getType() {
    return type;
}

void Bird::fly() {
    cout << "I'M FLYING!" << endl;
}
