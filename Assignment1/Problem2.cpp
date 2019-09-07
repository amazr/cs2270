#include <iostream>
#include <fstream>
#include <sstream>

struct Park {
    std::string parkname;
    std::string state;
    int area;
};

// length: Number of items currently stored in the array
void addPark(Park (&parks)[100], std::string parkname, std::string state, int area, int &length) {
    Park tempPark;
    tempPark.parkname = parkname;
    tempPark.state = state;
    tempPark.area = area;
    parks[length] = tempPark;
    length++;
}

// length: Number of items in the array
void printList(const Park parks[], int length) {
    for (int i = 0; i < length; i++) {
        std::cout << parks[i].parkname << " [" << parks[i].state << "] area: " << parks[i].area << std::endl;
    }
}

int main(int argc, char** argv) {
    //argv[1] == input.csv file
    //argv[2] == output.csv file
    //argv[3] == minimum area

    std::string inputName;
    std::string outputName;
    std::string minArea;

    if (argc < 4) {
        std::cout << "Not enough arguments. Please supply an input file name: ";
        std::cin >> inputName;
        std::cout << "Please supply an output file name: ";
        std::cin >> outputName;
        std::cout << "Please supply a minimum area: ";
        std::cin >> minArea;
    }
    else {
        inputName = argv[1];
        outputName = argv[2];
        minArea = argv[3];
    }

    std::ifstream ifs;
    ifs.open(inputName);

    if (!ifs.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return 0;
    }

    std::string line;
    std::string newParkName;
    std::string newState;
    int newArea;
    Park parks[100];
    int lengthCounter = 0;

    while (getline(ifs, line)) {
		
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ',');   //token = new name
        newParkName = token;
        std::getline(ss, token, ',');   //token = new state
        newState = token;
        std::getline(ss, token, ',');   //token = new area
        newArea = stoi(token);

        addPark(parks, newParkName, newState, newArea, lengthCounter);
	}

    ifs.close();

    printList(parks, lengthCounter);

    std::ofstream ofs;
    ofs.open(outputName);
    for (int i = 0; i < lengthCounter; i++) {
        if (parks[i].area < stoi(minArea)) {
            continue;
        }
        ofs << parks[i].parkname << "," << parks[i].state << "," << parks[i].area << std::endl;
    }
    ofs.close();
}




