#include <iostream>
#include <string>

// Abstract base class representing the prototype
class StudentPrototype {
public:
    virtual ~StudentPrototype() {}
    virtual StudentPrototype* clone() const = 0;
    virtual void printInfo() const = 0;
};

// Concrete class representing a Student
class Student : public StudentPrototype {
public:
    Student(std::string name, int age, std::string major)
        : name_(std::move(name)), age_(age), major_(std::move(major)) {}

    // Copy constructor for cloning
    Student(const Student& other)
        : name_(other.name_), age_(other.age_), major_(other.major_) {}

    // Clone method to create a copy of the object
    StudentPrototype* clone() const override {
        return new Student(*this);
    }

    // Print student information
    void printInfo() const override {
        std::cout << "Name: " << name_ << ", Age: " << age_ << ", Major: " << major_ << std::endl;
    }

    // Setter method for name
    void setName(const std::string& name) {
        name_ = name;
    }

private:
    std::string name_;
    int age_;
    std::string major_;
};

int main() {
    // Create a prototype student
    StudentPrototype* prototype = new Student("John", 20, "Computer Science");

    // Clone the prototype to create new student objects
    StudentPrototype* student1 = prototype->clone();
    StudentPrototype* student2 = prototype->clone();

    // Modify the cloned students if needed
    // For example, change the name of student2
    static_cast<Student*>(student2)->printInfo(); // Before modification
    static_cast<Student*>(student2)->setName("Alice");
    static_cast<Student*>(student2)->printInfo(); // After modification

    // Don't forget to release the allocated memory
    delete prototype;
    delete student1;
    delete student2;

    return 0;
}
