#include <iostream>

// Forward declarations
class Square;
class Circle;

// Abstract base class for the visitor
class ShapeVisitor {
public:
    virtual void visit(Square* square) = 0;
    virtual void visit(Circle* circle) = 0;
};

// Abstract base class for shapes
class Shape {
public:
    virtual void accept(ShapeVisitor* visitor) = 0;
    virtual ~Shape(){}
};

// Concrete Square class
class Square : public Shape {
public:
    void accept(ShapeVisitor* visitor) override {
        visitor->visit(this);
    }
};

// Concrete Circle class
class Circle : public Shape {
public:
    void accept(ShapeVisitor* visitor) override {
        visitor->visit(this);
    }
};

// Concrete visitor class implementing the double dispatch logic
class AreaCalculator : public ShapeVisitor {
public:
    void visit(Square* square) override {
        std::cout << "Calculating area of square" << std::endl;
    }

    void visit(Circle* circle) override {
        std::cout << "Calculating area of circle" << std::endl;
    }
};

// Concrete visitor class implementing another operation
class DrawVisitor : public ShapeVisitor {
public:
    void visit(Square* square) override {
        std::cout << "Drawing square" << std::endl;
    }

    void visit(Circle* circle) override {
        std::cout << "Drawing circle" << std::endl;
    }
};

int main() {
    Shape* square = new Square();
    Shape* circle = new Circle();

    ShapeVisitor* areaCalculator = new AreaCalculator();
    ShapeVisitor* drawVisitor = new DrawVisitor();

    // Double dispatch happens here
    square->accept(areaCalculator); // Calls visit of AreaCalculator
    circle->accept(areaCalculator); // Calls visit of AreaCalculator

    std::cout << std::endl;

    square->accept(drawVisitor); // Calls visit of DrawVisitor
    circle->accept(drawVisitor); // Calls visit of DrawVisitor

    // Cleanup
    delete square;
    delete circle;

    return 0;
}
