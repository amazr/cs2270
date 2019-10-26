#include "MovieTree.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include<fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

//Helper functions
void printInOrder(TreeNode *node) {
  if(node != NULL) {
    printInOrder(node->leftChild);
    cout << "Movies starting with letter: " << node->titleChar << endl;
    LLMovieNode *temp = node->head;
    while(temp != NULL) {
      cout << " >> " << temp->title << " " << temp->rating << endl;
      temp = temp->next;
    }

    printInOrder(node->rightChild);
  }
}

TreeNode* getMinValueNode(TreeNode* currNode){

    if(currNode->leftChild == NULL){
      return currNode;
    }
    return getMinValueNode(currNode->leftChild);
}

void deleteTree(TreeNode *node) { //Delete the entire tree
  if (node == NULL) return;

  if (node->leftChild != NULL) {
    deleteTree(node->leftChild);
  }
  if (node->rightChild != NULL) {
    deleteTree(node->rightChild);
  }

  LLMovieNode* current = node->head;  
  LLMovieNode* next;  
  
  while (current != NULL) {  
    next = current->next;  
    delete current;  
    current = next;  
  }  

  delete node;
}

TreeNode* deleteNode(TreeNode* currNode, char value)
{

  if(currNode == NULL)
  {
    return NULL;
  }
  else if(value < currNode->titleChar)
  {
    currNode->leftChild = deleteNode(currNode->leftChild, value);
  }
  else if(value > currNode->titleChar)
  {
    currNode->rightChild = deleteNode(currNode->rightChild, value);
  }
  // We found the node with the value
  else
  {
    //TODO Case : No child
    if(currNode->leftChild == NULL && currNode->rightChild == NULL)
    {
        delete currNode;
        return NULL;

    }
    //TODO Case : Only right child
    else if(currNode->leftChild == NULL)
    {
        currNode->titleChar = currNode->rightChild->titleChar;
        currNode->head = currNode->rightChild->head;
        if (currNode->rightChild->rightChild == NULL) {
          currNode->rightChild = NULL;
        }
        else {
          currNode->rightChild = currNode->rightChild->rightChild;
        }
    }
    //TODO Case : Only left child
    else if(currNode->rightChild == NULL)
    {
        currNode->titleChar = currNode->leftChild->titleChar;
        currNode->head = currNode->leftChild->head;
        if (currNode->leftChild->leftChild == NULL) {
          currNode->leftChild = NULL;
        }
        else {
          currNode->leftChild = currNode->leftChild->leftChild;
        }
    }
    //TODO Case: Both left and right child
    else
    {
        //Replace with Minimum from right subtree
        currNode->titleChar = getMinValueNode(currNode->rightChild)->titleChar;
        currNode->head = getMinValueNode(currNode->rightChild)->head;
        currNode->rightChild = deleteNode(currNode->rightChild, currNode->titleChar);
    }

  }
return currNode;
}



MovieTree::MovieTree() {
  //set root MovieNode to NULL
  root = NULL;
}

MovieTree::~MovieTree() {
  deleteTree(root);
}

void MovieTree::printMovieInventory() {
   if (root == NULL) {
     return;
   }
   else {
     printInOrder(root);
   }
}

void MovieTree::addMovie(int ranking, string title, int year, float rating) {

  TreeNode *newNode = new TreeNode();
  newNode->titleChar = title[0];
  bool isInTree = false;

  if (root == NULL) {
    root = newNode;
    root->head = new LLMovieNode(ranking, title, year, rating);
    return;
  }

  TreeNode *current = root;
  TreeNode *parent = NULL;

  while(current != NULL) {
    parent = current;
    if (newNode->titleChar == current->titleChar) {
      isInTree = true;
      break;
    }
    else if (newNode->titleChar > (current->titleChar)) {
      current = current->rightChild;
    }
    else {
      current = current->leftChild;
    }
  }

  //Logic to add a move to a linked list in the node
  if (isInTree) {
    if (current->head == NULL) {
      current->head = new LLMovieNode(ranking, title, year, rating);
    }
    else {
      LLMovieNode *temp = current->head;
      LLMovieNode *prev = NULL;
      bool early = false;

      while (temp != NULL) {
        if (temp->title.compare(title) < 0) { //if the current nodes title comes before the title alphabetically
          cout << temp->title << " comes before " << title << endl;
          early = true;
          break;
        }
        prev = temp;
        if (temp->next == NULL) {
          break;
        }
        temp = temp->next;
      }

      LLMovieNode *nn = new LLMovieNode(ranking, title, year, rating);
      if (early) {
        cout << "adding early " << title << endl;
        nn->next = temp->next;
        temp->next = nn;
      }
      else {
        cout << "adding " << title << endl;
        nn->next = current->head;
        current->head = nn;
      }

    }
    delete newNode;
    return;
  }
  else {
    newNode->head = new LLMovieNode(ranking, title, year, rating);
  }

  if (newNode->titleChar > (parent->titleChar)) {
    parent->rightChild = newNode;
  }
  else {
    parent->leftChild = newNode;
  }
}

void MovieTree::deleteMovie(std::string title) {
  TreeNode *current = root;

  while(current != NULL) {
    if (title[0] == current->titleChar) { //Section found
      break;
    }
    else if (title[0] > current->titleChar) { //Section not found
      current = current->rightChild;
    }
    else {
      current = current->leftChild;
    }
  }
  if (current == NULL) {
    cout << "Movie: " << title << " not found, cannot delete." << endl;
  }
  else {  //Movie section found
    LLMovieNode *temp = current->head;
    LLMovieNode *prev = NULL;
    while(temp != NULL) {
      if (temp->title == title) { //Movie found
        if (prev == NULL) {
          if (temp->next == NULL) {
            current->head = NULL;
            root=deleteNode(root,current->titleChar);
            delete temp;
            return;
          }
          else {
            current->head = temp->next;
          }
        }
        else {
          if (temp->next == NULL) {
            prev->next = NULL;
          }
          else {
            prev->next = temp->next;
          }
          delete temp;
          return;
        }
      }
      prev = temp;
      temp = temp->next;
    } 
  }
}
