#include <iostream>
#include <string>

// Abstract Vehicle class
class Vehicle {
public:
    virtual int getFuelTankCapacity() const = 0;
    virtual int getSeatingCapacity() const = 0;
    virtual ~Vehicle() {}
};

// Concrete Car class
class Car : public Vehicle {
public:
    int getFuelTankCapacity() const override {
        return 50; // Example value for car fuel tank capacity
    }

    int getSeatingCapacity() const override {
        return 5; // Example value for car seating capacity
    }
};

// Concrete Bike class
class Bike : public Vehicle {
public:
    int getFuelTankCapacity() const override {
        return 10; // Example value for bike fuel tank capacity
    }

    int getSeatingCapacity() const override {
        return 2; // Example value for bike seating capacity
    }
};

// Null Object class for Vehicle
class NullVehicle : public Vehicle {
public:
    int getFuelTankCapacity() const override {
        return 0; // Default value for fuel tank capacity
    }

    int getSeatingCapacity() const override {
        return 0; // Default value for seating capacity
    }
};

class VehicleFactory{
public:
    static Vehicle* getVehicle(std::string type){
        if(type=="Car") return new Car();
        if(type=="Bike") return new Bike();
        return new NullVehicle();
    }
};

int main() {
    Vehicle* car = VehicleFactory::getVehicle("Car");
    Vehicle* bike = VehicleFactory::getVehicle("Bike");
    Vehicle* nullVehicle = VehicleFactory::getVehicle("Random");

    // Print details of car
    std::cout << "Car - Fuel tank capacity: " << car->getFuelTankCapacity() << " liters, Seating capacity: " << car->getSeatingCapacity() << " persons" << std::endl;

    // Print details of bike
    std::cout << "Bike - Fuel tank capacity: " << bike->getFuelTankCapacity() << " liters, Seating capacity: " << bike->getSeatingCapacity() << " persons" << std::endl;

    // Print details of null object
    std::cout << "Null Object - Fuel tank capacity: " << nullVehicle->getFuelTankCapacity() << " liters, Seating capacity: " << nullVehicle->getSeatingCapacity() << " persons" << std::endl;

    // Clean up
    delete car;
    delete bike;
    delete nullVehicle;

    return 0;
}
