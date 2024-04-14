#ifndef _SORT_HPP
#define _SORT_HPP

#include "linked_list.hpp"

template<typename T> LinkedList<T> sort(LinkedList<T> list)
{
    //Bubble sort :)

    //boolean to check if a swap occured, if false, then list is sorted
	bool swapOccured;

    //integer which represents the index of the last unsorted element
    size_t last = list.getLength() - 1;
    do{
        swapOccured = false;
        //iterates through the unsorted elements
        for(size_t i = 0; i < last; i++){
            //checks if an element needs to be swapped
            if(list.getEntry(i+1) < list.getEntry(i)){
                //swapping
                swapOccured = true;
                T temp = list.getEntry(i+1);
                list.setEntry(i+1, list.getEntry(i));
                list.setEntry(i, temp);
            }
        }
        //decreases the number of unsorted elements
        last --;
    //loop can break as soon as the list is sorted
    }while(swapOccured);

	return list;
}

#endif
