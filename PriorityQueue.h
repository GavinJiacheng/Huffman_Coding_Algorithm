/*
 * PriorityQueue.h
 *
 * Description: Priority Queue
 * Class Invariant: The elements stored in this Priority Queue are always sorted.
 *
 * Author: Jiacheng Xu & Carla Louw
 * Modified: March 17, 2019
 *
 */

 /* None of the current content of this file can be modified. */

#pragma once
#include "HuffmansTree.h"
#include <iostream>

class Node {
    public:
        Node(HuffmansTree* ElementType){
            data = ElementType;
            next = NULL;
            prev = NULL;
            priority = ElementType->getPriority();
        }
        HuffmansTree* data;
        Node* next;
        Node* prev;
	      // Desc: store the priority of the element inside of the node
        long int priority;
};


class PriorityQueue {

private:

   Node* head;      // Pointer to first node in the chain
   int elementCount;   // Current count of list items
   Node* tail;      // to the last node

/* You can add private methods to this class */

public:

   // Default Constructor
   PriorityQueue();

   // Destructor
   ~PriorityQueue();

   // Description: Returns the number of elements in the Priority Queue.
   // Time Efficiency: O(1)
   int getElementCount() const;

   // Description: Returns "true" is this Priority Queue is empty, otherwise "false".
   // Time Efficiency: O(1)
   bool isEmpty() const;

   // Description: Inserts newElement in sort order.
   //              It returns "true" if successful, otherwise "false".
   // Precondition: This Priority Queue is sorted.
   // Postcondition: Once newElement is inserted, this Priority Queue remains sorted.
   // Time Efficiency: O(n)
   bool enqueue(HuffmansTree* newElement);

   // Description: Removes the element with the "highest" priority.
   //              It returns "true" if successful, otherwise "false".
   // Precondition: This Priority Queue is not empty.
   // Time Efficiency: O(1)
   bool dequeue();

   // Description: Returns the element with the "highest" priority.
   // Precondition: This Priority Queue is not empty.
   // Postcondition: This Priority Queue is unchanged.
   // Exceptions: Throws EmptyDataCollectionException if this Priority Queue is empty.
   // Time Efficiency: O(1)
   HuffmansTree* peek() const;

}; // end PriorityQueue
