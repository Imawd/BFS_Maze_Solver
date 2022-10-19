/* 
queue.cpp
*/

#include "queue.h"

//Constructor. maxlen must be as large as the total number
// of Locations that will ever be entered into this Queue.
// This is complete, you don't need to change it.
Queue::Queue(int maxlen) {
   contents = new Location[maxlen];
   head = 0;
   tail = 0;
}

//Destructor. releases resources. C++ will call it automatically.
//This is complete, you don't need to change it.
Queue::~Queue() {
  delete[] contents;
}

//Insert a new Location at the end/back of our list   
void Queue::add_to_back(Location loc) {
	
   // *** You complete **** CHECKPOINT 3
   contents[tail++] = loc;
}

//Return and "remove" the oldest Location not already extracted
Location Queue::remove_from_front() {
  
   // *** You complete **** CHECKPOINT 3
   return contents[head++];
}

//Is this Queue empty? (did we extract everything added?)
//This is complete, you don't need to change it.
bool Queue::is_empty() {
   return head == tail;
}

