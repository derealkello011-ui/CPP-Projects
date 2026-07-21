// Linear search is an algorithm for finding the index of an element in a given array
#include <iostream>

const int MAX_SIZE = 12;
const int DEFAULT_KEY = -1;

int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

int main() {
    // Initialize array elements
    int myArray[MAX_SIZE] = {10, 15, 9, 6, 3, 4, 32, 48, 20, 12, 9, 0};

    bool runProgram = true;

    while (runProgram) {
        int key;
        std::cout << "\nThe size of the array is: " << MAX_SIZE << std::endl;
        std::cout << "ENTER YOUR ELEMENT    : ";

        // Validate user input
        if (!(std::cin >> key)) {
            std::cerr << "Invalid input. Please enter an integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        int index = linearSearch(myArray, MAX_SIZE, key);

        if (index != -1) {
            std::cout << "The index of " << key << " is: " << index << "\n";
        } else {
            std::cout << "The key '" << key << "' was NOT FOUND!\n";
        }

        // Ask user if they want to continue
        char response;
        std::cout << "Do you want to continue? (y/n): ";
        std::cin >> response;

        runProgram = (response == 'y');
    }

    return 0;
}
