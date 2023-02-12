#ifndef STOCK_HPP_
#define STOCK_HPP_

#include <iostream>
#include <string>

class Observer
{
public:
    virtual void update(/*...*/) = 0;
    virtual ~Observer()
    {
    }
};

// Subject
class Stock
{
private:
    std::string symbol_;
    double price_;
    // TODO - kontener przechowywujacy obserwatorow
public:
    Stock(const std::string& symbol, double price) : symbol_(symbol), price_(price)
    {
    }

    std::string get_symbol() const
    {
        return symbol_;
    }

    double get_price() const
    {
        return price_;
    }

    // TODO: rejestracja obserwatora

    // TODO: wyrejestrowanie obserwatora

    void set_price(double price)
    {
        price_ = price;

        // TODO: powiadomienie inwestorow o zmianie kursu...
    }
};

class Investor : public Observer
{
    std::string name_;

public:
    Investor(const std::string& name) : name_(name)
    {
    }

    void update(/*...*/)
    {
        // TODO: implementacja
    }
};

#endif /*STOCK_HPP_*/
