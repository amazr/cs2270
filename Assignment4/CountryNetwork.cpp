/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
    head = NULL;
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty()
{
    if (head == NULL) {
        return true;
    }
    else {
        return false;
    }
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName) {
    if (head == NULL) {
        head = new Country;
        head->name = countryName;
        head->next = NULL;
        cout << "adding: " << countryName << " (HEAD)" << endl;
    }
    else if (previous == NULL) {
        Country *newCountry = new Country;
        newCountry->name = countryName;
        newCountry->next = head;
        head = newCountry;
        cout << "adding: " << countryName << " (HEAD)" << endl;
    }
    else {
        Country *newCountry = new Country;
        newCountry->name = countryName;
        newCountry->next = previous->next;
        previous->next = newCountry;
        cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
    }
}


/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
//Come back to this, think temp->next->name might be able to make this look nicer... WRITE IT DOWN
void CountryNetwork::deleteCountry(string countryName) {
    Country *temp = head;

    //case if the first node is the country 
    if (head->name == countryName) {
        head = head->next;
        delete temp;
        return;
    }

    while(true) {
        if (temp->next == NULL) {
            cout << "Country does not exist." << endl;
            return;
        }
        else if (temp->next->name == countryName) {
            Country *toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            return;
        }
        temp = temp->next;
    }
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup() {
    deleteEntireNetwork();
    insertCountry(head, "United States");
    insertCountry(searchNetwork("United States"), "Canada");
    insertCountry(searchNetwork("Canada"), "Brazil");
    insertCountry(searchNetwork("Brazil"), "India");
    insertCountry(searchNetwork("India"), "China");
    insertCountry(searchNetwork("China"), "Australia");
}


/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName) {
    Country *temp = head;
    while(true) {
        if (temp == NULL) {
            return NULL;
        }
        if (temp->name == countryName) {
            return temp;
        }
        else {
            if (temp->next == NULL) {
                return NULL;
            }
            else {
                temp = temp->next;
            }
        }
    }
}


/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork() {
    if (isEmpty()) {
        return;
    }

    Country *traverse = head;
    Country *toDelete = traverse;
    head = NULL;

    while(true) {
        if (traverse == NULL) {
            cout << "Deleted network" << endl;
            return;
        }
        cout << "deleting: " << toDelete->name << endl;
        traverse = traverse->next;
        delete toDelete;
        toDelete = traverse;

    }
}

/*
 * Purpose: Rotate the linked list i.e. move 'n' elements from
 * the back of the the linked to the front in the same order.
 * @param number elements to be moved from the end of the list to the beginning
 * @return none
 */
void CountryNetwork :: rotateNetwork(int n) {  

    if (isEmpty()) {
        cout << "Linked List is Empty" << endl;
        return;
    }

    int L = 0;
    Country *temp = head;
    Country *lastNode;

    while (true) {
        if (temp == NULL) {
            break;
        }
        else {
            temp = temp->next;
            L++;
        }
    }

    if (n > L || n < 1) {
        cout << "Rotate not possible" << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        lastNode = head;
        temp = head;
        while (true) {
            if (lastNode->next == NULL) {
                break;
            }
            else {
                lastNode = lastNode->next;
            }
        }
        head = head->next;
        lastNode->next = temp;
        temp->next = NULL;
    }

    cout << "Rotate Complete" << endl;
    return;
    
}

/*
 * Purpose: reverse the entire network
 * @param ptr head of list
 */
void CountryNetwork::reverseEntireNetwork() {

    if (isEmpty()) {
        return;
    }

    Country *tempHead = head;

    int L = 0;
    while (true) {
        if (tempHead->next == NULL) {
            break;
        }
        else {
            tempHead = tempHead->next;
            L++;
        }
    }

    Country *temp = tempHead;
    Country *prevTemp = head;

    for (int i = 0; i < L; i++) {
        if (temp == head) {
            break;
        }
        while (true) {
            if (prevTemp->next == temp) {
                temp->next = prevTemp;
                temp = prevTemp;
                break;
            }
            prevTemp = prevTemp->next;
        }
        prevTemp = head;
    }

    head = tempHead;
    temp->next = NULL;
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath() {
    Country *temp = head;

    cout << "== CURRENT PATH ==" << endl;

    if (temp == NULL) {
        cout << "nothing in path" << endl << "===" << endl;
        return;
    }

    while (true) {
        if (temp == NULL) {
            cout << "NULL" << endl << "===" << endl;
            return;
        }
        else {
            cout << temp->name << " -> ";
            temp = temp->next;
        }
    }
}
