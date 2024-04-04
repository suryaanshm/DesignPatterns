#include <iostream>

// Abstract Payments interface
class Payments {
public:
    // Template method defining the payment process
    virtual void processPayment(int amount) final {
        if (validate()) {
            debitAmount(amount);
            chargePaymentFee(amount);
            creditAmount(amount);
            std::cout << "Payment successful!" << std::endl;
        } else {
            std::cout << "Payment failed due to validation error." << std::endl;
        }
    }

    virtual ~Payments() {}

protected:
    // Abstract methods to be implemented by subclasses
    virtual bool validate() = 0;
    virtual void debitAmount(int amount) = 0;
    virtual void creditAmount(int amount) = 0;
    virtual void chargePaymentFee(int percent) = 0;
};

// Concrete implementation for paying to contact (no payment fee)
class PayToContact : public Payments {
protected:
    bool validate() override {
        return true; // Validation always succeeds for paying to contact
    }

    void debitAmount(int amount) override {
        std::cout << "Debiting amount: $" << amount << std::endl;
    }

    void chargePaymentFee(int amount) override {
        double fee = 0.00 * amount; // 2% fee calculation
        std::cout << "Charging payment fee: $" << fee << " (0% of $" << amount << ")" << std::endl;
    }

    void creditAmount(int amount) override {
        std::cout << "Crediting amount: $" << amount << " to contact." << std::endl;
    }
};

// Concrete implementation for paying to merchant (2% payment fee)
class PayToMerchant : public Payments {
protected:
    bool validate() override {
        return true; // Validation always succeeds for paying to merchant
    }

    void debitAmount(int amount) override {
        std::cout << "Debiting amount: $" << amount << std::endl;
    }

    void chargePaymentFee(int amount) override {
        double fee = 0.02 * amount; // 2% fee calculation
        std::cout << "Charging payment fee: $" << fee << " (2% of $" << amount << ")" << std::endl;
    }

    void creditAmount(int amount) override {
        double totalAmount = amount * 0.98; // Deducting 2% fee
        std::cout << "Crediting amount: $" << totalAmount << " to merchant." << std::endl;
    }
};

int main() {
    Payments* payment1 = new PayToContact();
    Payments* payment2 = new PayToMerchant();

    // Process payments
    std::cout << "Paying to contact:" << std::endl;
    payment1->processPayment(100); // No payment fee charged

    std::cout << "\nPaying to merchant:" << std::endl;
    payment2->processPayment(100); // 2% payment fee charged

    delete payment1;
    delete payment2;

    return 0;
}
