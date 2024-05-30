#pragma once

#include <list>
#include <algorithm>

template <typename T>
class Storage {
private:
    std::list<T> items;

public:
    void addItem(const T& item) {
        items.push_back(item);
    }

    void removeItem(const T& item) {
        items.remove(item);
    }

    const std::list<T>& getItems() const {
        return items;
    }

    template <typename Func>
    std::list<T> findItems(Func func) {
        std::list<T> results;
        for (auto& item : items) {
            if (func(item)) {
                results.push_back(item);
            }
        }
        return results;
    }
};
