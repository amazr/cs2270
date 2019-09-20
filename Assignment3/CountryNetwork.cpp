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
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName)
{   
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
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
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
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
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
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
    Country *temp = head;
    bool listInitialized = true;
    bool countryFound = false;
    if (temp == NULL) {
        listInitialized = false;
        cout << "Empty list" << endl;
        return;
    }

    while (listInitialized) {

        if (temp == NULL) {
            cout << "Country not found" << endl;
            return;
        }

        if (temp->name == receiver) {
            countryFound = true;
            break;
        }
        temp = temp->next;

    }

    temp = head;
    if (!countryFound) {
        cout << "Country not found" << endl;
        return;
    }
    else {
        while(listInitialized) {
            temp->message = message;
            temp->numberMessages = temp->numberMessages + 1;
            cout << temp->name << " [# messages received: " << temp->numberMessages << "] received: " << temp->message << endl;
            if (temp->name == receiver) {
                return;
            }
            temp = temp->next;
        }
    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
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
