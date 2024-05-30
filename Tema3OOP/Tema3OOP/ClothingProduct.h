#pragma once

#include "Product.h"
#include <string>

class ClothingProduct : public Product {
private:
    std::string size;
    std::string material;

public:
    ClothingProduct();
    ClothingProduct(int id, std::string name, std::string category, double price, int quantity, std::string size, std::string material);
    ClothingProduct(const ClothingProduct& other);
    virtual ~ClothingProduct();
    ClothingProduct& operator=(const ClothingProduct& other);
    std::istream& input(std::istream& is) override;
    friend std::istream& operator>>(std::istream& is, ClothingProduct& clothingProduct);

    virtual void print(std::ostream& os) const override;
    void setSize(std::string newSize);
    void setMaterial(std::string newMaterial);
};