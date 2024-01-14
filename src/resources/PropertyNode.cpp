//
// Created by lenny on 14/01/24.
//

#include "PropertyNode.h"

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
