#include <iostream>

class Dispenser {
public:
    Dispenser(Dispenser* successor = nullptr) : successor(successor) {}

    virtual void dispense(int amount) = 0;

    virtual ~Dispenser() {}

protected:
    Dispenser* successor;
};

class ConcreteDispenserA : public Dispenser {
public:
    ConcreteDispenserA(Dispenser* successor = nullptr) : Dispenser(successor) {}

    void dispense(int amount) override {
        if (amount >= 2000) {
            int numNotes = amount / 2000;
            int remainder = amount % 2000;
            std::cout << "Dispensing " << numNotes << " notes of 2000 rupees\n";
            if (remainder != 0) {
                successor->dispense(remainder);
            }
        }
        else {
            successor->dispense(amount);
        }
    }
};

class ConcreteDispenserB : public Dispenser {
public:
    ConcreteDispenserB(Dispenser* successor = nullptr) : Dispenser(successor) {}

    void dispense(int amount) override {
        if (amount >= 500) {
            int numNotes = amount / 500;
            int remainder = amount % 500;
            std::cout << "Dispensing " << numNotes << " notes of 500 rupees\n";
            if (remainder != 0) {
                successor->dispense(remainder);
            }
        }
        else {
            successor->dispense(amount);
        }
    }
};

class ConcreteDispenserC : public Dispenser {
public:
    ConcreteDispenserC(Dispenser* successor = nullptr) : Dispenser(successor) {}

    void dispense(int amount) override {
        if (amount >= 100) {
            int numNotes = amount / 100;
            int remainder = amount % 100;
            std::cout << "Dispensing " << numNotes << " notes of 100 rupees\n";
            if (remainder != 0) {
                successor->dispense(remainder);
            }
        }
        else {
            successor->dispense(amount);
        }
    }
};

class ConcreteDispenserD : public Dispenser {
public:
    ConcreteDispenserD(Dispenser* successor = nullptr) : Dispenser(successor) {}

    void dispense(int amount) override {
        if (amount >= 50) {
            int numNotes = amount / 50;
            int remainder = amount % 50;
            std::cout << "Dispensing " << numNotes << " notes of 50 rupees\n";
            if (remainder != 0) {
                successor->dispense(remainder);
            }
        }
        else {
            std::cout << "Amount cannot be dispensed with 50 rupees notes\n";
        }
    }
};

// Client code
int main() {
    Dispenser* dispenser = new ConcreteDispenserA(new ConcreteDispenserB(new ConcreteDispenserC(new ConcreteDispenserD)));
    int amount;
    std::cout << "Enter the amount to withdraw: ";
    std::cin >> amount;
    dispenser->dispense(amount);
    delete dispenser;
    return 0;
}
