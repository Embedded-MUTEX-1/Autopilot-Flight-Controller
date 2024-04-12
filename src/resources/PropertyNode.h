//
// Created by lenny on 14/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_PROPERTYNODE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_PROPERTYNODE_H

#include <functional>
#include <mutex>
#include <vector>

template <typename T>
class PropertyNode {
public:
    PropertyNode() {}
    void addCallback(std::function<void(T)> callback);
    void set(T &newValues);
    void get(T &values);
private:
    T values;
    std::mutex mutex;
    std::vector<std::function<void(T)>> callbacks;
};

//TODO à corriger(ld error)

template <typename T>
void PropertyNode<T>::addCallback(std::function<void(T)> callback)
{
    callbacks.push_back(callback);
}

template <class T>
void PropertyNode<T>::set(T &newValues)
{
    mutex.lock();
    this->values = newValues;
    for(auto callback: callbacks) {
        callback(newValues);
    }
    mutex.unlock();
}

template<class T>
void PropertyNode<T>::get(T &updatedValues) {
    mutex.lock();
    updatedValues = this->values;
    mutex.unlock();
}


#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_PROPERTYNODE_H
