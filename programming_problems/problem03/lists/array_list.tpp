#include "array_list.hpp"

template <typename T>
ArrayList<T>::ArrayList()
{
    length = 0;
    listPtr = nullptr;

}

template <typename T>
ArrayList<T>::~ArrayList()
{
    delete[] listPtr;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList& rhs) {
    length = rhs.length;
    listPtr = new T[length];

    for (size_t i = 0; i < length; i++) {
        listPtr[i] = rhs.listPtr[i];
    }
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList rhs)
{
    //Copy and Swap idiom
    swap(rhs);
    return *this;
}

template <typename T>
void ArrayList<T>::swap(ArrayList& rhs) {
    std::swap(listPtr, rhs.listPtr);
    std::swap(length, rhs.length);
}

template <typename T>
bool ArrayList<T>::isEmpty() const noexcept
{
    if (length == 0) {
        return true;
    }
    else {
        return false;
    }
}

template <typename T>
std::size_t ArrayList<T>::getLength() const noexcept {
    return length;
}

template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T& item) {
    //Checking for valid position
    if (position < 0 || position > length) {
        return false;
    }
    if (length == 0) {
        delete[] listPtr;
        length++;
        listPtr = new T[length];
        listPtr[position] = item;
        return true;
    }
    //incrementing the size of the array
    T* oldPtr = listPtr;
    listPtr = new T[length + 1];
    for(size_t i = 0; i < length; i++){
        listPtr[i] = oldPtr[i];
    }
    length++;
    delete[] oldPtr; 
    
    for (size_t i = length - 1; i > position; i--) {
        listPtr[i] = listPtr[i - 1];
    }
    listPtr[position] = item;
    return true;
}

template <typename T>
bool ArrayList<T>::remove(std::size_t position) {
    if (position < 0 || position > length || length == 0) {
        return false;
    }
    if (length == 1) {
        length--;
        return true;
    }

    for (size_t i = position; i < length - 1; i++) {
        listPtr[i] = listPtr[i + 1];
    }
    T* oldPtr = listPtr;
    listPtr = new T[length - 1];
    for(size_t i = 0; i < length - 1; i++){
        listPtr[i] = oldPtr[i];
    }
    length--;
    delete[] oldPtr; 
    return true;
}

template <typename T>
void ArrayList<T>::clear() {
    length = 0;
}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const
{
    if (0 <= position && position < length) {
        return listPtr[position];
    }

    return T();
}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T& newValue) {
    if (0 <= position && position < length) {
        listPtr[position] = newValue;
    }
}
