// Question:

// You are developing a shipping system for an e-commerce platform. 
// The platform needs to calculate shipping costs based on different strategies, 
// such as standard shipping, expedited shipping, and free shipping. 
// Implement the Strategy design pattern to allow the platform to dynamically switch between 
// different shipping cost calculation strategies. 
// Create a set of classes representing the strategies and a context class that uses these strategies.

// Requirements:

// Define an interface for the ShippingStrategy with a method to calculate the shipping cost.
// Implement concrete strategy classes for StandardShipping, ExpeditedShipping, and FreeShipping, each providing its own implementation for calculating shipping costs.
// Define a context class, ShippingContext, that has a reference to a ShippingStrategy and uses it to calculate shipping costs.
// The client code should be able to switch between different shipping strategies dynamically.


#include <iostream>
#include <string>

using namespace std;


class ShippingStrategy{
    public:
        virtual int getShippingCost() = 0;
};

class StandardShipping : public ShippingStrategy{
    public:
        int getShippingCost(){
            return 10;
        }
};
class ExpeditedShipping : public ShippingStrategy{
    public:
        int getShippingCost(){
            return 50;
        }
};
class FreeShipping : public ShippingStrategy{
    public:
        int getShippingCost(){
            return 0;
        }
};

class ShippingStrategyFactory{
    public:
        static ShippingStrategy* getShippingStrategy(string strategy){
            if(strategy=="Expedited")
                return new ExpeditedShipping();
            else if(strategy=="Free")
                return new FreeShipping();
            else
                return new StandardShipping();
        }
};

class ShippingContext{
    private:
        ShippingStrategy* obj;
    public:
        ShippingContext(ShippingStrategy* strategy){
            obj = strategy;
        }

        int getTotalOrderCost(int productCost){
            return productCost + obj->getShippingCost();
        }
};

int main() {
    // Standard shipping
    ShippingStrategy* standardShipping = ShippingStrategyFactory::getShippingStrategy("Standard");
    ShippingContext* standardContext = new ShippingContext(standardShipping);

    double standardCost = standardContext->getTotalOrderCost(100.0);
    std::cout << "Standard Shipping Cost: $" << standardCost << std::endl;

    delete standardShipping;
    delete standardContext;

    // Expedited shipping
    ShippingStrategy* expeditedShipping = ShippingStrategyFactory::getShippingStrategy("Expedited");
    ShippingContext* expeditedContext = new ShippingContext(expeditedShipping);

    double expeditedCost = expeditedContext->getTotalOrderCost(100.0);
    std::cout << "Expedited Shipping Cost: $" << expeditedCost << std::endl;

    delete expeditedShipping;
    delete expeditedContext;

    // Free shipping
    ShippingStrategy* freeShipping = ShippingStrategyFactory::getShippingStrategy("Free");
    ShippingContext* freeContext = new ShippingContext(freeShipping);

    double freeCost = freeContext->getTotalOrderCost(100.0);
    std::cout << "Free Shipping Cost: $" << freeCost << std::endl;

    delete freeShipping;
    delete freeContext;

    return 0;
}
