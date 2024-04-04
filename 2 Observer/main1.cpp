#include <iostream>
#include <vector>

class StockObservable;

class Observer{
    protected:
        StockObservable* stockObservableObj;
    public:
        Observer(StockObservable* obj) : stockObservableObj{obj}{};
        virtual void update() = 0;
};

class StockObservable{
    private:
        int data;
        std::vector<Observer*> ObserverList;
    public:
        void addObserver(Observer* obj){
            ObserverList.push_back(obj);
        }
        void removeObserver(Observer* obj){
            std::vector<Observer*> newObserverList;
            for(auto obs:ObserverList){
                if(obs!=obj)
                    newObserverList.push_back(obs);
            }
            ObserverList = newObserverList;
        }
        void notify(){
            for(auto obs : ObserverList){
                obs->update();
            }
        }
        int getData(){
            return data;
        }
        void setData(int stockPrice){
            data = stockPrice;
        }
};

class Trader : public Observer{
    public:
        Trader(StockObservable* obj) : Observer{obj}{};
        void update() override{
            std::cout<<"Trader View : Stock Data is now "<<stockObservableObj->getData()<<"\n";
        }
};

class Investor : public Observer{
    public:
        Investor(StockObservable* obj) : Observer{obj}{};
        void update() override{
            std::cout<<"Investor View : Stock Data is now "<<stockObservableObj->getData()<<"\n";
        }
};

int main(){
    StockObservable* google = new StockObservable();
    Trader* t1 = new Trader(google);
    Investor* i1 = new Investor(google);
    google->addObserver(t1);
    google->addObserver(i1);
    google->setData(42);
    google->notify();
    google->removeObserver(i1);
    google->setData(45);
    google->notify();
}