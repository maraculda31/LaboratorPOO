#include "ProductFactory.h"

ProductFactory& ProductFactory::getInstance() {
    static ProductFactory instance;
    return instance;
}

ProductFactory::ProductFactory() {}

std::shared_ptr<Product> ProductFactory::createProduct(const std::string& type) {
    if (type == "Clothing") {
        return std::make_shared<ClothingProduct>();
    }
    else if (type == "Electronics") {
        return std::make_shared<ElectronicProduct>();
    }
    else {
        return nullptr;
    }
}