#include "LinkedList.h"

using namespace std;

// Add a new node to the list
void LinkedList::insert(Node* prev, int newKey){

  //Check if head is Null i.e list is empty
  if(head == NULL){
    head = new Node;
    head->key = newKey;
    head->next = NULL;
  }

  // if list is not empty, look for prev and append our node there
  else if(prev == NULL)
  {
      Node* newNode = new Node;
      newNode->key = newKey;
      newNode->next = head;
      head = newNode;
  }

  else{

      Node* newNode = new Node;
      newNode->key = newKey;
      newNode->next = prev->next;
      prev->next = newNode;

    }
  }


// TODO: SILVER PROBLEM
// Delete node at a particular index
bool LinkedList::deleteAtIndex(int n)
{
  bool isDeleted = false;

  if(head == NULL){
    cout<< "List is already empty"<<endl;
    return isDeleted;
  }

  // Special case to delete the head
  if (n == 0) {
      Node *temp = head;
      temp = temp->next;
      delete head;
      head = temp;
      return true;
  }

  Node *pres = head;
	Node *prev = NULL;

  //TODO
  for (int i = 0; i < n; i++) {
    prev = pres;
    pres = pres->next;
  }

  prev->next = pres->next;
  delete pres;

  isDeleted = true;
	return isDeleted;
}

// TODO: GOLD PROBLEM
// Swap the first and last nodes (don't just swap the values)
bool LinkedList::swapFirstAndLast()
{
    bool isSwapped = false;

    if(head == NULL) {
        cout << "List is empty. Cannot swap" << endl;
        return false;
    }

    Node *temp = head;
    Node *prev = head;
    Node *last = head->next;

    while (true) {
      if (last->next == NULL) {
        break;
      }
      prev = last;
      last = last->next;
    }

    last->next = head->next;
    prev->next = head;
    head->next = NULL;
    head = last;

    isSwapped = true;

    return isSwapped;
}

// Print the keys in your list
void LinkedList::printList(){
  Node* temp = head;

  while(temp->next != NULL){
    cout<< temp->key <<" -> ";
    temp = temp->next;
  }

  cout<<temp->key<<endl;
}

// Search for a specified key and return a pointer to that node
Node* LinkedList::searchList(int key) {

    Node* ptr = head;
    while (ptr != NULL && ptr->key != key)
    {
        ptr = ptr->next;
    }
    return ptr;
}
