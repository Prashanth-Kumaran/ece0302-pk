#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList()
{
  headPtr = nullptr;
  itemCount = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  clear(); // clear to deconstruct list
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &x)
{
  itemCount = x.itemCount;
  Node<T> *originalPtr = x.headPtr;
  if (originalPtr == nullptr)
  {
    headPtr = nullptr; // copy will be empty if original list is empty
    return;
  }

  // copying the first node
  headPtr = new Node<T>();
  headPtr->setItem(originalPtr->getItem());

  // copying the remaining nodes
  Node<T> *newPtr = headPtr;
  originalPtr = originalPtr->getNext();

  // get next item, create a new node with the next item, then link the new node and advance pointers
  while (originalPtr != nullptr)
  {
    T nodeValue = originalPtr->getItem();

    newPtr->setNext(new Node<T>(nodeValue));

    newPtr = newPtr->getNext();
    originalPtr = originalPtr->getNext();
  }

  newPtr->setNext(nullptr); // this is the new end
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> x)
{
  swap(x);
  return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList &x)
{
  std::swap(itemCount, x.itemCount);
  std::swap(headPtr, x.headPtr);
}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
  return (itemCount == 0);
}

template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{
  return itemCount;
}

// copied from textbook. pg 278 from function insert
template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T &item)
{
  // create a new node with the entry and make a new node at the beginnig
  if (position > getLength())
  {
    return false;
  }
    Node<T> *newnode = new Node<T>(item);

    if (position == 0)
    {
      newnode->setNext(headPtr);
      headPtr = newnode;
    }
    // get the node before the new node and insert the new node after the node of the previous pointer
    else
    {
      Node<T> *currentPtr = headPtr;
      for(std::size_t i = 0; i < position - 1; i++)
      {
        currentPtr = currentPtr->getNext();
      }
      newnode->setNext(currentPtr->getNext());
      currentPtr->setNext(newnode);
    }
    itemCount++; // need to increase the size after inserting
    return true;
  }

// took code from textbook: pg 281, function remove
template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  
  if(isEmpty() || position >= getLength())
  {
    return false;
  }
    Node<T> *removenode = nullptr;

    // headpointer should be a position 0
    if (position == 0)
    {
      removenode = headPtr;
      headPtr = headPtr->getNext();
    }
    // if the position is 1, remove the first node and save the current pointer to the head pointer
    else // find node before the node to remove and disconnect the node from the list
    {
      Node<T>* currentPtr = headPtr;

      for(size_t i = 0; i < position - 1; i++)
      {
        currentPtr = currentPtr->getNext();
      }
      removenode = currentPtr ->getNext();

      removenode = currentPtr ->getNext();

      currentPtr->setNext(removenode->getNext());
    }
    delete removenode;
    itemCount--;
    return true;
  }

// copied function from the text book. pg 146, clear function
template <typename T>
void LinkedList<T>::clear()
{
  Node<T> *deletePtr = headPtr;
  while (headPtr != nullptr)
  {
    // return node and make headPtr a nullptr and deletePtr a nullptr
    headPtr = headPtr->getNext();
    deletePtr->setNext(nullptr);
    delete deletePtr;
    deletePtr = headPtr;
  }
  itemCount = 0;
}

// copy form List ADT from textbook. pg 275 getEntry function
template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  // check if the position is out of bounds and then proceed to set pointer
  if(position >= getLength())
  {
    return T();
  }

  //go up until the position and then get an item at that position
  Node<T>* currentPtr = headPtr;
  for(size_t i = 0; i < position; i++)
  {
    currentPtr = currentPtr->getNext();
  }

  return currentPtr->getItem();
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T &newValue)
{
  //position should be checked so that it is less than the length of the list
  if(position < getLength())
  {
    Node<T>* currentPtr = headPtr; //set head pointer then go through the list. The Item should be set to the position

    for(size_t i = 0; i < position; i++)
    {
      currentPtr = currentPtr->getNext();
    }

    currentPtr->setItem(newValue);
  }
}
