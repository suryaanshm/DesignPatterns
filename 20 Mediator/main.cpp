#include <iostream>
#include <vector>
#include <string>

// Forward declaration of Mediator class
class Mediator;

// Bidder interface
class Bidder {
protected:
    Mediator* mediator;
public:
    std::string name;
    Bidder(const std::string& n, Mediator* m) : name(n), mediator(m) {}
    virtual void placeBid(int amount) = 0;
    virtual void receiveNotification(const std::string& bidder, int amount) = 0;
};

// Mediator interface
class Mediator {
private:
    void notify(Bidder* bidder, int amount) {
        for (Bidder* b : bidders) {
            if (b != bidder) {
                b->receiveNotification(bidder->name, amount);
            }
        }
    }
    std::vector<Bidder*> bidders;
public:
    void registerBidder(Bidder* bidder) {
        bidders.push_back(bidder);
    }
    void placeBid(Bidder* bidder, int amount) {
        notify(bidder, amount);
    }
};

// Concrete Bidder classes
class RetailBidder : public Bidder {
public:
    RetailBidder(const std::string& n, Mediator* m) : Bidder(n, m) {
        m->registerBidder(this);
    }
    void placeBid(int amount) override {
        std::cout << name << " places a bid of $" << amount << std::endl;
        mediator->placeBid(this, amount);
    }
    void receiveNotification(const std::string& bidder, int amount) override {
        std::cout << name << " receives notification: Bid of $" << amount << " placed by " << bidder << std::endl;
    }
};

class CorporateBidder : public Bidder {
public:
    CorporateBidder(const std::string& n, Mediator* m) : Bidder(n, m) { 
        m->registerBidder(this);
    }
    void placeBid(int amount) override {
        std::cout << name << " places a bid of $" << amount << std::endl;
        mediator->placeBid(this, amount);
    }
    void receiveNotification(const std::string& bidder, int amount) override {
        std::cout << name << " receives notification: Bid of $" << amount << " placed by " << bidder << std::endl;
    }
};

int main() {
    Mediator auctionManager;

    // Create bidders and register them with the auction manager
    RetailBidder retailBidder1("Retail Bidder 1", &auctionManager);
    CorporateBidder corporateBidder1("Corporate Bidder 1", &auctionManager);
    CorporateBidder corporateBidder2("Corporate Bidder 2", &auctionManager);

    // Retail bidder places a bid
    retailBidder1.placeBid(100);

    std::cout << std::endl;

    // Corporate bidder places a bid
    corporateBidder1.placeBid(200);

    return 0;
}
