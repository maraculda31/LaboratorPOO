#pragma once

#include <exception>

class ProductException : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "General product exception";
    }
};

class ProductNotFoundException : public ProductException {
public:
    virtual const char* what() const noexcept override {
        return "Product not found";
    }
};

class InvalidProductDataException : public ProductException {
public:
    virtual const char* what() const noexcept override {
        return "Invalid product data provided";
    }
};