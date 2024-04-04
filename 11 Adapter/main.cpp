#include <iostream>
#include <string>

// Adaptee: XML format
class XMLFormat {
public:
    void loadXML(const std::string& xml) {
        std::cout << "Loading XML: " << xml << std::endl;
        // Parsing XML and converting to JSON is not implemented for simplicity
    }
};

// Target: JSON format
class JSONFormat {
public:
    virtual void loadJSON(const std::string& json) {
        std::cout << "Loading JSON: " << json << std::endl;
    }
};

// Adapter: Converts XML to JSON
class XMLToJSONAdapter : public JSONFormat {
private:
    XMLFormat xmlFormat;

public:
    void loadJSON(const std::string& xml) override {
        std::string json = "{";
        // Convert XML to JSON using the XMLFormat object
        // In this example, we're simply loading XML, but in real implementation, this would involve conversion
        xmlFormat.loadXML(xml);
        json += xml + "}";
        // Conversion logic to convert XML to JSON
        // json = ...;
        // Once conversion is done, call the base class method to load JSON
        JSONFormat::loadJSON(json);
    }
};

int main() {
    // Create adapter object
    JSONFormat* adapter = new XMLToJSONAdapter();

    // Load XML (which will be converted to JSON)
    adapter->loadJSON("<data><name>John</name><age>30</age></data>");

    return 0;
}
