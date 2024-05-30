#pragma once

#include <iostream>
#include <string>

class Product {
private:
    static int count;
    int id;
    std::string name;
    std::string category;
    double price;
    int quantity;

public:
    Product();
    Product(int id, std::string name, std::string category, double price, int quantity);
    Product(const Product& other);
    virtual ~Product();
    virtual std::istream& input(std::istream& is);
    virtual void print(std::ostream& os) const = 0;
    Product& operator=(const Product& other);
    friend std::ostream& operator<<(std::ostream& os, const Product& product);
    friend std::istream& operator>>(std::istream& is, Product& product);
    bool operator==(const Product& other) const;
    void updateQuantity(int newQuantity);
    bool isAvailable() const;
    double getPrice() const;
    std::string getCategory() const;
    int getQuantity() const;
    int getId() const;
    std::string getName() const;
    void setPrice(double newPrice);
    void setCategory(std::string newCategory);
    void setQuantity(int newQuantity);
    void setName(std::string newName);
    void setId(int newId);
    void decrementQuantity(int qty);
    void incrementQuantity(int qty);
    void addQuantity(int qty);
    void removeQuantity(int qty);
    static int getProductCount();
};