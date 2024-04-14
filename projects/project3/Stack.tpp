//   Adapated from Frank M. Carrano and Timothy M. Henry.

/** ADT Stack implementation.
    @file Stack.cpp */

#include <iostream>
#include <cstddef>
#include "Stack.hpp"
#include "Node.hpp"

// TODO: Implement the constructor here
template <class ItemType>
Stack<ItemType>::Stack()
{
    headPtr = nullptr;
    currentSize = 0;
} // end default constructor

// TODO: Implement the destructor here
template <class ItemType>
Stack<ItemType>::~Stack()
{
    clear();
} // end destructor

// TODO: Implement the isEmpty method here
template <class ItemType>
bool Stack<ItemType>::isEmpty() const
{
    return (currentSize == 0);
} // end isEmpty

// TODO: Implement the size method here
template <class ItemType>
int Stack<ItemType>::size() const
{
    return currentSize;
} // end size

// TODO: Implement the push method here
template <class ItemType>
bool Stack<ItemType>::push(const ItemType &newItem)
{
    Node<ItemType> *newNode = new Node<ItemType>(newItem);
    newNode->setNext(headPtr);
    headPtr = newNode;
    currentSize++;
    // newNode = nullptr;
    return true;
} // end push

// TODO: Implement the peek method here
template <class ItemType>
ItemType Stack<ItemType>::peek() const
{
    if (isEmpty())
    {
        throw std::logic_error("Peeking empty stack");
    }
    else
    {
        return headPtr->getItem();
    }

} // end peek

// TODO: Implement the pop method here
template <class ItemType>
bool Stack<ItemType>::pop()
{
    if (currentSize == 0)
    {
        return false;
    }
    else
    {
        Node<ItemType> *targetPtr = headPtr;
        headPtr = targetPtr->getNext();
        delete targetPtr;
        targetPtr = nullptr;
        currentSize--;
        return true;
    }
} // end pop

// TODO: Implement the clear method here
template <class ItemType>
void Stack<ItemType>::clear()
{
    while (!isEmpty())
    {
        pop();
    }
} // end clear
