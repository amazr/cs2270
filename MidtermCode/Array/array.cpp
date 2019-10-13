#include<iostream>
#include<string>
using namespace std;

/* 
// Split 'arr' into 'even_arr' & 'odd_arr'
//  - 'arr': pointer to original array
//  - 'even_arr': pointer to even array
//  - 'odd_arr': pointer to odd array
*/
void split(int* &arr, int* &even_arr, int* &odd_arr, int size, int &even_size, int &odd_size)
{
    //Initial loop to find how many even and odd numbers there are
	for (int i = 0; i < size; i++) {
        if (arr[i]%2 == 0) {
            even_size++;
        }
        else {
            odd_size++;
        }
    }

    //Dynamically declare both arrays of the size required to store the numbers and set index counters
    even_arr = new int[even_size];
    odd_arr = new int[odd_size];
    int even_counter = 0;
    int odd_counter = 0;

    //iterate through the original array and store even and odd numbers in their correct arrays
    for (int i = 0; i < size; i++) {
        if (arr[i]%2 == 0) {
            even_arr[even_counter] = arr[i];
            even_counter++;
        }
        else {
            odd_arr[odd_counter] = arr[i];
            odd_counter++;
        }
    }

}

void printArray(int* arr, int size) {
    for(int i = 0; i<size; i++)
    {
        cout<< arr[i];
        if(i < size-1)
          cout << ", ";
    }
    cout<<endl;
}

int main(int argc, char* argv[])
{
    if(argc<2)
    {
      cout<<"usage: a.out <#>";
      return -1;
    }

	// Create input array:
    int size = stoi(argv[1]);
    int *arr = new int[size];

    cout<< "original array: ";
    for(int i = 0; i<size; i++)
    {
        arr[i] = rand()%100;
        cout<< arr[i];
        if(i < size-1)
          cout << ", ";
    }
    cout<<endl;

	// Call your function with new arrays:
    //Declare arrays and size pointers/variables
    int *even_arr, *odd_arr;
    int even_size = 0;
    int odd_size = 0;
    //Call the split function
	split(arr, even_arr, odd_arr, size, even_size, odd_size);

	// Output 
    cout << "even array: ";
    if (even_size == 0) {
        cout << "no even items in array";
    }
    for (int i = 0; i < even_size; i++) {
        cout << even_arr[i];
        if (i < even_size-1) {
            cout << ", ";
        }
    }
    cout << endl;

    cout << "odd array: ";
    if (odd_size == 0) {
        cout << "no odd items in array";
    }
    for (int i = 0; i < odd_size; i++) {
        cout << odd_arr[i];
        if (i < odd_size-1) {
            cout << ", ";
        }
    }
    cout << endl;
	// Clean up (delete)
    delete[] arr;
    delete[] even_arr;
    delete[] odd_arr;

    return 0;
}
