#include "MovieTree.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include<fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

// MovieNode: node struct that will be stored in the MovieTree BST

//Helper functions:
void getAverageRating(MovieNode*node, int& count, float &ratings) {

  if (node == NULL) return;

  count++;
  getAverageRating(node->left, count, ratings);
  getAverageRating(node->right, count, ratings);

  ratings += node->rating;
}
void preOrderQuery(MovieNode *node, float rating, int year) {
  if(node != NULL) {
    if (node->rating >= rating && node->year > year) {
      cout << node->title << "(" << node->year << ") " << node->rating << endl;
    }
    preOrderQuery(node->left, rating, year);
    preOrderQuery(node->right, rating, year);
  }
}
void printInOrder(MovieNode *node) {
  if(node != NULL) {
    printInOrder(node->left);
    cout << "Movie: " << node->title << " " << node->rating << endl;
    printInOrder(node->right);
  }
}

void deleteTree(MovieNode *node) { //Delete the entire tree
  if (node == NULL) return;

  if (node->left != NULL && node->right != NULL) {
    deleteTree(node->left);
    deleteTree(node->right);
  }

  delete node;
}

MovieTree::MovieTree() {
  //set root MovieNode to NULL
  root = NULL;
}

MovieTree::~MovieTree() {
  //Delete the entire tree
  deleteTree(root);
}

void MovieTree::printMovieInventory() {
   //Print every node in the tree in alphabetical order
   if (root == NULL) {
     cout << "Tree is Empty. Cannot print" << endl;
   }
   else {
     printInOrder(root);
   }
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) {
  //write your code
  MovieNode *newM = new MovieNode(ranking, title, year, rating);

  if (root == NULL) {
    root = newM;
    return;
  }

  MovieNode *current = root;
  MovieNode *parent = NULL;

  while(current != NULL) {
    parent = current;
    if (newM->title.compare(current->title) > 0) {
      current = current->right;
    }
    else {
      current = current->left;
    }
  }

  if (newM->title.compare(parent->title) > 0) {
    parent->right = newM;
  }
  else {
    parent->left = newM;
  }
}

void MovieTree::findMovie(string title) {
  //write your code
  MovieNode *current = root;

  while(current != NULL) {
    if (title.compare(current->title) == 0) {
      break;
    }
    else if (title.compare(current->title) > 0) {
      current = current->right;
    }
    else {
      current = current->left;
    }
  }
  if (current == NULL) {
    cout << "Movie not found." << endl;
  }
  else {
    cout << "Movie Info:" << endl;
    cout << "==================" << endl;
    cout << "Ranking:" << current->ranking << endl;
    cout << "Title  :" << current->title << endl;
    cout << "Year   :" << current->year << endl;
    cout << "Rating :" << current->rating << endl;
  }
}

void MovieTree::queryMovies(float rating, int year) {
  //write your code
  if (root == NULL) {
    cout << "Tree is Empty. Cannot query Movies" << endl;
  }
  else {
    cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
    preOrderQuery(root, rating, year);
  }
}

void MovieTree::averageRating() {
  //write your code
  if (root == NULL) {
    cout << "Average rating:0.0" << endl;
    return;
  }

  float average = 0;
  int count = 0;
  getAverageRating(root, count, average);
  average = average / count;

  cout << "Average rating:" << average << endl;

}
