#include <iostream>
#include "QUEUEST.hpp"
using namespace std;


Queue::Queue()
{

}
Queue::~Queue()
{
  while(!isEmpty())
    dequeue();
}

/**
* This function will create the queue of size cap
* parameter: int cap
* return void
**/
void Queue:: initialiseQueue(int cap)
{
  primary.initialise(cap);
  secondary.initialise(cap);
}

/**
* This function will enqueue the argument num
* parameter: int num
* return void
**/
void Queue:: enqueue(int num){
    if(isFull())
    {
      cout<< " Queue is full. Can not enqueue"<<endl;
      return;
    }
    primary.push(num);
}
/**
* This function will dequeue from the queue.
* parameter: None
* return the dequeued value
* TODO: Implement this function
**/
int Queue:: dequeue(){

  //Return -999 if queueu is empty
  if (primary.isEmpty()) {
    cout << "Queue is empty. Can not dequeue" << endl;
    return -999;
  }

  //Transfers all values from prim to sec 
  while (true) {
    if (primary.isEmpty()) {
      break;
    }
    int temp = primary.peek();
    primary.pop();
    secondary.push(temp);
  }

  //sets return value to top of sec
  int toReturn = secondary.peek();
  secondary.pop();

  //returns all sec back to primary except for the val to be returned
  while(true) {
    if (secondary.isEmpty()) {
      break;
    }
    int temp = secondary.peek();
    secondary.pop();
    primary.push(temp);
  }
  
  return toReturn;
}
/**
* returns true if queue is full
**/
bool Queue:: isFull(){
  return primary.isFull();
}

/**
* returns true if queue is full.
**/
bool Queue:: isEmpty(){
  return primary.isEmpty();
}
