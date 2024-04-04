#include <iostream>
#include <string>

// Subject interface
class FileAccess {
public:
    virtual std::string readData() const = 0;
    virtual void writeData(const std::string& data) = 0;
};

// RealSubject: Implementation of FileAccess interface
class RealFileAccess : public FileAccess {
private:
    std::string fileName;

public:
    RealFileAccess(const std::string& fileName) : fileName(fileName) {}

    std::string readData() const override {
        // Read data from the file
        std::cout << "Reading data from file: " << fileName << std::endl;
        return "Data read from file";
    }

    void writeData(const std::string& data) override {
        // Write data to the file
        std::cout << "Writing data to file: " << fileName << std::endl;
    }
};

// Proxy: Controls access to the RealSubject
class FileAccessProxy : public FileAccess {
private:
    RealFileAccess* realFileAccess;
    std::string username;
    std::string password;

public:
    FileAccessProxy(const std::string& fileName, const std::string& username, const std::string& password)
        : realFileAccess(new RealFileAccess(fileName)), username(username), password(password) {}

    ~FileAccessProxy() {
        delete realFileAccess;
    }

    std::string readData() const override {
        // Check access credentials before allowing read operation
        if (authenticate()) {
            return realFileAccess->readData();
        } else {
            return "Access denied!";
        }
    }

    void writeData(const std::string& data) override {
        // Check access credentials before allowing write operation
        if (authenticate()) {
            realFileAccess->writeData(data);
        } else {
            std::cout << "Access denied!" << std::endl;
        }
    }

private:
    bool authenticate() const {
        // Simulate authentication process (e.g., check username and password)
        // For simplicity, just check if username and password are not empty
        return !username.empty() && !password.empty();
    }
};

int main() {
    // Create a file access proxy
    FileAccess* fileAccess = new FileAccessProxy("example.txt", "user123", "password123");

    // Try to read data
    std::string data = fileAccess->readData();
    std::cout << "Read data: " << data << std::endl;

    // Try to write data
    fileAccess->writeData("New data");

    delete fileAccess;
    return 0;
}
