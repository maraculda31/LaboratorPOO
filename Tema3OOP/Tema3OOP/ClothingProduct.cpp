#include "ClothingProduct.h"
#include <iostream>

ClothingProduct::ClothingProduct()
    : Product(), size("Undefined"), material("Undefined") {}

ClothingProduct::ClothingProduct(int id, std::string name, std::string category, double price, int quantity, std::string size, std::string material)
    : Product(id, name, category, price, quantity), size(size), material(material) {}

ClothingProduct::ClothingProduct(const ClothingProduct& other)
    : Product(other), size(other.size), material(other.material) {}

ClothingProduct::~ClothingProduct() {}

ClothingProduct& ClothingProduct::operator=(const ClothingProduct& other) {
    if (this != &other) {
        Product::operator=(other);
        size = other.size;
        material = other.material;
    }
    return *this;
}

std::istream& ClothingProduct::input(std::istream& is)
{
    Product::input(is);
    std::cout << "Enter size: ";
    is >> size;
    std::cout << "Enter material: ";
    is >> material;
    return is;
}

void ClothingProduct::print(std::ostream& os) const {
    os << "ID: " << getId() << ", Name: " << getName() << ", Category: " << getCategory()
        << ", Price: " << getPrice() << ", Quantity: " << getQuantity()
        << ", Size: " << size << ", Material: " << material;
}


void ClothingProduct::setSize(std::string newSize) {
    size = newSize;
}

void ClothingProduct::setMaterial(std::string newMaterial) {
    material = newMaterial;
}

std::istream& operator>>(std::istream& is, ClothingProduct& product) {
    is >> static_cast<Product&>(product);
    std::cout << "Enter size: ";
    std::cin >> product.size;
    std::cout << "Enter material: ";
    std::cin >> product.material;
    return is;
}
