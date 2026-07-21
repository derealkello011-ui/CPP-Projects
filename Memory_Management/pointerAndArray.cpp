#include <iostream>
using namespace std;

int main(){
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    cout << "Array values: ";
    for(int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    int *ptr = arr;
    cout << "\nArray values via pointer: ";
    for(int i = 0; i < 10; i++) {
        cout << *(ptr + i) << " ";
    }
    cout << endl;
    
    cout << "\nArray values via pointer increment: ";
    for(int i = 0; i < 10; i++) {
        cout << *ptr << " ";
        ptr++;
    }
    cout << endl;
    
    // Reset pointer to beginning for next demonstration
    ptr = arr;
    
    cout << "\nArray values via pointer arithmetic (post-increment): ";
    for(int i = 0; i < 10; i++) {
        cout << *(ptr++) << " ";
    }
    cout << endl;
    
    // Reset pointer to beginning for next demonstration
    ptr = arr;
    
    cout << "\nArray values via pointer arithmetic (pre-increment): ";
    for(int i = 0; i < 10; i++) {
        cout << *++ptr << " ";
    }
    cout << endl;
    
    return 0;
}