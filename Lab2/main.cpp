#include<iostream>
#include "swap.h"

using namespace std;
int main(int argc, char const *argv[])
{

  int foo[5] = {1, 2, 3, 4, 5};

  cout << "Addresses of elements:" << endl;
  for (int i = 0; i < 5; i++) {
    cout << "foo[" << i << "]: " << &foo[i] << " ";
  }

  cout << endl;

  cout << "Elements:" << endl;;
  //TODO Print all the eleme1nts using pointers
  for (int i = 0; i < 5; i++) {
    int* elemp = &foo[i];
    cout << "foo[" << i << "]: " << *elemp << " ";
  }

  cout << endl;

  int a,b;
  int f;
  int flag = 1;
  while(flag == 1){
    cout<<"Enter indices of elements you want to swap?"<<endl;
    cout<<"First index"<<endl;
    cin>>a;
    cout<<"Second index"<<endl;
    cin>>b;
    cout<<"Enter 0 for pass-by-value, 1 for pass-by-pointer"<<endl;
    cin>>f;

    switch (f) {
      case 0:
        // Pass by Value
        // Compare the resultant array with the array you get after passing by pointer
        cout << "Before swapping" << endl;
        for(int i = 0;i<5;i++){
          cout<<foo[i]<<" ";
        }
        cout<<endl;

        swap(foo[a],foo[b]);

        cout << "\nAfter swapping" << endl;
        for(int i = 0;i<5;i++){
          cout<<foo[i]<<" ";
        }
        cout<<endl;
        break;

      case 1:
        // Pass by pointer
        cout << "Before swapping" << endl;
        for(int i = 0;i<5;i++){
          cout<<foo[i]<<" ";
        }
        cout<<endl;

        // TODO complete the function in swap.cpp file
        swap_by_pointers(&foo[a],&foo[b]);

        cout << "\nAfter swapping" << endl;
        for(int i = 0;i<5;i++){
          cout<<foo[i]<<" ";
        }
        cout<<endl;
        break;

    }
    cout<<endl;
    cout << "Press 1 to continue else press 0"<<endl;
    cin>> flag;
  }

  cout << "Reversing the array";
  // Reverse your array
  // TODO complete the function in swap.cpp file
  reverse(foo,5);

  cout << "\nAfter reversing" << endl;
  for(int i = 0;i<5;i++){
    cout<<foo[i]<<" ";
  }
  cout<<endl;

  return 0;
}
