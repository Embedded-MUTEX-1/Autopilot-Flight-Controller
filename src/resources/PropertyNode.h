//
// Created by lenny on 14/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_PROPERTYNODE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_PROPERTYNODE_H

#include <mutex>

template <typename T>
class PropertyNode {
public:
    PropertyNode() {}
    void set(T &newValues);
    void get(T &values);
private:
    T values;
    std::mutex mutex;
};

//TODO à corriger(ld error)

template<class T>
void PropertyNode<T>::set(T &newValues) {
    mutex.lock();
    this->values = newValues;
    mutex.unlock();
}

template<class T>
void PropertyNode<T>::get(T &updatedValues) {
    mutex.lock();
    updatedValues = this->values;
    mutex.unlock();
}


#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_PROPERTYNODE_H
