/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}

int main(int argc, char const *argv[])
{
	ProducerConsumer PC;
	bool running = true;
	int amount;
	while(running) {
		menu();
		string option;
		cout << "";
    	cin >> option;
		switch(stoi(option)) {
			case 1:	//Add a user specified amount of items into the queue
				cout << "Enter the number of items to be produced:" << endl;
				cin >> amount;
				for (int i = 0; i < amount; i++) {
					cout << "Item" << PC.queueSize()+1 << ":" << endl;
					std::string newItem;
					cin >> newItem;
					PC.enqueue(newItem);
				}
				break;
			case 2:	//Remove a user specified amount of items from the queue
				cout << "Enter the number of items to be consumed:" << endl;
				cin >> amount;
				for (int i = 0; i < amount; i++) {
					if (PC.queueSize() == 0) {
						cout << "No more items to consume  from queue" << endl;
						break;
					}
					else {
						cout << "Consumed: " << PC.peek() << endl;
						PC.dequeue();
					}
				}
				break;
			case 3:	//Return the number of items in the queue and then exit
				cout << "Number of items in the queue:" << PC.queueSize() << endl;
				running = false;
				break;
		}
	}
}
