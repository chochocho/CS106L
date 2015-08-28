#include "Student.h"
#include <iostream>

using namespace std;

int main() {
    /* We can still use person since student #includes Person.
    This will work just the same as if student never existed.*/
    Person p("Obama", 46);
    cout << p.getName() <<  " " << p.getAge() << endl;

    /* We can also create a student just as if it were a normal 
    class. Note that we can still call Person's methods on it
    since it inherits from person */
    Student s("Kevin Miller", 21, "Stanford", "kmiller4");
    cout << s.getName() << " " << s.getAge() << " " 
        << s.getSchool() << " " << s.getId() << endl; 
 
}
