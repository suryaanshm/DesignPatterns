#include <iostream>

// Forward declaration of State class
class State;

// Context class: Vending Machine
class VendingMachine {
private:
    State* currentState;
    int totalAmount;

public:
    VendingMachine();

    ~VendingMachine();

    void setCurrentState(State* state);

    void insertMoney(int amount);

    void selectProduct(int productId);

    void dispenseProduct();

    void cancelTransaction();

    void addAmount(int amount);

    void resetAmount();

    int getTotalAmount() const;
};

// Abstract State class
class State {
public:
    virtual void insertMoney(VendingMachine* vendingMachine, int amount) = 0;
    virtual void selectProduct(VendingMachine* vendingMachine, int productId) = 0;
    virtual void dispenseProduct(VendingMachine* vendingMachine) = 0;
    virtual void cancelTransaction(VendingMachine* vendingMachine) = 0;
    virtual ~State() {}
};

// Concrete Idle state
class IdleState : public State {
public:
    void insertMoney(VendingMachine* vendingMachine, int amount) override;

    void selectProduct(VendingMachine* vendingMachine, int productId) override;

    void dispenseProduct(VendingMachine* vendingMachine) override;

    void cancelTransaction(VendingMachine* vendingMachine) override;
};

// Concrete Accepting Cash state
class AcceptingCashState : public State {
public:
    void insertMoney(VendingMachine* vendingMachine, int amount) override;

    void selectProduct(VendingMachine* vendingMachine, int productId) override;

    void dispenseProduct(VendingMachine* vendingMachine) override;

    void cancelTransaction(VendingMachine* vendingMachine) override;
};

// Concrete Dispensing state
class DispensingState : public State {
public:
    void insertMoney(VendingMachine* vendingMachine, int amount) override;

    void selectProduct(VendingMachine* vendingMachine, int productId) override;

    void dispenseProduct(VendingMachine* vendingMachine) override;

    void cancelTransaction(VendingMachine* vendingMachine) override;
};

// Implementation of VendingMachine methods
VendingMachine::VendingMachine() : currentState(new IdleState()), totalAmount(0) {}

VendingMachine::~VendingMachine() {
    delete currentState;
}

void VendingMachine::setCurrentState(State* state) {
    delete currentState;
    currentState = state;
}

void VendingMachine::insertMoney(int amount) {
    if (currentState)
        currentState->insertMoney(this, amount);
    else
        std::cout << "Vending machine is not operational." << std::endl;
}

void VendingMachine::selectProduct(int productId) {
    if (currentState)
        currentState->selectProduct(this, productId);
    else
        std::cout << "Vending machine is not operational." << std::endl;
}

void VendingMachine::dispenseProduct() {
    if (currentState)
        currentState->dispenseProduct(this);
    else
        std::cout << "Vending machine is not operational." << std::endl;
}

void VendingMachine::cancelTransaction() {
    if (currentState)
        currentState->cancelTransaction(this);
    else
        std::cout << "Vending machine is not operational." << std::endl;
}

void VendingMachine::addAmount(int amount) {
    totalAmount += amount;
}

void VendingMachine::resetAmount() {
    totalAmount = 0;
}

int VendingMachine::getTotalAmount() const {
    return totalAmount;
}

// Implementation of IdleState methods
void IdleState::insertMoney(VendingMachine* vendingMachine, int amount) {
    std::cout << "Money inserted: $" << amount << std::endl;
    vendingMachine->setCurrentState(new AcceptingCashState());
    vendingMachine->addAmount(amount);
}

void IdleState::selectProduct(VendingMachine* vendingMachine, int productId) {
    std::cout << "Please insert money first." << std::endl;
}

void IdleState::dispenseProduct(VendingMachine* vendingMachine) {
    std::cout << "Please select a product first." << std::endl;
}

void IdleState::cancelTransaction(VendingMachine* vendingMachine) {
    std::cout << "No transaction to cancel inside Idle state." << std::endl;
}

// Implementation of AcceptingCashState methods
void AcceptingCashState::insertMoney(VendingMachine* vendingMachine, int amount) {
    std::cout << "Money inserted: $" << amount << std::endl;
    vendingMachine->addAmount(amount);
}

void AcceptingCashState::selectProduct(VendingMachine* vendingMachine, int productId) {
    std::cout << "Product selected: " << productId << std::endl;
    vendingMachine->setCurrentState(new DispensingState());
}

void AcceptingCashState::dispenseProduct(VendingMachine* vendingMachine) {
    std::cout << "Please select a product first." << std::endl;
}

void AcceptingCashState::cancelTransaction(VendingMachine* vendingMachine) {
    std::cout << "Transaction cancelled." << std::endl;
    vendingMachine->resetAmount();
    vendingMachine->setCurrentState(new IdleState());
}

// Implementation of DispensingState methods
void DispensingState::insertMoney(VendingMachine* vendingMachine, int amount) {
    std::cout << "Already accepting cash. Cannot insert more money." << std::endl;
}

void DispensingState::selectProduct(VendingMachine* vendingMachine, int productId) {
    std::cout << "Already dispensing a product. Please wait." << std::endl;
}

void DispensingState::dispenseProduct(VendingMachine* vendingMachine) {
    std::cout << "Dispensing product..." << std::endl;
    vendingMachine->resetAmount();
    vendingMachine->setCurrentState(new IdleState());
}

void DispensingState::cancelTransaction(VendingMachine* vendingMachine) {
    std::cout << "Transaction cancelled." << std::endl;
    vendingMachine->resetAmount();
    vendingMachine->setCurrentState(new IdleState());
}

int main() {
    VendingMachine vendingMachine;

    vendingMachine.insertMoney(10); // Inserting money while in idle state
    vendingMachine.selectProduct(1); // Selecting product while in idle state
    vendingMachine.dispenseProduct(); // Dispensing product while in idle state

    vendingMachine.insertMoney(20); // Inserting money while accepting cash
    vendingMachine.selectProduct(2); // Selecting product while accepting cash
    vendingMachine.dispenseProduct(); // Dispensing product while in dispensing state

    vendingMachine.cancelTransaction(); // Cancelling transaction while in dispensing state

    return 0;
}
