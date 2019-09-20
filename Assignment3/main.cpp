/****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
#include <locale>
// you may include more libraries as needed

// declarations for main helper-functions
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
            else if (stoi(option) == 3) {
                string message, name;
                cin.ignore();
                cout << "Enter name of the country to receive the message: " << endl;
                getline(cin, name);
                cout << "Enter the message to send: " << endl << endl;
                getline(cin, message);
                CountryNet.transmitMsg(name, message);
            }
            else if(stoi(option) == 4) {
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
            else if (stoi(option) == 5) {
                cout << "Quitting..." << endl;
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
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
