#include "CartItem.h"

CartItem::CartItem() : product(nullptr), quantity(0) {}

CartItem::CartItem(std::shared_ptr<Product> prod, int qty) : product(prod), quantity(qty) {}

CartItem::CartItem(const CartItem& other) : product(other.product), quantity(other.quantity) {}

CartItem& CartItem::operator=(const CartItem& other) {
    if (this != &other) {
        product = other.product;
        quantity = other.quantity;
    }
    return *this;
}

CartItem::~CartItem() {
}

void CartItem::setQuantity(int qty) {
    quantity = qty;
}

int CartItem::getQuantity() const {
    return quantity;
}

const Product& CartItem::getProduct() const {
    return *product;
}

void CartItem::incrementQuantity(int qty)
{
    this->quantity += qty;
}

std::ostream& operator<<(std::ostream& os, const CartItem& item) {
    os << *(item.product) << " - Quantity: " << item.quantity;
    return os;
}
