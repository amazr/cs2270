#include <iostream>
using namespace std;

void Swap (int& x, int y); 

int main() {
    int a = 1;
    int b = 2;
    Swap(a,b);
    cout << a << ", " << b << endl;
    return 0;
}

void Swap(int& x, int y) {
    int temp = x;
    x = y;
    y = temp;
}