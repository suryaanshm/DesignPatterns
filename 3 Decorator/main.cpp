#include <iostream>
#include <string>

class Pizza {
public:
    virtual ~Pizza() {}
    virtual std::string getDescription() const = 0;
    virtual double getCost() const = 0;
};

class Margherita : public Pizza {
public:
    std::string getDescription() const override {
        return "Margherita";
    }

    double getCost() const override {
        return 5.0;
    }
};

class PizzaDecorator : public Pizza {
protected:
    Pizza* pizza;

public:
    PizzaDecorator(Pizza* pizza) : pizza(pizza) {}

    std::string getDescription() const override {
        return pizza->getDescription();
    }

    double getCost() const override {
        return pizza->getCost();
    }
};

class Cheese : public PizzaDecorator {
public:
    Cheese(Pizza* pizza) : PizzaDecorator(pizza) {}

    std::string getDescription() const override {
        return pizza->getDescription() + " + Cheese";
    }

    double getCost() const override {
        return pizza->getCost() + 2.5;
    }
};

class Pepperoni : public PizzaDecorator {
public:
    Pepperoni(Pizza* pizza) : PizzaDecorator(pizza) {}

    std::string getDescription() const override {
        return pizza->getDescription() + " + Pepperoni";
    }

    double getCost() const override {
        return pizza->getCost() + 2.0;
    }
};

int main() {
    Pizza* pizza = new Pepperoni(new Cheese(new Margherita()));

    std::cout << "Description: " << pizza->getDescription() << std::endl;
    std::cout << "Cost: $" << pizza->getCost() << std::endl;

    delete pizza;

    return 0;
}
