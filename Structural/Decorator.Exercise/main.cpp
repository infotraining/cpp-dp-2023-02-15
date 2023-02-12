#include "starbugs_coffee.hpp"
#include <memory>

void client(std::unique_ptr<Coffee> coffee)
{
    std::cout << "Description: " << coffee->get_description() << "; Price: " << coffee->get_total_price() << std::endl;
    coffee->prepare();
}

int main()
{
    std::unique_ptr<Coffee> cf = std::make_unique<Espresso>();
    client(std::move(cf));
}
