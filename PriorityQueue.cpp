/*
 * PriorityQueue.cpp
 *
 * Description: Priority Queue
 * Class Invariant: The elements stored in this Priority Queue are always sorted.
 *
 * Author: Jiacheng Xu & Carla Louw
 * Modified: March 17, 2019
 *
 */

 /* None of the current content of this file can be modified. */

#include "PriorityQueue.h"

// Default Constructor
PriorityQueue::PriorityQueue(){
    head = NULL;
    tail = NULL;
    elementCount = 0;
}

// Destructor
PriorityQueue::~PriorityQueue(){
    Node* ToBeRemoved = NULL;
    Node* current = head;
    while (current!= NULL) {
      ToBeRemoved = current;
      current = current->next;
      delete ToBeRemoved;
      ToBeRemoved = NULL;
    }
    elementCount = 0;
}

// Description: Returns the number of elements in the Priority Queue.
// Time Efficiency: O(1)
int PriorityQueue::getElementCount() const{
    return elementCount;
}

// Description: Returns "true" is this Priority Queue is empty, otherwise "false".
// Time Efficiency: O(1)
bool PriorityQueue::isEmpty() const{
    return elementCount == 0;
}

// Description: Inserts newElement in sort order.
//              It returns "true" if successful, otherwise "false".
// Precondition: This Priority Queue is sorted.
// Postcondition: Once newElement is inserted, this Priority Queue remains sorted.
// Time Efficiency: O(n)
bool PriorityQueue::enqueue(HuffmansTree* newElement){
    // if the queue is empty:
    if (elementCount == 0){
        Node* newNode = new Node(newElement);
        head = newNode;
        tail = newNode;
        elementCount++;
	    return true;
    }
    // not empty:
    Node* newNode = new Node(newElement);
    Node* current = head;
    while (current!= NULL && current->priority > newNode->priority) {
        current = current->next;
    }
    if (current == NULL){
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        elementCount++;
        return true;
    }else {
        Node* nextNode = current;
        current = current->prev;
        if (current == NULL){
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
            elementCount++;
            return true;
        }
        current->next = newNode;
        nextNode->prev = newNode;
        newNode->next = nextNode;
        newNode->prev = current;
        elementCount++;
        return true;
    }
}

// Description: Removes the element with the "highest" priority.
//              It returns "true" if successful, otherwise "false".
// Precondition: This Priority Queue is not empty.
// Time Efficiency: O(1)
bool PriorityQueue::dequeue(){
    if (elementCount == 0){
        return false;
    } else {
        Node* ToBeRemoved = tail;
        tail = tail->prev;
    if (tail == NULL){
        head = NULL;
    } else {
        tail->next = NULL;
    }
        delete ToBeRemoved;
        ToBeRemoved = NULL;
        elementCount--;
	return true;
    }
}

// Description: Returns the element with the "highest" priority.
// Precondition: This Priority Queue is not empty.
// Postcondition: This Priority Queue is unchanged.
// Exceptions: Throws EmptyDataCollectionException if this Priority Queue is empty.
// Time Efficiency: O(1)
HuffmansTree* PriorityQueue::peek() const{
    if (tail){
        return tail->data;
    } else {
        cout << "Cannot peek the queue since it is empty!" << endl;
    }
}
