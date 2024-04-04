#include <iostream>
#include <vector>
#include <string>

// Component interface
class FileSystemComponent {
public:
    virtual void ls() const = 0;
    virtual ~FileSystemComponent() {}
};

// Leaf class representing a file
class File : public FileSystemComponent {
private:
    std::string name;

public:
    File(const std::string& name) : name(name) {}

    void ls() const override {
        std::cout << name << std::endl;
    }
};

// Composite class representing a directory
class Directory : public FileSystemComponent {
private:
    std::string name;
    std::vector<FileSystemComponent*> children;

public:
    Directory(const std::string& name) : name(name) {}

    void addComponent(FileSystemComponent* component) {
        children.push_back(component);
    }

    void ls() const override {
        std::cout << "Directory: " << name << std::endl;
        for (const auto& child : children) {
            child->ls();
        }
    }

    ~Directory() {
        for (auto& child : children) {
            delete child;
        }
    }
};

int main() {
    // Create files
    File* file1 = new File("file1.txt");
    File* file2 = new File("file2.txt");
    File* file3 = new File("file3.txt");

    // Create directories
    Directory* dir1 = new Directory("Folder 1");
    Directory* dir2 = new Directory("Folder 2");

    // Populate directories
    dir1->addComponent(file1);
    dir1->addComponent(dir2);
    dir2->addComponent(file2);
    dir2->addComponent(file3);

    // List contents
    dir1->ls();

    // Clean up
    delete dir1;

    return 0;
}
