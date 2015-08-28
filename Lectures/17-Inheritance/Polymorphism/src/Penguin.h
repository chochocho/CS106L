#pragma once
#include <iostream>
#include "Bird.h"

class Penguin : public Bird {
public:
    Penguin();
    virtual ~Penguin();
    /* notice that fly is declared virtual. This means
    the program will decide at run time which function to call
    to enable polymorphism. If fly were not virtual, the following 
    code would call Bird::fly:
    Bird *b = new Penguin; b->fly(); */
    virtual void fly();

private:
    int* chicks;
};

Penguin::Penguin():Bird::Bird("Penguin"), chick(new int[5]){}

Penguin::~Penguin() {
    delete[] chicks;
}

void Penguin::fly() {
    std::cout << "SPLAT!" << std::endl;
}
