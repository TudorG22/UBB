#pragma once

#include <algorithm>
#include <vector>

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Observable {
private:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

protected:
    void notify() {
        for (auto* observer : observers) {
            observer->update();
        }
    }
};
