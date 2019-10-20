#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include<fstream>
#include <sstream>

void printMenu() {
    std::cout << "======Main Menu======" << std::endl;
    std::cout << "1. Find a movie" << std::endl;
    std::cout << "2. Query movies" << std::endl;
    std::cout << "3. Print the inventory" << std::endl;
    std::cout << "4. Average Rating of movies" << std::endl;
    std::cout << "5. Quit" << std::endl;
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
        std::cout << "adding movie: " << title << std::endl;
        mt.addMovieNode(stoi(ranking), title, stoi(year), stof(rating));
    }

    while(true) {
        int option;
        printMenu();
        std::cin >> option;
        switch(option) {
            case 1: {//Find movie
                std::string title;
                std::cout << "Enter title:" << std::endl;
                std::cin >> title;
                mt.findMovie(title);
                break;
            }
            case 2: {//Query movie
                int minYear;
                float minRating;
                std::cout << "Enter minimum rating:" << std::endl;
                std::cin >> minRating;
                std::cout << "Enter minimum year:" << std::endl;
                std::cin >> minYear;
                mt.queryMovies(minRating, minYear);
                break;
            }
            case 3: {//Print inventory
                mt.printMovieInventory();
                break;
            }
            case 4: {//Average rating of movies
                mt.averageRating();
                break;
            }
            case 5: {//quit
                std::cout << "Goodbye!" << std::endl; 
                break;
            }
        }
    }
}