#pragma once

#include "Product.h"
#include <string>

class ElectronicProduct : public Product {
private:
    int warrantyPeriod;

public:
    ElectronicProduct();
    ElectronicProduct(int id, std::string name, std::string category, double price, int quantity, int warrantyPeriod);
    ElectronicProduct(const ElectronicProduct& other);
    virtual ~ElectronicProduct();
    ElectronicProduct& operator=(const ElectronicProduct& other);
    std::istream& input(std::istream& is) override;
    friend std::istream& operator>>(std::istream& is, ElectronicProduct& electronicProduct);


    void extendWarranty(int additionalMonths);
    virtual void print(std::ostream& os) const override;
};