// Reference Variables create an alias for the same object
#include <iostream>

using namespace std;

int main(){
    int x = 10;
    int &y = x;

    cout << "y: " << y << endl;
    cout << "x: " << x << endl;
    cout << "Address of x: " << &x << endl;
    cout << "Address of y: " << &y << endl;
    
    y = 20;
    cout << "\nAfter modifying y (alias for x):" << endl;
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "Address of x: " << &x << endl;
    cout << "Address of y: " << &y << endl;

    x++;
    cout << "\nAfter incrementing x:" << endl;
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "Address of x: " << &x << endl;
    cout << "Address of y: " << &y << endl;

    
    return 0;
}