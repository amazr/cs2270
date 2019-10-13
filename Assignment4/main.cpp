/****************************************************************/
/*                   Assignment 4 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
// you may include more libraries as needed

using namespace std;

void displayMenu();

int main(int argc, char* argv[])
{
    // Object representing our network of cities.
    // (Linked list representation is in CountryNetwork)
    CountryNetwork CountryNet;

    while (true) {
        displayMenu();
        string option;
        cin >> option;

        try {
            if (stoi(option) == 1) {    //call loaddefaultsetup and then call printpath
                CountryNet.loadDefaultSetup();
                CountryNet.printPath();
            }
            else if (stoi(option) == 2) {   //Just calls the printPath function
                CountryNet.printPath();
            }
            else if(stoi(option) == 3) {    //add country
                string newCountry, prevCountry;
                cin.ignore();
                cout << "Enter a new country name: " << endl;
                getline(cin, newCountry);
                cout << "Enter the previous country name (or First): " << endl;
                getline(cin, prevCountry);

                newCountry[0] = toupper(newCountry[0]);

                while (CountryNet.searchNetwork(prevCountry) == NULL) {
                    if (prevCountry == "First") {
                        break;
                    }
                    cout << "INVALID(previous country name)...Please enter a VALID previous country name!" << endl;
                    getline(cin, prevCountry);
                }

                if (prevCountry == "First") {
                    CountryNet.insertCountry(NULL, newCountry);
                }
                else {
                    CountryNet.insertCountry(CountryNet.searchNetwork(prevCountry), newCountry);
                }

                CountryNet.printPath();
            }
            else if(stoi(option) == 4) {    //Delete a country
                string toDelete;
                cin.ignore();
                cout << "Enter a country name: " << endl;
                getline(cin, toDelete);
                CountryNet.deleteCountry(toDelete);
                CountryNet.printPath();
            }
            else if(stoi(option) == 5) {    //Reverse Network
                CountryNet.reverseEntireNetwork();
                CountryNet.printPath();
            }
            else if(stoi(option) == 6) {    //Rotate Network
                string numRotationsStr;
                int numRotations;
                cin.ignore();
                cout << "Enter the count of values to be rotated: " << endl;
                getline(cin, numRotationsStr);
                numRotations = stoi(numRotationsStr);
                CountryNet.rotateNetwork(numRotations);
                CountryNet.printPath();
            }
            else if(stoi(option) == 7) {    //Delete the network
                cout << "Network before deletion" << endl;
                CountryNet.printPath();
                CountryNet.deleteEntireNetwork();
                cout << "Network after deletion" << endl;
                CountryNet.printPath();
            }
            else if (stoi(option) == 8) {   //quit
                cout << "Quitting... cleaning up path:" << endl;
                CountryNet.printPath();
                CountryNet.deleteEntireNetwork();
                cout << "Path cleaned" << endl;
                cout << "Goodbye!" << endl;
                return 0;
            }
        }
        catch(invalid_argument) {
            cout << "Please enter a valid option." << endl;
        }
        catch(out_of_range) {
            cout << "Please enter a valid option." << endl;
        }
        catch(exception) {
            cout << "Something went horribly wrong." << endl;
        }
    }

    return 0;
}

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Add Country " << endl;
    cout << " 4. Delete Country " << endl;
    cout << " 5. Reverse Network" << endl;
    cout << " 6. Rotate Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
