#pragma once

#include <vector>
#include <iostream>
#include "Observer.h"
#include "CartItem.h"

class Cart: public Observer
{
private:
    std::vector<CartItem> items;

public:
    void addProduct(const std::shared_ptr<Product>& product, int quantity);
    void removeProduct(const std::shared_ptr<Product>& product);
    void updateProductQuantity(const std::shared_ptr<Product>& product, int newQuantity);
    std::string highestValueCategory() const;
    double calculateTotal() const;

    void update(int productId, int newQuantity) override;

    friend std::ostream& operator<<(std::ostream& os, const Cart& cart);
};

std::ostream& operator<<(std::ostream& os, const Cart& cart);