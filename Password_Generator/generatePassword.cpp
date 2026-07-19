#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

string getPassword(int length){
    srand(time(0));
    string password = "";
    string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+";
    
    for(int i = 0; i < length; i++){
        int index = rand() % characters.length();
        password += characters[index];
    }
    
    return password;
}

int main(){
    srand(time(0));
    int length;

    cout << "Enter the length of your password: ";
    cin >> length;

    string passWord = getPassword(length);
    cout << "Generated Password: " << passWord << endl;

    return 0;
}