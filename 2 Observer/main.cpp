#include <iostream>
#include <vector>

class Subject;

// Observer class
class Observer {
protected:
    Subject* mySubject;
public:
    // Method called by the subject when it changes state
    Observer(Subject* obj){
        mySubject = obj;
    }
    virtual void update() = 0;
};

// Subject class
class Subject {
public:
    // Attach an observer to the subject
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    // Notify all observers of a state change
    void notify() {
        for (Observer* observer : observers) {
            observer->update();
        }
    }

    int getData(){
        return data;
    }

    void setData(int _data){
        data = _data;
    }

    // For simplicity, we're not implementing specific state management here
    // This is just to demonstrate the pattern

private:
    std::vector<Observer*> observers;
    int data;
};

// Concrete Observer 1
class ConcreteObserver1 : public Observer {
public:
    ConcreteObserver1(Subject* obj) : Observer(obj){}
    void update() override {
        std::cout << "ConcreteObserver1 has been notified of the state change.\n";
        std::cout << "Current subject state is "<<mySubject->getData()<<"\n";
    }
};

// Concrete Observer 2
class ConcreteObserver2 : public Observer {
public:
    ConcreteObserver2(Subject* obj) : Observer(obj){}
    void update() override {
        std::cout << "ConcreteObserver2 has been notified of the state change.\n";
        std::cout << "Current subject state is "<<mySubject->getData()+1<<"\n";
    }
};

int main() {
    // Create subject
    Subject* subject = new Subject;

    // Create observers
    Observer* observer1 = new ConcreteObserver1(subject);
    Observer* observer2 = new ConcreteObserver2(subject);

    // Attach observers to subject
    subject->attach(observer1);
    subject->attach(observer2);

    // Notify observers of state change
    subject->setData(42);
    subject->notify();

    delete observer1;
    delete observer2;
    delete subject;

    return 0;
}
