#include "ProducerConsumer.hpp"
#include <iostream>

ProducerConsumer::ProducerConsumer() {
    queueEnd = 0;
    queueFront = 0;
}

//returns true if the queue is empty, false if not
bool ProducerConsumer::isEmpty() {
    return (counter == 0) ? true : false;
}

//returns the amount of items in the queue
int ProducerConsumer::queueSize() {
    return counter;
}

//returns true if the queue is full, false if not
bool ProducerConsumer::isFull() {
    return (queueSize() == SIZE) ? true : false;
}

//Adds an item to location of queueEnd in the array
void ProducerConsumer::enqueue(std::string item) {
    if (isFull()) {
        std::cout << "Queue full, cannot add new item with size" << std::endl;
        return;
    }
    else {
        counter++;
        queue[queueEnd] = item;
        if (queueEnd == SIZE - 1) {
            queueEnd = 0;
        }
        else {
            queueEnd++;
        }
    }
}

//Removes an item from the location of queueFront in the array
void ProducerConsumer::dequeue() {
    if (isEmpty()) {
        std::cout << "Queue empty, cannot dequeue an item" << std::endl;
    }
    else {
        counter--;
        queue[queueFront] == "";
        if (queueFront ==  SIZE - 1) {
            queueFront = 0;
        }
        else {
            queueFront++;
        }
    }
}

//If the queue is NOT empty this will return the item pointed to by queueFront
std::string ProducerConsumer::peek() {
    if (isEmpty()) {
        std::cout << "Queue empty, cannot peek" << std::endl;
        return "";
    }
    else {
        return queue[queueFront];
    }
}



