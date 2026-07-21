#include <iostream>

using namespace std;

int main(){
    int x = 10;
    float y = 5.5;
    
    cout << "--------- INITIALLY --------------" << endl;
    cout << "The value of x is: " << x << endl;
    cout << "Address of x: " << &x << endl;
    cout << "The value of y is: " << y << endl;
    cout << "Address of y: " << &y << endl;
    cout << endl;

    // Demo Pointer
    int *ptr = &x;
    cout << "--------- POINTER DEMO --------------" << endl;
    cout << "Address stored in ptr (address of x): " << ptr << endl;
    cout << "Value via pointer (*ptr): " << *ptr << endl;
    cout << "The Address of the pointer variable is : " << &ptr << endl;
    cout << "Value via pointer to ptr (*(&ptr)): " << *(&ptr) << endl;
    cout << endl;

    // Pointer to pointer
    int **ptr2 = &ptr;
    cout << "--------- POINTER TO POINTER DEMO --------------" << endl;
    cout << "Address stored in ptr2 (address of ptr): " << ptr2 << endl;
    cout << "Value via pointer to ptr (*ptr2): " << *ptr2 << endl;
    cout << "Value via double dereference (**ptr2): " << **ptr2 << endl;
    cout << "Address of ptr2: " << &ptr2 << endl;
    cout << endl;

    // Modify value via pointer
    *ptr = 25;
    cout << "----------- MODIFICATION -------------------" << endl;
    cout << "After modifying via pointer:" << endl;
    cout << "New value of x: " << x << endl;
    cout << "Value via pointer (*ptr): " << *ptr << endl;
    cout << "Value via double dereference (**ptr2): " << **ptr2 << endl;
    cout << endl;

    // Modify value via pointer to pointer
    **ptr2 = 35;
    cout << "--------- MODIFICATION THROUGH POINTER TO POINTER --------------" << endl;
    cout << "After modifying via pointer to pointer:" << endl;
    cout << "New value of x: " << x << endl;
    cout << "Value via pointer (*ptr): " << *ptr << endl;
    cout << "Value via double dereference (**ptr2): " << **ptr2 << endl;
    cout << endl;

    return 0;
}