#include <iostream>
#include <string>

// Implementor interface
class BreathingImpl {
public:
    virtual void breathe() = 0;
    virtual ~BreathingImpl() {}
};

// Concrete Implementor 1: Breathe through nose
class NoseBreathing : public BreathingImpl {
public:
    void breathe() override {
        std::cout << "Breathing through nose." << std::endl;
    }
};

// Concrete Implementor 2: Breathe through gills
class GillsBreathing : public BreathingImpl {
public:
    void breathe() override {
        std::cout << "Breathing through gills." << std::endl;
    }
};

// Concrete Implementor 3: Breathe through leaves
class LeavesBreathing : public BreathingImpl {
public:
    void breathe() override {
        std::cout << "Breathing through leaves." << std::endl;
    }
};

// Abstraction: LivingThings
class LivingThings {
protected:
    BreathingImpl* breathingImpl;

public:
    LivingThings(BreathingImpl* impl) : breathingImpl(impl) {}

    virtual void breathe() {
        if (breathingImpl) {
            breathingImpl->breathe();
        } else {
            std::cout << "No breathing implementation provided." << std::endl;
        }
    }

    virtual ~LivingThings() {
        delete breathingImpl;
    }
};

// Refined Abstraction 1: Land Animals
class LandAnimals : public LivingThings {
public:
    LandAnimals(BreathingImpl* impl) : LivingThings(impl) {}
};

// Refined Abstraction 2: Water Animals
class WaterAnimals : public LivingThings {
public:
    WaterAnimals(BreathingImpl* impl) : LivingThings(impl) {}
};

// Refined Abstraction 3: Plants
class Plants : public LivingThings {
public:
    Plants(BreathingImpl* impl) : LivingThings(impl) {}
};

int main() {
    // Land animal breathing through nose
    LandAnimals lion(new NoseBreathing());
    std::cout << "Lion: ";
    lion.breathe();

    // Water animal breathing through gills
    WaterAnimals fish(new GillsBreathing());
    std::cout << "Fish: ";
    fish.breathe();

    // Plant breathing through leaves
    Plants tree(new LeavesBreathing());
    std::cout << "Tree: ";
    tree.breathe();

    return 0;
}
