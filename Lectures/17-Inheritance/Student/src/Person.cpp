#include "Person.h"

using namespace std;

Person::Person(string name, int age):name(name), age(age) {}

void Person::setAge(int age) {
    this->age = age;
}

void Person::setName(string name) {
    this->name = name;
}

int Person::getAge() {
    return age;
}

string Person::getName() {
    return name;
}
