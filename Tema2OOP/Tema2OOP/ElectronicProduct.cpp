#include "ElectronicProduct.h"
#include <iostream>

ElectronicProduct::ElectronicProduct()
    : Product(), warrantyPeriod(0) {}

ElectronicProduct::ElectronicProduct(int id, std::string name, std::string category, double price, int quantity, int warrantyPeriod)
    : Product(id, name, category, price, quantity), warrantyPeriod(warrantyPeriod) {}

ElectronicProduct::ElectronicProduct(const ElectronicProduct& other)
    : Product(other), warrantyPeriod(other.warrantyPeriod) {}

ElectronicProduct::~ElectronicProduct() {
}

ElectronicProduct& ElectronicProduct::operator=(const ElectronicProduct& other) {
    if (this != &other) {
        Product::operator=(other);
        warrantyPeriod = other.warrantyPeriod;
    }
    return *this;
}

std::istream& ElectronicProduct::input(std::istream& is)
{
    Product::input(is);
    std::cout << "Enter warranty period (months): ";
    is >> warrantyPeriod;
    return is;
}

void ElectronicProduct::extendWarranty(int additionalMonths) {
    warrantyPeriod += additionalMonths;
}

void ElectronicProduct::print(std::ostream& os) const {
    os << "ID: " << getId() << ", Name: " << getName() << ", Category: " << getCategory()
		<< ", Price: " << getPrice() << ", Quantity: " << getQuantity()
		<< ", Warranty Period: " << warrantyPeriod;
}

std::istream& operator>>(std::istream& is, ElectronicProduct& product) {
    is >> static_cast<Product&>(product);
    std::cout << "Enter warranty period (months): ";
    is >> product.warrantyPeriod;
    return is;
}