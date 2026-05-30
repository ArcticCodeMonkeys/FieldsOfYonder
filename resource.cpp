

#include "string"

class Resource
{
public:
    Resource(const std::string& name, int quantity = 0)
        : name(name), quantity(quantity) {}
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    void setQuantity(int q) { quantity = q; }
private:
    std::string name;
    int quantity;
};