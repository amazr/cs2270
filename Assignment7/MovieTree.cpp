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

void deleteTree(TreeNode *node) { //Delete the entire tree
  if (node == NULL) return;

  if (node->leftChild != NULL && node->rightChild != NULL) {
    deleteTree(node->leftChild);
    deleteTree(node->rightChild);
  }

  delete node;
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

      while(temp->next != NULL) {
        if (temp->title.compare(title) > 0) {
          break;
        }
        prev = temp;
        temp = temp->next;
      }
      LLMovieNode *nn = new LLMovieNode(ranking, title, year, rating);
      if (prev == NULL) {
        current->head = nn;
        current->head->next = temp;
      }
      else {
        if (temp->title.compare(title) > 0) {
            prev->next = nn;
            nn->next = temp;
        }
        else {
            temp->next = nn;
        }
      }
    }

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
          current->head = NULL;
          delete temp;
          return;
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
  cout << "Movie: " << title << " not found, cannot delete." << endl;
}
