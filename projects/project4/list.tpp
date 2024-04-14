#include "list.hpp"

template <typename T>
List<T>::List()
{
    length = 0;
    listPtr = nullptr;
}

template <typename T>
List<T>::~List()
{
    delete[] listPtr;
}

template <typename T>
List<T>::List(const List<T> &x)
{
    length = x.length;
    listPtr = new T[length];

    for (size_t i = 0; i < length; i++)
    {
        listPtr[i] = x.listPtr[i];
    }
}

template <typename T>
List<T> &List<T>::operator=(List<T> x)
{
    // Copy and Swap idiom
    swap(x);
    return *this;
}

template <typename T>
void List<T>::swap(List<T> &x)
{
    std::swap(listPtr, x.listPtr);
    std::swap(length, x.length);
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
    if (length == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
    return length;
}

template <typename T>
void List<T>::insert(std::size_t position, const T &item)
{
    // Checking for valid position
    if (position < 0 || position > length)
    {
        throw std::range_error("Position out of range");
    }
    if (length == 0)
    {
        delete[] listPtr;
        length++;
        listPtr = new T[length];
        listPtr[position] = item;
        return;
    }
    // incrementing the size of the array
    T *oldPtr = listPtr;
    listPtr = new T[length + 1];
    for (size_t i = 0; i < length; i++)
    {
        listPtr[i] = oldPtr[i];
    }
    length++;
    delete[] oldPtr;

    for (size_t i = length - 1; i > position; i--)
    {
        listPtr[i] = listPtr[i - 1];
    }
    listPtr[position] = item;
    return;
}

template <typename T>
void List<T>::remove(std::size_t position)
{
    if (position < 0 || position > length || length == 0)
    {
        throw std::range_error("Position out of range");
    }
    if (length == 1)
    {
        length--;
        return;
    }

    for (size_t i = position; i < length - 1; i++)
    {
        listPtr[i] = listPtr[i + 1];
    }
    T *oldPtr = listPtr;
    listPtr = new T[length - 1];
    for (size_t i = 0; i < length - 1; i++)
    {
        listPtr[i] = oldPtr[i];
    }
    length--;
    delete[] oldPtr;
    return;
}

template <typename T>
void List<T>::clear()
{
    length = 0;
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
    if (0 <= position && position < length)
    {
        return listPtr[position];
    }

    return T();
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T &newValue)
{
    if (0 <= position && position < length)
    {
        listPtr[position] = newValue;
    }
}
