#pragma once

class Observer {
public:
    virtual void update(int productId, int newQuantity) = 0;
};
