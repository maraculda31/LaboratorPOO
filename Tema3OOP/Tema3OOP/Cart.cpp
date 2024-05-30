#include "Cart.h"
#include <map>
#include <algorithm>

void Cart::addProduct(const std::shared_ptr<Product>& product, int quantity) {
    auto it = std::find_if(items.begin(), items.end(), [&product](const CartItem& item) {
        return item.getProduct().getId() == product->getId();
    });
    if (it != items.end()) {
        it->incrementQuantity(quantity);
    }
    else {
        items.emplace_back(product, quantity);
    }
}

void Cart::removeProduct(const std::shared_ptr<Product>& product) {
    items.erase(std::remove_if(items.begin(), items.end(), [&product](const CartItem& item) {
        return item.getProduct().getId() == product->getId();
    }), items.end());
}

void Cart::updateProductQuantity(const std::shared_ptr<Product>& product, int newQuantity) {
    auto it = std::find_if(items.begin(), items.end(), [&product](const CartItem& item) {
        return item.getProduct().getId() == product->getId();
    });
    if (it != items.end()) {
        it->setQuantity(newQuantity);
    }
}

double Cart::calculateTotal() const {
    double total = 0.0;
    for (const auto& item : items) {
        total += item.getProduct().getPrice() * item.getQuantity();
    }
    return total;
}

void Cart::update(int productId, int newQuantity)
{
    auto it = std::find_if(items.begin(), items.end(), [productId](const CartItem& item) {
		return item.getProduct().getId() == productId;
	});
	if (it != items.end()) {
		it->setQuantity(newQuantity);
	}
}

std::ostream& operator<<(std::ostream& os, const Cart& cart) {
    os << "Cart Contents:\n";
    for (const auto& item : cart.items) {
        os << item << "\n";
    }
    os << "Total Price: $" << cart.calculateTotal() << std::endl;
    return os;
}


std::string Cart::highestValueCategory() const {
    std::map<std::string, double> categoryTotals;

    for (const auto& item : items) {
        categoryTotals[item.getProduct().getCategory()] += item.getProduct().getPrice() * item.getQuantity();
    }

    std::string topCategory = "";
    double maxTotal = 0.0;

    for (const auto& category : categoryTotals) {
        if (category.second > maxTotal) {
            maxTotal = category.second;
            topCategory = category.first;
        }
    }

    return topCategory;
}