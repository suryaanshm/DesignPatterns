#include <iostream>
#include <string>
#include <vector>

// Product: Student
class Student {
private:
    int rollNumber;
    std::string name;
    std::string branch;
    std::vector<std::string> subjects;
    std::string fatherName;
    std::string motherName;

public:
    // Constructor is private to force object creation via Builder
    Student() {}

    // Setters
    void setRollNumber(int roll) { rollNumber = roll; }
    void setName(const std::string& n) { name = n; }
    void setBranch(const std::string& b) { branch = b; }
    void addSubject(const std::string& subject) { subjects.push_back(subject); }
    void setFatherName(const std::string& fName) { fatherName = fName; }
    void setMotherName(const std::string& mName) { motherName = mName; }

    // Display student details
    void display() const {
        std::cout << "Roll Number: " << rollNumber << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Branch: " << branch << std::endl;
        std::cout << "Subjects: ";
        for (const auto& subject : subjects) {
            std::cout << subject << ", ";
        }
        std::cout << std::endl;
        std::cout << "Father's Name: " << fatherName << std::endl;
        std::cout << "Mother's Name: " << motherName << std::endl;
    }
};

// Builder: StudentBuilder
class StudentBuilder {
protected:
    Student student;

public:
    virtual ~StudentBuilder() {}

    void setRollNumber(int roll) { student.setRollNumber(roll); }
    void setName(const std::string& n) { student.setName(n); }
    void setBranch(const std::string& b) { student.setBranch(b); }
    void setFatherName(const std::string& fName) { student.setFatherName(fName); }
    void setMotherName(const std::string& mName) { student.setMotherName(mName); }

    virtual Student build() = 0;
};

// Concrete Builder: EngineeringStudentBuilder
class EngineeringStudentBuilder : public StudentBuilder {
public:
    Student build() override {
        // Hardcoded subjects for engineering students
        student.addSubject("Math");
        student.addSubject("Physics");
        student.addSubject("Chemistry");
        return student;
    }
};

// Concrete Builder: MBAStudentBuilder
class MBAStudentBuilder : public StudentBuilder {
public:
    Student build() override {
        // Hardcoded subjects for MBA students
        student.addSubject("Marketing");
        student.addSubject("Finance");
        student.addSubject("Management");
        return student;
    }
};

// Director: StudentDirector
class StudentDirector {
private:
    StudentBuilder* builder;

public:
    StudentDirector(StudentBuilder* b) : builder(b) {}

    Student construct(int roll, const std::string& name, const std::string& branch,
                      const std::string& fatherName, const std::string& motherName) {
        builder->setRollNumber(roll);
        builder->setName(name);
        builder->setBranch(branch);
        builder->setFatherName(fatherName);
        builder->setMotherName(motherName);

        return builder->build();
    }
};

// int main() {
//     // Create a EngineeringStudentBuilder
//     EngineeringStudentBuilder engStudentBuilder;

//     // Create a StudentDirector with the EngineeringStudentBuilder
//     StudentDirector engDirector(&engStudentBuilder);

//     // Construct an Engineering student
//     Student engStudent = engDirector.construct(101, "John Doe", "Engineering",
//                                           "John's Father", "John's Mother");

//     // Display Engineering student details
//     std::cout << "Engineering Student Details:" << std::endl;
//     engStudent.display();
//     std::cout << std::endl;

//     // Create a MBAStudentBuilder
//     MBAStudentBuilder mbaStudentBuilder;

//     // Create a StudentDirector with the MBAStudentBuilder
//     StudentDirector mbaDirector(&mbaStudentBuilder);

//     // Construct an MBA student
//     Student mbaStudent = mbaDirector.construct(102, "Jane Doe", "MBA",
//                                           "Jane's Father", "Jane's Mother");

//     // Display MBA student details
//     std::cout << "MBA Student Details:" << std::endl;
//     mbaStudent.display();

//     return 0;
// }

int main() {
    // Engineering student creation without director
    EngineeringStudentBuilder engStudentBuilder;
    engStudentBuilder.setRollNumber(101);
    engStudentBuilder.setName("John Doe");
    engStudentBuilder.setBranch("Engineering");
    engStudentBuilder.setFatherName("John's Father");
    engStudentBuilder.setMotherName("John's Mother");

    // Construct an Engineering student
    Student engStudent = engStudentBuilder.build();

    // Display Engineering student details
    std::cout << "Engineering Student Details:" << std::endl;
    engStudent.display();
    std::cout << std::endl;

    // MBA student creation without director
    MBAStudentBuilder mbaStudentBuilder;
    mbaStudentBuilder.setRollNumber(102);
    mbaStudentBuilder.setName("Jane Doe");
    mbaStudentBuilder.setBranch("MBA");
    mbaStudentBuilder.setFatherName("Jane's Father");
    mbaStudentBuilder.setMotherName("Jane's Mother");

    // Construct an MBA student
    Student mbaStudent = mbaStudentBuilder.build();

    // Display MBA student details
    std::cout << "MBA Student Details:" << std::endl;
    mbaStudent.display();

    return 0;
}

