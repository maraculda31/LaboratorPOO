#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>

class Product {
private:
    int id;
    std::string name;
    std::string category;
    double price;
    int quantity;

public:
    Product() : id(0), name(""), category(""), price(0.0), quantity(0) {}

    Product(int id, std::string name, std::string category, double price, int quantity)
        : id(id), name(name), category(category), price(price), quantity(quantity) {}

    Product(const Product& other)
        : id(other.id), name(other.name), category(other.category), price(other.price), quantity(other.quantity) {}

    ~Product() {}

    Product& operator=(const Product& other) {
        if (this != &other) {
            id = other.id;
            name = other.name;
            category = other.category;
            price = other.price;
            quantity = other.quantity;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Product& product) {
        os << "ID: " << product.id << ", Name: " << product.name << ", Category: " << product.category
            << ", Price: " << product.price << ", Quantity: " << product.quantity;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Product& product) {
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

    bool operator==(const Product& other) const {
        return id == other.id;
    }

    bool operator>(const Product& other) const {
        return this->price > other.price;
    }

    void updateQuantity(int newQuantity) {
        quantity = newQuantity;
    }

    bool isAvailable() const {
        return quantity > 0;
    }

    double getPrice() const {
        return price;
    }

    std::string getCategory() const {
        return category;
    }

    void setId(int id) {
        this->id = id;
    }

    int getId() const {
        return id;
    }

    void setName(std::string name) {
        this->name = name;
    }

    std::string getName() {
        return name;
    }

    void setCategory(std::string category) {
        this->category = category;
    }

    void setPrice(double price) {
        this->price = price;
    }

    void setQuantity(int quantity) {
        this->quantity = quantity;
    }
};

class Cart {
private:
    struct CartItem {
        Product product;
        int quantity;

        CartItem(const Product& prod, int qty) : product(prod), quantity(qty) {}
    };

    std::vector<CartItem> items;

public:
    void addProduct(const Product& product, int quantity) {
        auto it = std::find_if(items.begin(), items.end(),
            [&product](const CartItem& item) {
                return item.product == product;
            });
        if (it != items.end()) {
            it->quantity += quantity;
        }
        else {
            items.push_back(CartItem(product, quantity));
        }
    }

    void removeProduct(const Product& product) {
        items.erase(std::remove_if(items.begin(), items.end(),
            [&product](const CartItem& item) {
                return item.product == product;
            }),
            items.end());
    }

    void updateProductQuantity(const Product& product, int newQuantity) {
        auto it = std::find_if(items.begin(), items.end(),
            [&product](const CartItem& item) {
                return item.product == product;
            });
        if (it != items.end()) {
            it->quantity = newQuantity;
        }
    }

    void applyCategoryDiscount(const std::string& category, double discountPercentage) {
        for (auto& item : items) {
            if (item.product.getCategory() == category) {
                double newPrice = item.product.getPrice() * (1 - discountPercentage / 100);
                item.product.setPrice(newPrice);
            }
        }
    }

    std::string highestValueCategory() const {
        std::map<std::string, double> categoryTotals;

        for (const auto& item : items) {
            categoryTotals[item.product.getCategory()] += item.product.getPrice() * item.quantity;
        }

        std::string topCategory;
        double maxTotal = 0.0;
        for (const auto& category : categoryTotals) {
            if (category.second > maxTotal) {
                maxTotal = category.second;
                topCategory = category.first;
            }
        }

        return topCategory;
    }

    double calculateTotal() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.product.getPrice() * item.quantity;
        }
        return total;
    }

    friend std::ostream& operator<<(std::ostream& os, const Cart& cart);
    friend Cart& operator+=(Cart& cart, const Product& product);
};

Cart& operator+=(Cart& cart, const Product& product) {
    cart.addProduct(product, 1);
    return cart;
}

std::ostream& operator<<(std::ostream& os, const Cart& cart) {
    os << "Cart Contents:\n";
    for (const auto& item : cart.items) {
        os << item.product << " - Quantity: " << item.quantity << "\n";
    }
    os << "Total Price: $" << cart.calculateTotal() << std::endl;
    return os;
}

static void readProductFromFile(std::istream& is, Product& product) {
    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);

    std::string id, name, category, price, quantity;
    std::getline(iss, id, ',');
    std::getline(iss, name, ',');
    std::getline(iss, category, ',');
    std::getline(iss, price, ',');
    std::getline(iss, quantity);

    product.setId(std::stoi(id));
    product.setName(name);
    product.setCategory(category);
    product.setPrice(std::stod(price));
    product.setQuantity(std::stoi(quantity));
}

static void displayProducts(const std::vector<Product>& products) {
    for (const auto& product : products) {
        std::cout << product << std::endl;
    }
}

int main() {
    Cart cart;
    std::vector<Product> products;
    int choice, n;

    do {
        std::cout << "1. Read a product from keyboard\n";
        std::cout << "2. Read N products from keyboard\n";
        std::cout << "3. Read products from tastatura.txt\n";
        std::cout << "4. Display all products\n";
        std::cout << "5. Add a product to cart\n";
        std::cout << "6. Remove a product from cart\n";
        std::cout << "7. Update product quantity in cart\n";
        std::cout << "8. Display cart contents\n";
        std::cout << "9. Show category with highest value\n";
        std::cout << "10. Apply discount to a category\n";
        std::cout << "11. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            Product product;
            std::cin >> product;
            products.push_back(product);
            break;
        }
        case 2: {
            std::cout << "Enter number of products: ";
            std::cin >> n;
            for (int i = 0; i < n; ++i) {
                Product product;
                std::cin >> product;
                products.push_back(product);
            }
            break;
        }
        case 3: {
            std::ifstream inputFile("tastatura.txt");
            Product product;
            while (inputFile.peek() != EOF) {
                readProductFromFile(inputFile, product);
                if (inputFile) {
                    products.push_back(product);
                }
            }
            inputFile.close();
            break;
        }
        case 4: {
            displayProducts(products);
            break;
        }
        case 5: {
            int index;
            std::cout << "Enter product index to add to cart: ";
            std::cin >> index;
            if (index >= 1 && index <= static_cast<int>(products.size())) {
                
                cart.addProduct(products[index - 1], 1);
            }
            break;
        }
        case 6: {
            int index;
            std::cout << "Enter product index to remove from cart: ";
            std::cin >> index;
            if (index >= 1 && index <= static_cast<int>(products.size())) {
                
                cart.removeProduct(products[index - 1]);
            }
            break;
        }
        case 7: {
            int index, qty;
            std::cout << "Enter product index to update quantity: ";
            std::cin >> index;
            std::cout << "Enter new quantity: ";
            std::cin >> qty;
            if (index >= 1 && index <= static_cast<int>(products.size())) {

                cart.updateProductQuantity(products[index - 1], qty);
            }
            break;
        }
        case 8: {
            std::cout << cart;
            break;
        }
        case 9: {
            std::string category = cart.highestValueCategory();
            std::cout << "Category with the highest value: " << category << std::endl;
            break;
        }
        case 10: {
            std::string category;
            double discount;
            std::cout << "Enter category to apply discount: ";
            std::cin >> category;
            std::cout << "Enter discount percentage (e.g., 20 for 20%): ";
            std::cin >> discount;
            cart.applyCategoryDiscount(category, discount);
            std::cout << "Discount applied to " << category << " category.\n";
            break;
        }
        case 11: {
            std::cout << "Exiting program...\n";
            break;
        }
        default: {
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    } while (choice != 11);

    return 0;
}
