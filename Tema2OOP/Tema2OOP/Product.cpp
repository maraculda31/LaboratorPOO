#include "Product.h"
#include <iostream>
#include <string>

int Product::count = 0;

Product::Product() : id(0), name(""), category(""), price(0.0), quantity(0) {
    count++;
}

Product::Product(int id, std::string name, std::string category, double price, int quantity)
    : id(id), name(name), category(category), price(price), quantity(quantity) {
    count++;
}

Product::Product(const Product& other)
    : id(other.id), name(other.name), category(other.category), price(other.price), quantity(other.quantity) {
    count++;
}

Product::~Product() {
    count--;
}

std::istream& Product::input(std::istream& is)
{
    std::cout << "Enter product ID: ";
    is >> id;
    std::cout << "Enter product name: ";
    is.ignore();
    std::getline(is, name);
    std::cout << "Enter product category: ";
    std::getline(is, category);
    std::cout << "Enter product price: ";
    is >> price;
    std::cout << "Enter product quantity: ";
    is >> quantity;
    return is;
}

int Product::getProductCount() {
    return count;
}

Product& Product::operator=(const Product& other) {
    if (this != &other) {
        id = other.id;
        name = other.name;
        category = other.category;
        price = other.price;
        quantity = other.quantity;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Product& product) {
    os << "ID: " << product.id << ", Name: " << product.name << ", Category: " << product.category
        << ", Price: " << product.price << ", Quantity: " << product.quantity;
    return os;
}

std::istream& operator>>(std::istream& is, Product& product) {
    std::cout << "Enter product ID: ";
    is >> product.id;
    std::cout << "Enter product name: ";
    is.ignore();
    std::getline(is, product.name);
    std::cout << "Enter product category: ";
    std::getline(is, product.category);
    std::cout << "Enter product price: ";
    is >> product.price;
    std::cout << "Enter product quantity: ";
    is >> product.quantity;
    return is;
}

bool Product::operator==(const Product& other) const {
    return id == other.id;
}

void Product::updateQuantity(int newQuantity) {
    quantity = newQuantity;
}

bool Product::isAvailable() const {
    return quantity > 0;
}

double Product::getPrice() const {
    return price;
}

std::string Product::getCategory() const {
    return category;
}

int Product::getQuantity() const {
	return quantity;
}

int Product::getId() const {
	return id;
}

std::string Product::getName() const {
	return name;
}

void Product::setPrice(double newPrice) {
	price = newPrice;
}

void Product::setCategory(std::string newCategory) {
	category = newCategory;
}

void Product::setQuantity(int newQuantity) {
	quantity = newQuantity;
}

void Product::setName(std::string newName) {
	name = newName;
}

void Product::setId(int newId) {
	id = newId;
}

void Product::decrementQuantity(int qty) {
	if (quantity > qty) quantity -= qty;
	else quantity = 0;
}

void Product::incrementQuantity(int qty) {
	quantity += qty;
}

void Product::addQuantity(int qty) {
	quantity += qty;
}

void Product::removeQuantity(int qty) {
	if (quantity > qty) quantity -= qty;
	else quantity = 0;
}