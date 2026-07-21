#include <iostream>

// A large structure to clearly show memory footprint differences
struct LargeData {
    long long values[1000]; // 1000 elements * 8 bytes = 8000 bytes (approx 8 KB)
};

// 1. Pass by Value (No pointer or reference)
void processByValue(LargeData dataObj) {
    std::cout << "[Value] Address inside function: " << &dataObj << "\n";
    std::cout << "[Value] Size of object in memory: " << sizeof(dataObj) << " bytes\n";
}

// 2. Pass by Pointer
void processByPointer(LargeData* dataPtr) {
    std::cout << "[Pointer] Address stored in pointer: " << dataPtr << "\n";
    std::cout << "[Pointer] Address of the pointer variable itself: " << &dataPtr << "\n";
    std::cout << "[Pointer] Size of the pointer variable: " << sizeof(dataPtr) << " bytes\n";
    std::cout << "[Pointer] Size of the target object (*ptr): " << sizeof(*dataPtr) << " bytes\n";
    std::cout << "[Pointer] Address of original object (via pointer): " << &(*dataPtr) << "\n";
    std::cout << "[Pointer] Size of dereferenced value: " << sizeof(*dataPtr) << " bytes\n";
}

// 3. Pass by Reference
void processByReference(LargeData& dataRef) {
    std::cout << "[Reference] Address of original object (via ref): " << &dataRef << "\n";
    std::cout << "[Reference] Size reported by sizeof(ref): " << sizeof(dataRef) << " bytes\n";
}

int main() {
    LargeData originalObj;

    std::cout << "--- Original Object Details ---" << std::endl;
    std::cout << "Original object address: " << &originalObj << "\n";
    std::cout << "Original object size: " << sizeof(originalObj) << " bytes\n\n";

    std::cout << "--- 1. Testing Pass-by-Value ---" << std::endl;
    processByValue(originalObj); // Triggers a full copy (8000 bytes allocated anew)

    std::cout << "\n--- 2. Testing Pass-by-Pointer ---" << std::endl;
    processByPointer(&originalObj); // Passes only the address (8 bytes)

    std::cout << "\n--- 3. Testing Pass-by-Reference ---" << std::endl;
    processByReference(originalObj); // Passes an alias to the original object

    std::cout << "\n--- Summary of Memory Footprint ---" << std::endl;
    std::cout << "Pass-by-Value: Full copy (8000 bytes) + pointer variable (8 bytes)\n";
    std::cout << "Pass-by-Pointer: Pointer only (8 bytes) + target object (8000 bytes)\n";
    std::cout << "Pass-by-Reference: Alias only (no extra memory) + reference variable (8 bytes)\n";
    
    return 0;
}