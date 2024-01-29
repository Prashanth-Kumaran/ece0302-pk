#ifndef _ABSTRACT_BAG_HPP_
#define _ABSTRACT_BAG_HPP_

#include <cstdlib>

/** Interface for class Bag
 @file abstract_bag.hpp
*/
template <typename T>
class AbstractBag
{
    /**Returns the current number of elements in the bag
     @return size
    */
    virtual std::size_t getCurrentSize() const = 0;

    /**Checks if the bag is empty
     @return 0 if the current size is not 0, 1 if it is
    */
    virtual bool isEmpty() const = 0;

    /**Adds an item to the bag
     @precondition bag contains items
     @param item to be added
     @return 0 if bag is full and item cannot be added, 1 if item is successfully added
     @postcondition the item is added to the bag at the next index
    */
    virtual bool add(const T &entry) = 0;

    /**Removes an item from the bag
     @param item to be removed
     @precondition bag contains tems
     @return 1 if item is found and successfully removed, 0 if bag is empty or item is not in the bag
     @postcondition the lowest index instance of the selected item is removed from the bag, all higher indexes are shifted down by one
    */
    virtual bool remove(const T &entry) = 0;

    /**Removes all items from the bag by setting the size to 0
    */
    virtual void clear() = 0;

    /**Counts the number of times an item appears in the bag
     @param item to be counted
     @return amount of times the item is in the bag
    */
    virtual std::size_t getFrequencyOf(const T &entry) const = 0;

    /**Checks if bag contains an item
     @param item to be checked
     @return 0 if item is not found, 1 if item is found
    */
    virtual bool contains(const T &entry) const = 0;
};

#endif