#include <iostream>
#include <vector>
#include <stack>
#include <string>

// Forward declaration of Book class
class Book;

// Iterator interface
class Iterator {
public:
    virtual bool hasNext() const = 0;
    virtual Book* next() = 0;
    virtual ~Iterator() {}
};

// Aggregator interface
class Aggregator {
public:
    virtual Iterator* createIterator() = 0;
    virtual ~Aggregator() {}
};

// Concrete Book class
class Book {
private:
    std::string title;
public:
    Book(const std::string& t) : title(t) {}
    std::string getTitle() const {
        return title;
    }
};

// Shelf class implementing Aggregator
class Shelf : public Aggregator {
private:
    std::vector<Book*> books;
public:
    void addBook(Book* book) {
        books.push_back(book);
    }
    Iterator* createIterator() override;
    friend class ShelfIterator;
};

// ShelfIterator class implementing Iterator
class ShelfIterator : public Iterator {
private:
    Shelf* shelf;
    size_t index;
public:
    ShelfIterator(Shelf* s) : shelf(s), index(0) {}
    bool hasNext() const override {
        return index < shelf->books.size();
    }
    Book* next() override {
        if (!hasNext())
            return nullptr;
        return shelf->books[index++];
    }
};

// Stack class implementing Aggregator
class Stack : public Aggregator {
private:
    std::stack<Book*> books;
public:
    void pushBook(Book* book) {
        books.push(book);
    }
    Iterator* createIterator() override;
    friend class StackIterator;
};

// StackIterator class implementing Iterator
class StackIterator : public Iterator {
private:
    Stack* stack;
public:
    StackIterator(Stack* s) : stack(s) {}
    bool hasNext() const override {
        return !stack->books.empty();
    }
    Book* next() override {
        if (!hasNext())
            return nullptr;
        Book* top = stack->books.top();
        stack->books.pop();
        return top;
    }
};

// Implement createIterator() methods for Shelf and Stack
Iterator* Shelf::createIterator() {
    return new ShelfIterator(this);
}

Iterator* Stack::createIterator() {
    return new StackIterator(this);
}

int main() {
    // Create some books
    Book book1("Book 1");
    Book book2("Book 2");
    Book book3("Book 3");

    // Create a shelf and add books
    Shelf shelf;
    shelf.addBook(&book1);
    shelf.addBook(&book2);
    shelf.addBook(&book3);

    // Create a stack and push books
    Stack stack;
    stack.pushBook(&book1);
    stack.pushBook(&book2);
    stack.pushBook(&book3);

    // Iterate over shelf
    Iterator* shelfIterator = shelf.createIterator();
    std::cout << "Books on shelf:" << std::endl;
    while (shelfIterator->hasNext()) {
        Book* book = shelfIterator->next();
        std::cout << book->getTitle() << std::endl;
    }
    delete shelfIterator;

    // Iterate over stack
    Iterator* stackIterator = stack.createIterator();
    std::cout << "\nBooks on stack:" << std::endl;
    while (stackIterator->hasNext()) {
        Book* book = stackIterator->next();
        std::cout << book->getTitle() << std::endl;
    }
    delete stackIterator;

    return 0;
}
