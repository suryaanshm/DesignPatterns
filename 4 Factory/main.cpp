#include <iostream>
#include <string>

// Base class for vehicles
class Vehicle {
public:
    virtual void drive() const = 0;
};

// Concrete bike class
class Bike : public Vehicle {
public:
    void drive() const override {
        std::cout << "Riding a bike\n";
    }
};

// Concrete car class
class Car : public Vehicle {
public:
    void drive() const override {
        std::cout << "Driving a car\n";
    }
};

class VehicleFactory{
    public:
    static Vehicle* createVehicle(std::string s){
        if(s=="car") return new Car;
        if (s=="bike") return new Bike;
        return nullptr;
    }
};

int main() {
    VehicleFactory* factory = new VehicleFactory();
    
    Vehicle* bike = factory->createVehicle("bike");
    bike->drive();
    delete bike;

    Vehicle* car = factory->createVehicle("car");
    car->drive();
    delete car;
    
    delete factory;

    return 0;
}
