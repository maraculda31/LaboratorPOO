#pragma once

#include <memory>
#include <string>
#include "Product.h"
#include "ClothingProduct.h"
#include "ElectronicProduct.h"

class ProductFactory {
public:
    static ProductFactory& getInstance();

    ProductFactory(ProductFactory const&) = delete;
    void operator=(ProductFactory const&) = delete;

    std::shared_ptr<Product> createProduct(const std::string& type);

private:
    ProductFactory();
};
