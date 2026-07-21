#include <iostream>

int binarySearch(int arr[], int n, int key){
        int start = 0;
        int end = n - 1;

        while (start <= end){
            int middleNum = (start + end)/2;

            if (arr[middleNum] == key){
                return middleNum;
            } else if(arr[middleNum] > key){
                end = middleNum - 1;
            } else{
                start = middleNum + 1;
            }
        }
        return -1;  
}

int main(){
    int myArray[] = {12, 34, 65, 75, 10, 30, 28, 84, 72, 49, 92, 100, 85};

    int n = sizeof(myArray)/sizeof(int);

    bool runProgram = true;

    while(runProgram){
        int key;
        std::cout << "\nThe size of the array is " << n << std::endl;
        std::cout << "ENTER YOUR ELEMENT    : ";

        // validate key
        if (!(std::cin >> key)){
            std::cout << "[x] Invalid key !!!..\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        int index = binarySearch(myArray, n, key);

        if (index!=1){
            std::cout << index << " is present at index " << "'" << key << "\n";
        } else {
            std::cout << key << " is NOT FOUND!!!\n";
        }

        // Ask user if they want to continue
        char response;
        std::cout << "Do you want to continue? (y/n): ";
        std::cin >> response;
        runProgram = (response == 'y'||response == 'Y');
    }
    return 0;
}