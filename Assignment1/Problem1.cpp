#include <iostream>
#include <fstream>

int insertIntoSortedArray(int myArray[], int numEntries, int newValue) {
    if (numEntries == 0) {
        myArray[0] = newValue;
    }
    else {
        bool valueInserted = false;
        for (int i = 0; i < numEntries; i++) {
            if (myArray[i] >= newValue) {
                for (int j = numEntries; j > i; j--) {
                    myArray[j] = myArray[j - 1];
                }
                myArray[i] = newValue;
                valueInserted = true;
                break;
            }
        }
        if (!valueInserted) {
            myArray[numEntries] = newValue;
        }
    }
    return numEntries + 1;
}

int main(int argc, char **argv) {

    std::string fileName = argv[1];
    int myArray[100];
    int myArEntries = 0;
    std::ifstream ifs;

    ifs.open(fileName);

    if (!ifs.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
    }
    
    std::string line;

    while (getline(ifs, line)) {
		myArEntries = insertIntoSortedArray(myArray, myArEntries, stoi(line));
        std::cout << std::endl;
        for (int i = 0; i < myArEntries; i++) {
            if (i == myArEntries - 1) {
                std::cout << myArray[i];
            } else {
                std::cout << myArray[i] << ", ";
            }
        }
        std::cout << std::endl;
	}
}