#include <iostream>
#include <string>

class Handler {
public:
    Handler(Handler* successor = nullptr) : successor(successor) {}

    // make Handler an abstract class
    virtual void handleRequest(const std::string& request) = 0;

    virtual ~Handler() {}

private:
    Handler* successor;
};

void Handler::handleRequest(const std::string& request)
{
    if (successor) {
        successor->handleRequest(request);
    }
    else {
        std::cout << "No handler for the input." << std::endl;
    }
}

class ConcreteHandlerA : public Handler {
public:
    ConcreteHandlerA(Handler* successor = nullptr) : Handler(successor){};
    void handleRequest(const std::string& request) override {
        if (request == "A") {
            std::cout << "ConcreteHandlerA handles the request 'A'." << std::endl;
        } else {
            Handler::handleRequest(request);
        }
    }
};

class ConcreteHandlerB : public Handler {
public:
    ConcreteHandlerB(Handler* successor = nullptr) : Handler(successor){};
    void handleRequest(const std::string& request) override {
        if (request == "B") {
            std::cout << "ConcreteHandlerB handles the request 'B'." << std::endl;
        } else {
            Handler::handleRequest(request);
        }
    }
};

class ConcreteHandlerC : public Handler {
public:
    ConcreteHandlerC(Handler* successor = nullptr) : Handler(successor){};
    void handleRequest(const std::string& request) override {
        if (request == "C") {
            std::cout << "ConcreteHandlerC handles the request 'C'." << std::endl;
        } else {
            Handler::handleRequest(request);
        }
    }
};

class Client {
public:
    void makeRequest(Handler* handler, const std::string& request) {
        handler->handleRequest(request);
    }
};

int main() {
    Handler* handler = new ConcreteHandlerA(new ConcreteHandlerB(new ConcreteHandlerC));
    Client client;

    client.makeRequest(handler, "A");
    client.makeRequest(handler, "B");
    client.makeRequest(handler, "C");
    client.makeRequest(handler, "D");
    return 0;
}
