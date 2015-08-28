#pragma once
#include "Person.h"

class Student : public Person {
public:
    Student(std::string name = "", int age = 0, 
        std::string school = "Stanford", 
        std::string id = "00000000"):Person::Person(name, age), school(school), id(id) {

    }

    std::string getSchool() {
        return school;
    }

    std::string getId() {
        return id;
    }

private:
    std::string school;
    std::string id;
};
