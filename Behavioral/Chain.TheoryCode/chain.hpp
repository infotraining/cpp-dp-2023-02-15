#ifndef CHAIN_HPP_
#define CHAIN_HPP_

#include <iostream>
#include <memory>
#include <string>

// "Handler"
class Handler
{
protected:
    std::shared_ptr<Handler> successor_;

public:
    Handler()
        : successor_{nullptr}
    {
    }

    virtual ~Handler() = default;

    void set_successor(std::shared_ptr<Handler> successor)
    {
        successor_ = successor;
    }

    void handle_request(int request)
    {
        if (is_satisfied(request))
            process_request(request);
        else if (successor_ != nullptr)
            successor_->handle_request(request);
    }

protected:
    virtual bool is_satisfied(int request) const = 0;
    virtual void process_request(int request) = 0;
};

// "ConcreteHandler1"
class ConcreteHandler1 : public Handler
{
protected:
    bool is_satisfied(int request) const override
    {
        return (request >= 0) && (request < 10);
    }

    void process_request(int request) override
    {
        std::cout << "ConcreteHandler1 handled request " << request << std::endl;
    }
};

// "ConcreteHandler2"
class ConcreteHandler2 : public Handler
{
protected:
    bool is_satisfied(int request) const override
    {
        return (request >= 10) && (request < 20);
    }

    void process_request(int request) override
    {
        std::cout << "ConcreteHandler2 handled request " << request << std::endl;
    }
};

// "ConcreteHandler3"
class ConcreteHandler3 : public Handler
{
protected:
    bool is_satisfied(int request) const override
    {
        return (request >= 20) && (request < 30);
    }

    void process_request(int request) override
    {
        std::cout << "ConcreteHandler3 handled request " << request << std::endl;
    }
};

#endif /*CHAIN_HPP_*/
