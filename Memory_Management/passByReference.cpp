#include <iostream>
using namespace std;

// Pass by reference
void applyTax(int& income){
    income = static_cast<int>(income * 1.2);
}

int main(){
    int salary = 50000;
    cout << "Original salary: $" << salary << endl;
    
    applyTax(salary);
    cout << "After tax: $" << salary << endl;
    
    return 0;
}