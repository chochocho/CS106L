#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

// declare main and error to make the compiler happy
int main() {
    return 0;
}
void error(string error) {
    exit(-1);
}

// Implement the functions

string integerToString(int n) {
   ostringstream stream;
   stream << n;
   return stream.str();
}

int stringToInteger(string str) {
   istringstream stream(str);
   int value;
   stream >> value >> ws;
   if (stream.fail() || !stream.eof()) {
      error("stringToInteger: Illegal integer format (" + str + ")");
   }
   return value;
}

string realToString(double d) {
   ostringstream stream;
   stream << uppercase << d;
   return stream.str();
}

double stringToReal(string str) {
   istringstream stream(str);
   double value;
   stream >> value >> ws;
   if (stream.fail() || !stream.eof()) {
      error("stringToReal: Illegal floating-point format (" + str + ")");
   }
   return value;
}

