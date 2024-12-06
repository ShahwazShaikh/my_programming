#include <iostream>
using namespace std;

// Function prototype
void swap(int &x, int &y);

int main() {
    int a = 10;
    int b = 20;

    cout << "Before swap, a = " << a << " and b = " << b << endl;

    // Call the swap function
    swap(a, b);

    cout << "After swap, a = " << a << " and b = " << b << endl;

    return 0;
}

// Function definition
void swap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}
