#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include<fstream>
#include <sstream>

void printMenu() {
    std::cout << "======Main Menu======" << std::endl;
    std::cout << "1. Print the inventory" << std::endl;
    std::cout << "2. Delete a movie" << std::endl;
    std::cout << "3. Quit" << std::endl;
}

int main(int argc, char** argv) {
    std::string inputName = argv[1];

    std::ifstream ifs;
    ifs.open(inputName);

    if (!ifs.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return 0;
    }

    MovieTree mt;

    std::string line;
    while(getline(ifs, line)) {
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ',');   //token = ranking
        std::string ranking = token;

        std::getline(ss, token, ',');   //token = title
        std::string title = token;

        std::getline(ss, token, ',');   //token = year
        std::string year = token;

        std::getline(ss, token, ',');   //token = rating
        std::string rating = token;

        mt.addMovie(stoi(ranking), title, stoi(year), stof(rating));
    }

    while(true) {
        int option;
        printMenu();
        std::cin >> option;
        std::cin.ignore();
        switch(option) {
            case 1: {//Print the inventory
                mt.printMovieInventory();
                break;
            }
            case 2: {//Delete a movie
                std::string title;
                std::cout << "Enter a movie title:" << std::endl;
                getline(std::cin, title);
                mt.deleteMovie(title);
                break;
            }
            case 3: {//Quit
                std::cout << "Goodbye!" << std::endl;   
                return 0;
                break;  
            }

        }
    }
}