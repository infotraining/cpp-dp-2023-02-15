#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include <variant>

using namespace std::literals;

namespace DynamicPolymorphism
{
    class Pickup
    {
    public:
        virtual std::string convert_signal(const std::string& string_vibrations) const = 0;
        virtual ~Pickup() = default;
    };
    
    class SingleCoil : public Pickup
    {
    public:
        std::string convert_signal(const std::string& string_vibrations) const override
        {
            return "humming "s + string_vibrations;
        }
    };

    class Humbucker : public Pickup
    {
    public:
        std::string convert_signal(const std::string& string_vibrations) const override
        {
            return "strong, noiseless "s + string_vibrations;
        }
    };

    class Guitar
    {
        std::unique_ptr<Pickup> pickup_;

    public:
        Guitar(std::unique_ptr<Pickup> pickup)
            : pickup_{std::move(pickup)}
        {
            assert(pickup_ != nullptr);
        }

        void play(const std::string& sound)
        {
            std::cout << "Playing " << pickup_->convert_signal(sound) << std::endl;
        }
    };
}

namespace StaticPolymorphism
{
    class SingleCoil
    {
    public:
        std::string convert_signal(const std::string& string_vibrations) const
        {
            return "humming "s + string_vibrations;
        }
    };

    class Humbucker
    {
    public:
        std::string convert_signal(const std::string& string_vibrations) const
        {
            return "strong, noiseless "s + string_vibrations;
        }
    };

    template <typename TPickup_>
    class Guitar
    {
        TPickup_ pickup_;

    public:
        Guitar() = default;

        Guitar(TPickup_ pickup)
            : pickup_{std::move(pickup)}
        {
        }

        void play(const std::string& sound)
        {
            std::cout << "Playing " << pickup_.convert_signal(sound) << std::endl;
        }
    };
}

namespace DuckTyping
{
    using Pickup = std::function<std::string(const std::string&)>;

    class SingleCoil
    {
    public:
        std::string operator()(const std::string& string_vibrations) const
        {
            return "humming "s + string_vibrations;
        }
    };

    class Humbucker
    {
    public:
        std::string operator()(const std::string& string_vibrations) const
        {
            return "strong, noiseless "s + string_vibrations;
        }
    };

    struct Guitar
    {
        Pickup pickup;

        Guitar(Pickup pickup)
            : pickup{std::move(pickup)}
        {      
        }

        void play(const std::string& sound)
        {
            std::cout << "Playing " << pickup(sound) << std::endl;
        }
    };
}

namespace VariantPolymorphism
{
    class SingleCoil
    {
    public:
        std::string convert_signal(const std::string& string_vibrations) const
        {
            return "humming "s + string_vibrations;
        }
    };

    class Humbucker
    {
    public:
        std::string convert_signal(const std::string& string_vibrations) const
        {
            return "strong, noiseless "s + string_vibrations;
        }
    };

    using Pickup = std::variant<SingleCoil, Humbucker>;

    class Guitar
    {
        Pickup pickup_;

    public:
        Guitar() = default;

        Guitar(Pickup pickup)
            : pickup_{std::move(pickup)}
        {
        }

        void play(const std::string& sound)
        {
            std::cout << "Playing ";
            
            std::cout << std::visit([&sound](auto& p) { return p.convert_signal(sound);}, pickup_);

            std::cout << std::endl;
        }
    };
}

int main()
{
    {
        using namespace DynamicPolymorphism;

        Guitar strat{std::make_unique<SingleCoil>()};
        strat.play("D-power-cord");

        Guitar les_paul{std::make_unique<Humbucker>()}; // runtime config
        les_paul.play("D-power-cord");
    }

    {
        using namespace StaticPolymorphism;

        Guitar strat{SingleCoil{}}; // CTAD
        strat.play("D-power-cord");

        Guitar<Humbucker> les_paul; // compile-time config
        les_paul.play("D-power-cord");
    }

    {
        using namespace DuckTyping;

        SingleCoil sc;

        Guitar g{std::move(sc)};

        g.play("D-power-cord");

        g.pickup = [](const std::string& string_vibrations)
        {
            return "strong, noiseless "s + string_vibrations;
        };

        g.play("A-power-cord");
    }

    {
        using namespace VariantPolymorphism;

        SingleCoil sc;
        Humbucker h;

        Guitar g{h};
        g.play("E-power-cord");
    }
}

struct PrintVisitor
{
    void operator()(int x) 
    {
        std::cout << "int: " << x << "\n";
    }

    void operator()(double x) 
    {
        std::cout << "double: " << x << "\n";
    }

    void operator()(const std::string& x) 
    {
        std::cout << "string: " << x << "\n";
    }
};

void varaint_explain()
{
    using namespace std::literals;

    std::variant<int, double, std::string> v1;

    v1 = 42;
    v1 = 3.14;
    //v1 = "text"s;

    std::cout << std::get<std::string>(v1) << "\n";

    std::visit(PrintVisitor{}, v1);
    std::visit([](const auto& x) { std::cout << x << "\n";}, v1);
}