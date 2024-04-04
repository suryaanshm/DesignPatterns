#include <iostream>
#include <string>
#include <vector>

// Memento class
class ConfigurationMemento {
private:
    int height;
    int width;

public:
    ConfigurationMemento(int h, int w) : height(h), width(w) {}

    int getHeight() const { return height; }
    int getWidth() const { return width; }
};

// Originator class
class Configuration {
private:
    int height;
    int width;

public:
    Configuration(int h, int w) : height(h), width(w) {}

    // Save current state as a memento
    ConfigurationMemento* saveToMemento() {
        return new ConfigurationMemento(height, width);
    }

    // Restore state from a memento
    void restoreFromMemento(ConfigurationMemento* memento) {
        height = memento->getHeight();
        width = memento->getWidth();
    }

    void setHeight(int h) { height = h; }
    void setWidth(int w) { width = w; }
    int getHeight() const { return height; }
    int getWidth() const { return width; }

    void display() {
        std::cout << "Current Configuration: Height = " << height << ", Width = " << width << std::endl;
    }
};

// Caretaker class
class Caretaker {
private:
    std::vector<ConfigurationMemento*> history;

public:
    void saveMemento(ConfigurationMemento* mem) {
        history.push_back(mem);
    }

    ConfigurationMemento* retrieveMemento() {
        if (history.size()>0)
            return history[history.size()-1];
        else
            return nullptr; // Out of bounds index
    }
};

int main() {
    // Create configuration object
    Configuration config(100, 200);
    config.display();

    // Save current state
    Caretaker caretaker;
    caretaker.saveMemento(config.saveToMemento());

    // Modify configuration
    config.setHeight(150);
    config.setWidth(250);
    config.display();
    caretaker.saveMemento(config.saveToMemento());

    // Modify configuration
    config.setHeight(200);
    config.setWidth(300);
    config.display();

    // Restore saved state
    config.restoreFromMemento(caretaker.retrieveMemento());
    config.display();

    return 0;
}
