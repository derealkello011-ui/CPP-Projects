#include <iostream>

using namespace std;

int main(){
    int x = 10;
    int* ptr = &x;
    
    cout << "----------- Using POINTERS ------------" << endl;
    cout << "1. Value of x: " << x << endl;
    cout << "2. Address of x: " << &x << endl;
    cout << "3. Value via pointer: " << *ptr << endl;
    cout << "4. Pointer address: " << ptr << endl;
    cout << endl;

    cout << "---------- Using REFERENCE ------------" << endl;
    int &ref = x;
    ref = 23;
    cout << "1. The reference is : " << ref << endl;
    cout << "2. The new value for x is : " << x << endl;
    cout << "3. Address of x: " << &x << endl;
    cout << "4. Value via reference: " << ref << endl;
    cout << "5. Pointer address: " << ptr << endl;
    cout << endl;

    cout << "6. Address of reference: " << &ref << endl;
    cout << "7. Value via reference: " << ref << endl;
    cout << endl;

    cout << "---------- TESTING --------------" << endl;
    int y = 42;
    int* ptr2 = &y;
    int &ref2 = y;
    
    cout << "1. Testing with new variable y = " << y << endl;
    cout << "2. Address of y: " << &y << endl;
    cout << "3. Value via pointer: " << *ptr2 << endl;
    cout << "4. Pointer address: " << ptr2 << endl;
    cout << "5. Address of reference: " << &ref2 << endl;
    cout << "6. Value via reference: " << ref2 << endl;
    cout << endl;

    return 0;
}