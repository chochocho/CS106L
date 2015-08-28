#include <string>

class Bird {
public:
    Bird(std::string type);

    /* Destructors should always be virtual even if they
    are empty in the base class since you never know
    if some derived class will need a destructor */
    virtual ~Bird() {}
    
    std::string getType();
    virtual void fly();

private:
    std::string type;
};
