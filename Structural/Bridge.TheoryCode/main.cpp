#include "bridge.hpp"

using namespace std;

int main()
{
    auto implA = shared_ptr<Implementor>{make_shared<ConcreteImplementorA>()};
    auto implB = shared_ptr<Implementor>{make_shared<ConcreteImplementorB>()};

    auto ab = make_shared<Abstraction>(implA);
    ab->operation();

    // Change implemention and call
    ab->set_implementor(implB);
    ab->operation();

    auto refined_ab = make_shared<RefinedAbstraction>(implB);
    refined_ab->operation();
}