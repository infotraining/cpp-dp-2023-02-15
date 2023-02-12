#ifndef FACADE_HPP_
#define FACADE_HPP_

#include <iostream>
#include <memory>
#include <string>

// "Subsystem ClassA"
class SubSystemOne
{
public:
    void method_one()
    {
        std::cout << "SubSystemOne method" << std::endl;
    }
};

// "Subsystem ClassB"
class SubSystemTwo
{
public:
    void method_two()
    {
        std::cout << "SubSystemTwo method" << std::endl;
    }
};

// Subsystem ClassC"
class SubSystemThree
{
public:
    void method_three()
    {
        std::cout << "SubSystemThree method" << std::endl;
    }
};

// Subsystem ClassD"
class SubSystemFour
{
public:
    void method_four()
    {
        std::cout << "SubSystemFour method" << std::endl;
    }
};

// "Facade"
class Facade
{
    SubSystemOne one;
    SubSystemTwo two;
    SubSystemThree three;
    SubSystemFour four;

public:
    Facade() = default;

    void methodA()
    {
        std::cout << "MethodA() ---- \n";
        one.method_one();
        two.method_two();
        four.method_four();
    }

    void methodB()
    {
        std::cout << "MethodB() ---- \n";
        two.method_two();
        three.method_three();
    }
};

#endif /*FACADE_HPP_*/
