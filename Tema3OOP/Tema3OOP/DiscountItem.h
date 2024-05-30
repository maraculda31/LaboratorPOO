#pragma once

#include "Product.h"

template <typename T>
class DiscountedItem {
public:
    T item;
    double discountRate;

    DiscountedItem(T i, double rate) : item(i), discountRate(rate) {}

    double getPriceAfterDiscount() {
        return item->getPrice() * (1 - discountRate);
    }

    void print(std::ostream& os) {
        item->print(os);
        os << " - Discounted Price: $" << getPriceAfterDiscount() << std::endl;
    }
};
