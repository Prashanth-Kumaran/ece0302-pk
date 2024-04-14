#include "limited_size_bag.hpp"

template <typename T>
LimitedSizeBag<T>::LimitedSizeBag()
{
    size = 0;
}

template <typename T>
bool LimitedSizeBag<T>::add(const T &item)
{
    if (size >= maxsize)
    {
        return false;
    }
    else
    {
        bagArray[size] = item;
        size++;
        return true;
    }
}

template <typename T>
bool LimitedSizeBag<T>::remove(const T &item)
{
    //Loops through the array until an element matches the argument
    for (int i = 0; i < size; i++)
    {
        if (bagArray[i] == item)
        {
            //Shifts the remaining elements down one, and deincrements the size
            for (int j = i + 1; j < size; j++)
            {
                bagArray[j - 1] = bagArray[j];
            }
            size--;
            return true;
        }
    }
    return false;
}

template <typename T>
bool LimitedSizeBag<T>::isEmpty() const
{
    if (size == 0)
        return true;
    return false;
}

template <typename T>
std::size_t LimitedSizeBag<T>::getCurrentSize() const
{
    return size;
}

template <typename T>
bool LimitedSizeBag<T>::contains(const T &item) const
{
    for (int i = 0; i < size; i++)
    {
        if (bagArray[i] == item)
            return true;
    }

    return false;
}

template <typename T>
void LimitedSizeBag<T>::clear() {
    size = 0;
}

template <typename T>
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T &item) const
{
    std::size_t count = 0;
    for (int i = 0; i < size; i++)
    {
        if (bagArray[i] == item)
            count++;
    }
    return count;
};
