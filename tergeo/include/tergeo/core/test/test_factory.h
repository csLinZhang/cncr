#ifndef TERGEO_CORE_TEST_TEST_FACTORY_H_
#define TERGEO_CORE_TEST_TEST_FACTORY_H_
#include <iostream>
#include "tergeo/core/factory.h"

namespace tergeo {
namespace test {
namespace core {
class TestObject : public tergeo::core::IPlugin {
    DECLARE_FACTORY(TestObject)
public:
    TestObject() {}
    ~TestObject() {std::cout << "release TestObject" << std::endl;}

    virtual void print() {
        std::cout << "this is " << getClassName() << std::endl; 
    }
};

class TestObjectSub1 : public TestObject {
public:
    TestObjectSub1() {}
    ~TestObjectSub1() {std::cout << "release TestObjectSub1" << std::endl;}
    virtual void print() {
        std::cout << "this is " << getClassName() << std::endl; 
    }
    void printObject1() const {
        std::cout << "print: " << getClassName() << std::endl;
    }
};

class TestObjectSub2 : public TestObject {
public:
    TestObjectSub2() {}
    ~TestObjectSub2() {std::cout << "release TestObjectSub2" << std::endl;}
    virtual void print() {
        std::cout << "this is " << getClassName() << std::endl; 
    }
    void printObject2() const {
        std::cout << "print: " << getClassName() << std::endl;
    }
};

}
}
}

#endif