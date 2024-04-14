#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList()
{
    headPtr = nullptr;
    length = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    //automatically clears when destructor is called
    clear();
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &x)
{   
    //copies over the length
    length = x.length;

    //pointer which points to the list to be copied
    Node<T> *copyPtr = x.headPtr;


    //if the original list is empty, return an empty list
    if (copyPtr == nullptr)
    {
        headPtr = nullptr; 
        return;
    }

    //copying first node with a new head pointer
    headPtr = new Node<T>();
    headPtr->setItem(copyPtr->getItem());

    //copying the other nodes
    Node<T> *newPtr = headPtr;
    copyPtr = copyPtr->getNext();

    //loops while the next node doesn't point to nothing (end of list)
    while (copyPtr != nullptr)
    {
        //creates a new next node with the copied value
        T nodeValue = copyPtr->getItem();
        newPtr->setNext(new Node<T>(nodeValue));

        //iterates to the next node
        newPtr = newPtr->getNext();
        copyPtr = copyPtr->getNext();
    }

    //sets the end of the list
    newPtr->setNext(nullptr);
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> x)
{
    //copy swap idiom
    swap(x);
    return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList &x)
{
    //swaps private member variables
    std::swap(length, x.length);
    std::swap(headPtr, x.headPtr);
}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
    //returns 0 if empty
    return (length == 0);
}

template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{
    //returns length
    return length;
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T &item)
{
    //checks for valid position
    if (position > getLength() || position < 0)
    {
        return false;
    }


    Node<T> *newPtr = new Node<T>(item);
    //if added to beginning of list, sets the headpointer to new node
    if (position == 0)
    {
        newPtr->setNext(headPtr);
        headPtr = newPtr;
    }

    //inserts the node to the middle of the list
    else
    {
        Node<T> *currentPtr = headPtr;
        for (std::size_t i = 0; i < position - 1; i++)
        {
            currentPtr = currentPtr->getNext();
        }
        newPtr->setNext(currentPtr->getNext());
        currentPtr->setNext(newPtr);
    }
    length++;
    return true;
}


template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
    //checks for valid position
    if (isEmpty() || position >= getLength() || position < 0)
    {
        return false;
    }
    Node<T> *targetPtr = nullptr;

    //if removed node is at position 0, resets head pointer
    if (position == 0)
    {
        targetPtr = headPtr;
        headPtr = headPtr->getNext();
    }
    else 
    {
        Node<T> *prevPtr = headPtr;

        //iterates to node before target
        for (size_t i = 0; i < position - 1; i++)
        {
            prevPtr = prevPtr->getNext();
        }

        //sets target to the correct position
        targetPtr = prevPtr->getNext();

        //sets the next position of the previous to the next of the target, disconnecting the target
        prevPtr->setNext(targetPtr->getNext());
    }
    //deletes target and subtracts length
    delete targetPtr;
    length--;
    return true;
}

template <typename T>
void LinkedList<T>::clear()
{
    while (headPtr != nullptr)
    {
        remove(0);
    }
    headPtr = nullptr;
}


template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
    //return blank if position is invalid
    if (position >= getLength() || position < 0)
    {
        return T();
    }

    //iterates a pointer to position and returns
    Node<T> *currentPtr = headPtr;
    for (size_t i = 0; i < position; i++)
    {
        currentPtr = currentPtr->getNext();
    }

    return currentPtr->getItem();
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T &newValue)
{
    //checks if position is valid
    if (position < getLength() || position >= 0)
    {
        //iterates pointer to a position and sets the node to a new value
        Node<T> *currentPtr = headPtr;

        for (size_t i = 0; i < position; i++)
        {
            currentPtr = currentPtr->getNext();
        }

        currentPtr->setItem(newValue);
    }
}