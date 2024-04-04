#include <iostream>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

class Logger{
private:
    static int ctr;
    static Logger* instance;
    static mutex mtx;
    Logger(){
        cout<<"New Logger Instance created. Total instance count is: "<< ++ctr<< endl;
    }
public:
    static Logger* getInstance(){
        if(instance==nullptr){
            mtx.lock();
            if(instance==nullptr) {
                instance = new Logger();
            }
            mtx.unlock();
        }
        return instance;
    }
    void log(string msg){
        cout<<msg<<endl;
    }
    Logger(const Logger&) = delete;
    Logger operator=(const Logger&) = delete;
};

int Logger::ctr = 0;
Logger* Logger::instance = nullptr;
mutex Logger::mtx;

void logFromUser1(){
    Logger* logger1 = Logger::getInstance();
    logger1->log("Message from user 1.");
}

void logFromUser2(){
    Logger* logger2 = Logger::getInstance();
    logger2->log("Message from user 2.");
}

int main(){
    thread t1(logFromUser1);   
    thread t2(logFromUser2);

    t1.join();   
    t2.join();   

    return 0;
}


// 1) Make constructor private
// 2) Create static instance member and getInstance method
// 3) Get instance checks if instance is a nullptr then creates, else simply returns the reference to the instance
// 4) Make thread safe, introduce mutex
// 5) Avoid unneccesary mutex locking if instance not null - double checked locking
// 6) Delete copy constructor and assignment operator