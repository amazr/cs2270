#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

//Commented functions are not implemented

struct wordItem {
    std::string word;
    int count;
};

//Function template for storing stop words in an array
void getStopWords(const char *ignoreWordFileName, std::string ignoreWords[]);

//Returns true if the passed word is an ignore word
bool isStopWord(std::string word, std::string ignoreWords[]);

//Doubles an array of type 'wordItem'
void arrayDouble(wordItem *&oldArray, int &capacity);

//This function returns the sum of all the occurances of each individual non-ignored word
int getTotalNumberNonStopWords(wordItem uniqueWords[], int length);

//This function sorts the array so that the most commonly occuring words are near the 0th index.
void arraySort(wordItem uniqueWords[], int length);

/*
Probability of next 10 words from rank 25
---------------------------------------
0.0033 - little
0.0033 - more
0.0032 - into
*/

void printNext10(wordItem uniqueWords[], int N, int totalNumWords);


int main(int argc, char** argv) {
    /*
        argv[1] = index N to begin output
        argv[2] = inputFile.txt
        argv[3] = ignoreFile.txt
    */

   std::string ignoreWords[50];

    if (argc < 4) {
        std::cout << "Usage: A2 <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" << std::endl;
        return 0;
    }

    //Gets words to ignore and stores them in the ar 'ignoreWords'
    getStopWords(argv[3], ignoreWords); 

    int uLength = 100;
    wordItem* uniqueWords;

    uniqueWords = new wordItem[uLength];

    std::ifstream ifs;
    ifs.open(argv[2]);

    if (!ifs.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return 0;
    }

    std::string line;
    std::string word;
    int wordCounter = 0; 
    int arDoubling = 0;

    while (getline(ifs, line)) {
       
        std::stringstream ss(line);
        std::string word;

        while(getline(ss, word, ' ')) {
            
            bool wordAlreadyFound = false;

            //Continue on an ignore word
            for (int j = 0; j < 50; j++) {
                if (word == ignoreWords[j]) {
                    wordAlreadyFound = true;
                    break;
                }
            }

            if (wordAlreadyFound) {
                continue;
            }

            for (int j = 0; j < wordCounter; j++) {
                if (uniqueWords[j].word == word) {
                    uniqueWords[j].count++;
                    wordAlreadyFound = true;
                    break;
                }
            }

            if (wordAlreadyFound) {
                continue;
            }
            else {
                uniqueWords[wordCounter].count = 1;
                uniqueWords[wordCounter].word = word;
                wordCounter++;
            }

            if (wordCounter >= uLength - 1) {
                arrayDouble(uniqueWords, uLength);
                arDoubling++;
            }
        }
    }
    
    arraySort(uniqueWords, uLength);

    std::string indexN = argv[1];

    std::cout << "Array doubled: " << arDoubling << std::endl;
    std::cout << "#" << std::endl;
    std::cout << "Unique non-common words: " << wordCounter << std::endl;
    std::cout << "#" << std::endl;
    std::cout << "Total non-common words: " << getTotalNumberNonStopWords(uniqueWords, uLength) << std::endl;
    std::cout << "#" << std::endl;
    std::cout << "Probability of next 10 words from rank " << indexN << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    printNext10(uniqueWords, stoi(indexN), getTotalNumberNonStopWords(uniqueWords, uLength));
    
}

//Functioning
void getStopWords(const char *ignoreWordFileName, std::string ignoreWords[]) {

    std::ifstream ifsIgnore;
    ifsIgnore.open(ignoreWordFileName);

    if (!ifsIgnore.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return;
    }

    std::string line;
    int wordsRead = 0;

    while(getline(ifsIgnore, line)) {

        if (wordsRead == 50) {
            break;
        }

        ignoreWords[wordsRead] = line;
        wordsRead++;
    }
}

//Functioning
bool isStopWord(std::string word, std::string ignoreWords[]) {
    for (int i = 0; i < 50; i++) {
        if (word == ignoreWords[i]) {
            return true;
        }
    }

    return false;
}

int getTotalNumberNonStopWords(wordItem uniqueWords[], int length) {
    int sum = 0;
    for (int i = 0; i < length + 1; i++) {
        sum += uniqueWords[i].count;
    }
    return sum;
}

void arrayDouble(wordItem *&oldArray, int &capacity) {
	
    int newCapacity = capacity * 2;

	wordItem *newArray = new wordItem[newCapacity];

	for (int i = 0; i < capacity; i++) {
		newArray[i] = oldArray[i];
	}

	delete [] oldArray;

	oldArray = newArray;
	capacity = newCapacity;
}

void swap(wordItem *a, wordItem *b) {
	wordItem t = *a;
	*a = *b;
	*b = t;
}

int partition(wordItem ar[], int low, int high) {
    int pivot = ar[high].count;
	int i = (low - 1);
	for (int j = low; j < high; j++) {
		if (ar[j].count >= pivot) {
			i++;
			swap(&ar[i], &ar[j]);
		}
	}
	swap(&ar[i + 1], &ar[high]);

	return i + 1;
}

void quickSort(wordItem ar[], int low, int high) {
	if (low < high) {
		int pi = partition(ar, low, high);

		quickSort(ar, low, pi - 1);
		quickSort(ar, pi + 1, high);
	}
}

void arraySort(wordItem uniqueWords[], int length) {
    quickSort(uniqueWords, 0, length - 1);
}

void printNext10(wordItem uniqueWords[], int N, int totalNumWords) {
    for (int i = N; i < N + 10; i++) {
        float probability = (float) uniqueWords[i].count / totalNumWords;   
        std::cout << std::fixed << std::setprecision(4) << probability;
        std::cout << " - " << uniqueWords[i].word << std::endl;
    }
}