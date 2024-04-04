#include <iostream>
#include <string>
#include <unordered_map>

// Receiver: Air Conditioner (AC)
class AC {
public:
    void turnOn() {
        std::cout << "AC is turned on." << std::endl;
    }

    void turnOff() {
        std::cout << "AC is turned off." << std::endl;
    }

    void setTemp(int temp) {
        std::cout << "AC temperature set to " << temp << " degrees Celsius." << std::endl;
    }
};

// Command interface
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

// Concrete command to turn on the AC
class TurnOnCommand : public Command {
public:
    TurnOnCommand(AC* ac) : ac_(ac) {}

    void execute() override {
        if (ac_)
            ac_->turnOn();
    }

private:
    AC* ac_;
};

// Concrete command to turn off the AC
class TurnOffCommand : public Command {
public:
    TurnOffCommand(AC* ac) : ac_(ac) {}

    void execute() override {
        if (ac_)
            ac_->turnOff();
    }

private:
    AC* ac_;
};

// Concrete command to set temperature of the AC
class SetTempCommand : public Command {
public:
    SetTempCommand(AC* ac, int temp) : ac_(ac), temp_(temp) {}

    void execute() override {
        if (ac_)
            ac_->setTemp(temp_);
    }

private:
    AC* ac_;
    int temp_;
};

// // Invoker: Remote control
// class Remote {
// public:
//     Remote() : ac_(nullptr), command_(nullptr) {}

//     void setAC(AC* ac) {
//         ac_ = ac;
//     }

//     void setCommand(Command* command) {
//         command_ = command;
//     }

//     void pressButton() {
//         if (ac_ && command_) {
//             command_->execute();
//         } else {
//             std::cout << "Remote is not properly configured." << std::endl;
//         }
//     }

// private:
//     AC* ac_;
//     Command* command_;
// };

// int main() {
//     // Create an instance of Air Conditioner (AC)
//     AC* ac = new AC();

//     // Create commands
//     Command* turnOn = new TurnOnCommand(ac);
//     Command* turnOff = new TurnOffCommand(ac);
//     Command* setTemp = new SetTempCommand(ac, 25);

//     // Create an instance of Remote
//     Remote remote;

//     // Configure the remote with the AC
//     remote.setAC(ac);

//     // Press different buttons on the remote
//     remote.setCommand(turnOn);
//     remote.pressButton();

//     remote.setCommand(setTemp);
//     remote.pressButton();

//     remote.setCommand(turnOff);
//     remote.pressButton();

//     // Cleanup
//     delete turnOn;
//     delete turnOff;
//     delete setTemp;
//     delete ac;

//     return 0;
// }



// Invoker: Remote control
class Remote {
public:
    Remote(AC* ac) : ac_(ac) {}

    void addCommand(const std::string& name, Command* command) {
        commands_[name] = command;
    }

    void pressButton(const std::string& name) {
        auto it = commands_.find(name);
        if (it != commands_.end()) {
            it->second->execute();
        } else {
            std::cout << "Command not found." << std::endl;
        }
    }

private:
    AC* ac_;
    std::unordered_map<std::string, Command*> commands_;
};

int main() {
    // Create an instance of Air Conditioner (AC)
    AC* ac = new AC();

    // Create an instance of Remote
    Remote remote(ac);

    // Create commands and add them to the remote with names
    remote.addCommand("TurnOn", new TurnOnCommand(ac));
    remote.addCommand("SetTemp", new SetTempCommand(ac, 25));
    remote.addCommand("TurnOff", new TurnOffCommand(ac));

    // Execute specific commands by name
    remote.pressButton("TurnOn");
    remote.pressButton("SetTemp");
    remote.pressButton("TurnOff");

    // Cleanup
    delete ac;

    return 0;
}
