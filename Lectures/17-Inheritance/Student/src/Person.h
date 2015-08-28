#pragma once
#include <string>

class Person {
public:
    Person(std::string name = "", int age = 0);
    
    void setAge(int age);
    void setName(std::string name);

    int getAge();
    std::string getName();

private:
    std::string name;
    int age;
};
