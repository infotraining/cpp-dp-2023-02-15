#ifndef BRIDGE_HPP_
#define BRIDGE_HPP_

#include <iostream>
#include <memory>

class Implementor
{
public:
    virtual void primitive_operation() = 0;
    virtual ~Implementor() = default;
};

// "Abstraction"
class Abstraction
{
protected:
    std::shared_ptr<Implementor> implementor_;

public:
    Abstraction(std::shared_ptr<Implementor> impl) : implementor_{impl}
    {
    }

    void set_implementor(std::shared_ptr<Implementor> impl)
    {
        implementor_ = impl;
    }

    virtual void operation()
    {
        implementor_->primitive_operation();
    }

    virtual ~Abstraction() = default;
};

// "Implementor"

// "RefinedAbstraction"
class RefinedAbstraction : public Abstraction
{
public:
    using Abstraction::Abstraction;

    void operation() override
    {
        std::cout << "Refined ";
        implementor_->primitive_operation();
    }
};

// "ConcreteImplementorA"
class ConcreteImplementorA : public Implementor
{
public:
    void primitive_operation()
    {
        std::cout << "ConcreteImplementorA Operation" << std::endl;
    }
};

// "ConcreteImplementorB"
class ConcreteImplementorB : public Implementor
{
public:
    void primitive_operation()
    {
        std::cout << "ConcreteImplementorB Operation" << std::endl;
    }
};

#endif /*BRIDGE_HPP_*/
