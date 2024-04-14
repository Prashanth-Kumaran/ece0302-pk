 #include "dynamic_bag.hpp"

template <typename T>
DynamicBag<T>::DynamicBag()
{
    capacity = 100;
    size = 0;
    bag_ptr = new T[capacity];
}

template <typename T>
DynamicBag<T>::DynamicBag(const DynamicBag<T> &x)
{
    capacity = x.capacity;
    size = x.size;
    bag_ptr = new T[capacity];
    for (int i = 0; i < size; i++)
    {
        bag_ptr[i] = x.bag_ptr[i];
    }
}

template <typename T>
DynamicBag<T>::~DynamicBag()
{
    delete[] bag_ptr;
}

template <typename T>
DynamicBag<T> &DynamicBag<T>::operator=(DynamicBag<T> x)
{
    delete[] bag_ptr;
    capacity = x.capacity;
    size = x.size;
    bag_ptr = new T[capacity];
    for (int i = 0; i < size; i++)
    {
        bag_ptr[i] = x.bag_ptr[i];
    }
    return *this;
}

template <typename T>
void DynamicBag<T>::swap(DynamicBag<T> &x)
{
    std::swap(*this, x);
}

template <typename T>
bool DynamicBag<T>::add(const T &item)
{
    if (size >= capacity)
    {
        T *temp_ptr;
        temp_ptr = new T[capacity * 2];
        for (int i = 0; i < size; i++)
        {
            temp_ptr[i] = bag_ptr[i];
        }
        delete[] bag_ptr;
        bag_ptr = temp_ptr;
    }
    bag_ptr[size] = item;
    size++;
    return true;
}

template <typename T>
bool DynamicBag<T>::remove(const T &item)
{
    //Loops through the array until the element matches the argument
    for (int i = 0; i < size; i++)
    {
        if (item == bag_ptr[i])
        {
            //shifts the remaining elements down by one and then deincrements the size
            for (int j = i + 1; j < size; j++)
            {
                bag_ptr[j - 1] = bag_ptr[j];
            }
            size--;
            return true;
        }
    }
    return false;
}

template <typename T>
bool DynamicBag<T>::isEmpty() const
{
    if (size == 0)
        return true;
    return false;
}

template <typename T>
std::size_t DynamicBag<T>::getCurrentSize() const
{
    return size;
}

template <typename T>
bool DynamicBag<T>::contains(const T &item) const
{
    for (int i = 0; i < size; i++)
    {
        if (item == bag_ptr[i])
            return true;
    }
    return false;
}

template <typename T>
void DynamicBag<T>::clear() {
    delete[] bag_ptr;
    bag_ptr = new T[capacity];
    size = 0;
}

template <typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T &item) const
{
    size_t count = 0;
    for(int i = 0; i < size; i++){
        if(bag_ptr[i] == item){
            count++;
        }
    }
    return count;
};
