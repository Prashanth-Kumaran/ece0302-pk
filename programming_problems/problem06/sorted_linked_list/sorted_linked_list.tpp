#include "sorted_linked_list.hpp"
#include <stdexcept>

template <typename T>
SortedLinkedList<T>::SortedLinkedList() : LinkedList<T>()
{
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(LinkedList<T> unsorted_list)
{
    //insert's every element, insert automatically sorts
    for (size_t i = 0; i < unsorted_list.getLength(); i++)
    {
        insert(unsorted_list.getEntry(i));
    }
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(const SortedLinkedList<T> &x) : LinkedList<T>(x)
{
}

template <typename T>
SortedLinkedList<T> &SortedLinkedList<T>::operator=(SortedLinkedList<T> x)
{
    LinkedList<T>::operator=(x);
    return *this;
}

template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
    // base destructor gets called automatically
}

template <typename T>
bool SortedLinkedList<T>::isEmpty() const noexcept
{
    return LinkedList<T>::isEmpty();
}

template <typename T>
std::size_t SortedLinkedList<T>::getLength() const noexcept
{
    return LinkedList<T>::getLength();
}

template <typename T>
void SortedLinkedList<T>::insert(const T &item)
{
    //if the list is empty, automatically inserts into 0th position
    if (isEmpty())
    {
        LinkedList<T>::insert(0, item);
        return;
    }
    for (size_t i = 0; i < getLength(); i++)
    {
        //inserts to the first position where item is less than the entry at that position
        if (item <= getEntry(i))
        {
            LinkedList<T>::insert(i, item);
            return;
        }
    }
    //if item is the greatest entry, inserts at the back of the list
    LinkedList<T>::insert(getLength(), item);
}

template <typename T>
void SortedLinkedList<T>::remove(const T &item)
{
    if (isEmpty())
        throw std::range_error("empty list in remove");
    //if the item is not in the list, throws error
    if(getPosition(item) == -1){
        throw std::range_error("item not in list");
    }
    //removes the item
    else{
        LinkedList<T>::remove(getPosition(item));
    }
}

template <typename T>
void SortedLinkedList<T>::removeAt(std::size_t position)
{
    if (isEmpty())
        throw std::range_error("empty list in remove");
    LinkedList<T>::remove(position);
}

template <typename T>
void SortedLinkedList<T>::clear()
{
    LinkedList<T>::clear();
}

template <typename T>
T SortedLinkedList<T>::getEntry(std::size_t position) const
{
    return LinkedList<T>::getEntry(position);
}

template <typename T>
long int SortedLinkedList<T>::getPosition(const T &item)
{
    //loops through the list and finds the first instance of the item, returns the position
    for(size_t i = 0; i < getLength(); i++){
        if(getEntry(i) == item){
            return i;
        }
    }

    //if item is not found, returns -1
    return -1;
}
