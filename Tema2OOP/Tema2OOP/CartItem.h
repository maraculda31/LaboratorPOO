#pragma once

#include "Product.h"
#include <memory>
#include <iostream>

class CartItem {
private:
    std::shared_ptr<Product> product;
    int quantity;

public:
    CartItem();
    CartItem(std::shared_ptr<Product> prod, int qty);
    CartItem(const CartItem& other);
    CartItem& operator=(const CartItem& other);
    ~CartItem();
    void setQuantity(int qty);
    int getQuantity() const;
    const Product& getProduct() const;
    void incrementQuantity(int qty);


    friend std::ostream& operator<<(std::ostream& os, const CartItem& item);
};
