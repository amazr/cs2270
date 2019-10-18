#include <iostream>

using namespace std;

int main() {
    int a[] = {1,2,3,4,5};

    int* ptr = (int*)(&a[0]+5);

    cout << *(a+1) << ", " << *(ptr-1) << endl;

    return 0;
}