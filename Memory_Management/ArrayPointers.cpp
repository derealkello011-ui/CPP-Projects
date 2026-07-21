#include <iostream>
using namespace std;

int main(){
    int myArr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    cout << "The Memory Address of the Array is: " << myArr << endl;

    for (int i = 0; i < 10; i++) {
        cout << "The Address of " << myArr[i] << " is : " << &myArr[i] << endl;
    }
    
    cout << R"(
    a. Why the array has the same memory address as its first element
        Ans: In C++, the name of an array is converted to a pointer to its first element when used in expressions. 
            Therefore, the array name and the address of its first element are the same.
    b. Why the addresses increase by 4 bytes for each subsequent element
        Ans: Each element in the array is an integer (int), which typically occupies 4 bytes in memory. 
            When the address of the next element is calculated, the pointer arithmetic adds the size of one int (4 bytes) to the current address.
    c. How does pointer arithmetic work with arrays?
        Ans: Pointer arithmetic automatically scales by the size of the pointed-to type. 
            For example, if `ptr` is an `int*`, then `ptr + 1` actually adds `sizeof(int)` bytes (typically 4 bytes) to the address, 
            pointing to the next array element.
    d. What happens when you increment a pointer vs. incrementing the value it points to?
        Ans: Incrementing a pointer (`ptr++`) changes the address stored in the pointer (advancing to the next element), 
        while incrementing the value (`(*ptr)++`) changes the actual data at that memory location without moving the pointer.
)";
}