#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "ClothingProduct.h"
#include "ElectronicProduct.h"
#include "ProductExceptions.h"
#include "Cart.h"

static void readProductsFromFile(const std::string& filename, std::vector<std::shared_ptr<Product>>& products) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if(line.empty()) continue;

        std::istringstream iss(line);
        std::string type;
        getline(iss, type, ',');

        if (type == "Electronics") {
            int id, warrantyPeriod;
            std::string name, category;
            double price;
            int quantity;

            iss >> id;
            iss.ignore(1, ',');
            std::getline(iss, name, ',');
            std::getline(iss, category, ',');
            iss >> price;
            iss.ignore(1, ',');
            iss >> quantity;
            iss.ignore(1, ',');
            iss >> warrantyPeriod;

            auto product = std::make_shared<ElectronicProduct>(id, name, category, price, quantity, warrantyPeriod);
            products.push_back(product);
        }
        else if (type == "Clothing") {
            int id;
            std::string name, category, size, material;
            double price;
            int quantity;

            iss >> id;
            iss.ignore(1, ',');
            std::getline(iss, name, ',');
            std::getline(iss, category, ',');
            iss >> price;
            iss.ignore(1, ',');
            iss >> quantity;
            iss.ignore(1, ',');
            std::getline(iss, size, ',');
            std::getline(iss, material);

            auto product = std::make_shared<ClothingProduct>(id, name, category, price, quantity, size, material);
            products.push_back(product);
        }
    }
    file.close();
}

int main() {
    Cart cart;
    std::vector<std::shared_ptr<Product>> products;
    int choice;

    do {
        try {
            std::cout << "1. Add an electronic product\n";
            std::cout << "2. Add a clothing product\n";
            std::cout << "3. Add N products\n";
            std::cout << "4. Read products from file\n";
            std::cout << "5. Add a product to cart\n";
            std::cout << "6. Remove a product from cart\n";
            std::cout << "7. Update product quantity in cart\n";
            std::cout << "8. Display cart contents\n";
            std::cout << "9. Show category with highest value\n";
            std::cout << "10. Show all products\n";
            std::cout << "11. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
            case 1: {
                std::shared_ptr<Product> product = std::make_shared<ElectronicProduct>();
                product->input(std::cin);
                products.push_back(product);
                break;
            }
            case 2: {
                std::shared_ptr<Product> product = std::make_shared<ClothingProduct>();
                product->input(std::cin);
                products.push_back(product);
                break;
            }
            case 3: {
                int n;
                std::cout << "Enter number of products to add: ";
                std::cin >> n;
                std::cin.ignore();
                for (int i = 0; i < n; ++i) {
                    std::cout << "Enter product type (1 for Electronic, 2 for Clothing): ";
                    int type;
                    std::cin >> type;
                    std::shared_ptr<Product> product;
                    if (type == 1) {
					    product = std::make_shared<ElectronicProduct>();
				    }
                    else if (type == 2) {
					    product = std::make_shared<ClothingProduct>();
				    }
                    product->input(std::cin);
				    products.push_back(product);
                }
                break;
            }
            case 4: {
                readProductsFromFile("tastatura.txt", products);
                break;
            }
            case 5: {
                int id, quantity;
                std::cout << "Enter product ID: ";
                std::cin >> id;
                std::cout << "Enter quantity: ";
                std::cin >> quantity;

                auto it = std::find_if(products.begin(), products.end(),
                    [&id](const std::shared_ptr<Product>& product) {
                    return product->getId() == id;
                });

                if (it != products.end()) {
                    cart.addProduct(*it, quantity);
                    std::cout << "Product added to cart.\n";
                }
                else {
                    throw ProductNotFoundException();
                }
                break;
            }
            case 6: {
                int id;
				std::cout << "Enter product ID: ";
				std::cin >> id;

				auto it = std::find_if(products.begin(), products.end(),
                    [&id](const std::shared_ptr<Product>& product) {
					return product->getId() == id;
				});

                if (it != products.end()) {
					cart.removeProduct(*it);
					std::cout << "Product removed from cart.\n";
				}
                else {
					throw ProductNotFoundException();
				}
				break;
            }
            case 7: {
				int id, quantity;
                std::cout << "Enter product ID: ";
                std::cin >> id;
                std::cout << "Enter new quantity: ";
                std::cin >> quantity;

                auto it = std::find_if(products.begin(), products.end(),
                    [&id](const std::shared_ptr<Product>& product) {
					return product->getId() == id;
				});

                if (it != products.end()) {
                    cart.updateProductQuantity(*it, quantity);
                    std::cout << "Product quantity updated.\n";
                }
                else {
					throw ProductNotFoundException();
				}
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
                for (std::shared_ptr<Product> p : products) {
				    p->print(std::cout);
				    std::cout << '\n';
			    }
			    break;
            }
            case 11:
                std::cout << "Exiting program...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        } catch (const ProductNotFoundException& e) {
            std::cerr << "Error: " << e.what() << '\n';
        } catch (const std::exception& e) {
            std::cerr << "An unexpected error occurred: " << e.what() << '\n';
        }
    } while (choice != 11);

    return 0;
}