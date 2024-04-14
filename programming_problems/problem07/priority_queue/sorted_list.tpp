#include "sorted_list.hpp"

template <typename T, typename L>
SortedList<T, L>::SortedList()
{
    // nothing to do, plist gets created on the stack
}

template <typename T, typename L>
SortedList<T, L>::SortedList(const SortedList<T, L> &x)
{
    plist = x.plist; // use copy assignment to implement copy construction
}

template <typename T, typename L>
SortedList<T, L> &SortedList<T, L>::operator=(SortedList<T, L> x)
{
    plist = x.plist;
    return *this;
}

template <typename T, typename L>
SortedList<T, L>::~SortedList()
{
    // plist destructor gets called automatically
}

template <typename T, typename L>
bool SortedList<T, L>::isEmpty() const noexcept
{
    return plist.isEmpty();
}

template <typename T, typename L>
std::size_t SortedList<T, L>::getLength() const noexcept
{
    return plist.getLength();
}

template <typename T, typename L>
void SortedList<T, L>::insert(const T &item)
{
    // if the list is empty, automatically inserts into 0th position
    if (isEmpty())
    {
        plist.insert(0, item);
        return;
    }
    for (size_t i = 0; i < getLength(); i++)
    {
        // inserts to the first position where item is less than the entry at that position
        if (item <= getEntry(i))
        {
            plist.insert(i, item);
            return;
        }
    }
    // if item is the greatest entry, inserts at the back of the list
    plist.insert(getLength(), item);
}

template <typename T, typename L>
void SortedList<T, L>::remove(const T &item)
{
    if (isEmpty())
        throw std::range_error("empty list in remove");
    // if the item is not in the list, throws error
    if (getPosition(item) == -1)
    {
        throw std::range_error("item not in list");
    }
    // removes the item
    else
    {
        plist.remove(getPosition(item));
    }
}

template <typename T, typename L>
void SortedList<T, L>::removeAt(std::size_t position)
{
    plist.remove(position);
}

template <typename T, typename L>
void SortedList<T, L>::clear()
{
    plist.clear();
}

template <typename T, typename L>
T SortedList<T, L>::getEntry(std::size_t position) const
{
    return plist.getEntry(position);
}

template <typename T, typename L>
long int SortedList<T, L>::getPosition(const T &newValue)
{
    //loops through the list and finds the first instance of the item, returns the position
    for(size_t i = 0; i < getLength(); i++){
        if(getEntry(i) == newValue){
            return i;
        }
    }

    //if item is not found, returns -1
    return -1;
}
