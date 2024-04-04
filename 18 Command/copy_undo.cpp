#include <iostream>
#include <string>
#include <stack>

// Receiver: Text Editor
class TextEditor {
public:
    void copy(const std::string& text) {
        clipboard_ = text;
        std::cout << "Copied: " << clipboard_ << std::endl;
    }

    void paste() {
        std::cout << "Pasted: " << clipboard_ << std::endl;
    }

    void setText(const std::string& text) {
        text_ = text;
    }

    std::string getText() const {
        return text_;
    }

    void setClipboard(const std::string& text) {
        clipboard_ = text;
    }

    std::string getClipboard() const {
        return clipboard_;
    }

private:
    std::string text_;
    std::string clipboard_;
};

// Command interface
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// Concrete command to copy text
class CopyCommand : public Command {
public:
    CopyCommand(TextEditor* textEditor, const std::string& text) : textEditor_(textEditor), text_(text) {}

    void execute() override {
        if (textEditor_) {
            // Save the previous clipboard state before copy
            prevClipboard_ = textEditor_->getClipboard();
            textEditor_->copy(text_);
        }
    }

    void undo() override {
        if (textEditor_) {
            // Revert clipboard state to previous state
            textEditor_->setClipboard(prevClipboard_);
            std::cout << "Undo Copy: Clipboard content reverted to previous state." << std::endl;
        }
    }

private:
    TextEditor* textEditor_;
    std::string text_;
    std::string prevClipboard_;
};

// Concrete command to paste text
class PasteCommand : public Command {
public:
    PasteCommand(TextEditor* textEditor) : textEditor_(textEditor) {}

    void execute() override {
        if (textEditor_) {
            // Save the previous editor state before paste
            prevText_ = textEditor_->getText();
            textEditor_->paste();
        }
    }

    void undo() override {
        if (textEditor_) {
            // Revert editor state to previous state
            textEditor_->setText(prevText_);
            std::cout << "Undo Paste: Text editor content reverted to previous state." << std::endl;
        }
    }

private:
    TextEditor* textEditor_;
    std::string prevText_;
};

// Command Manager (Invoker)
class CommandManager {
public:
    void execute(Command* command) {
        if (command) {
            command->execute();
            undoStack.push(command);
            redoStack = std::stack<Command*>(); // Clear redo stack after executing a new command
        }
    }

    void undo() {
        if (!undoStack.empty()) {
            Command* command = undoStack.top();
            undoStack.pop();
            command->undo();
            redoStack.push(command);
        } else {
            std::cout << "Nothing to undo." << std::endl;
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            Command* command = redoStack.top();
            redoStack.pop();
            execute(command); // Re-execute the command
        } else {
            std::cout << "Nothing to redo." << std::endl;
        }
    }

private:
    std::stack<Command*> undoStack;
    std::stack<Command*> redoStack;
};

int main() {
    // Create an instance of Text Editor
    TextEditor textEditor;

    // Create an instance of Command Manager
    CommandManager manager;

    // Copy "Hello, world!" to clipboard
    Command* copyCommand = new CopyCommand(&textEditor, "Hello, world!");
    manager.execute(copyCommand);

    // Paste text from clipboard
    Command* pasteCommand = new PasteCommand(&textEditor);
    manager.execute(pasteCommand);
    
    // Undo the last command (Paste)
    manager.undo();

    // Redo the undone command (Paste)
    manager.redo();
    
    // Cleanup
    delete copyCommand;
    delete pasteCommand;

    return 0;
}
