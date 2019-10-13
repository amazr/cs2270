#include <iostream>
#include "RPNCalculator.hpp"

RPNCalculator::RPNCalculator() {
    stackHead = NULL;
}

RPNCalculator::~RPNCalculator() {
    //Must pop everything from stack first
    Operand *temp = stackHead;
    if (stackHead != NULL) {
        while (temp->next != NULL) {
            temp=temp->next;
            pop();
        }
        pop();
        stackHead = NULL;
    }
}

//If the stackHead is null, return true, else return false
bool RPNCalculator::isEmpty() {
    return (stackHead == NULL ? true : false);
}

//Inserts a new operand at the top of the stack
void RPNCalculator::push(float num) {
    Operand *newOP = new Operand();
    newOP->number = num;
    newOP->next = NULL;

    if (isEmpty()) {
        stackHead = newOP;
    }
    else {
        Operand *temp = stackHead;
        stackHead = newOP;
        newOP->next = temp;
    }
}

//Removes the item at the top of the linked list
void RPNCalculator::pop() {
    if (isEmpty()) {
        std::cout << "Stack empty, cannot pop an item." << std::endl;
        return;
    }
    Operand *temp = stackHead;
    stackHead = stackHead->next;
    delete temp;
}

//Returns a pointer to the top of the stack as long as the stack is NOT empty
Operand* RPNCalculator::peek() {
    if (isEmpty()) {
        std::cout << "Stack empty, cannot peek." << std::endl;
        return NULL;
    }
    else {
        return stackHead;
    }
}

//This will calculate the addition or multiplication of the first two elements of a stack or return false
bool RPNCalculator::compute(std::string symbol) {
    float num1, num2;

    if (isEmpty()) {
        std::cout << "err: not enough operands" << std::endl;
        return false;
    }
    else {
        num1 = peek()->number;
        pop();
        if (isEmpty()) {
            std::cout << "err: not enough operands" << std::endl;
            push(num1);
            return false;
        }
        num2 = peek()->number;
        pop();
    }

    if (symbol == "+") {
        float result = num1 + num2;
        push(result);
        return true;
    }
    else if (symbol == "*") {
        float result = num1 * num2;
        push(result);
        return true;
    }
    else {
        push(num2);
        push(num1);
        std::cout << "err: invalid operation" << std::endl;
        return false;
    }

    return false;
}