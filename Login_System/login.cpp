#include <iostream>
#include <fstream>
#include <limits>
#include <regex>
#include <sstream>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

class temp {
    private:
        string userName, email, password;
        fstream file;

        bool emailExists(const string& emailToCheck);
        string sanitizeForCsv(string input);

    public:
        bool isValidEmail(const string& email);
        void login();
        void signup();

        string getPassword(int length) {
            srand(time(0));
            string password = "";
            string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789`~|\"',.?/\\<>!@#$%^&*()_+";

            for (int i = 0; i < length; i++) {
                int index = rand() % characters.length();
                password += characters[index];
            }

            return password;
        }

        void forgotPasswd();
} obj;


void printWelcomeBanner() {
    cout << "===================" << endl;
    cout << "Login System\t  ||\n";
    cout << "===================" << endl;
    cout << "|| 1. Login\n";
    cout << "|| 2. Create Account\n";
    cout << "|| 3. Forgot Password\n";
    cout << "|| 4. Exit\n";
    cout << "===================" << endl;
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    temp loginSystem;
    char choice;
    bool running = true;

    // Wrap the menu in a loop so the program keeps running
    // until the user explicitly picks "4. Exit" instead of returning
    // after a single action.
    while (running) {
        printWelcomeBanner();

        cout << "Enter your choice: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case '1':
                cout << "Login selected" << endl;
                loginSystem.login();
                break;
            case '2':
                cout << "Create Account selected" << endl;
                loginSystem.signup();
                break;
            case '3':
                cout << "Forgot Password selected" << endl;
                loginSystem.forgotPasswd();
                break;
            case '4':
                cout << "Exiting..." << endl;
                running = false;
                break;
            default:
                cout << "Invalid choice" << endl;
        }

        cout << endl;
    }

    return 0;
}

bool temp::isValidEmail(const string& email) {
    // Regular expression pattern for general email
    const regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.\w+)+)");
    return regex_match(email, pattern);
}

string temp::sanitizeForCsv(string input) {
    replace(input.begin(), input.end(), ',', ';');
    return input;
}

bool temp::emailExists(const string& emailToCheck) {
    ifstream inFile("users.txt");
    if (!inFile.is_open()) return false;

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string storedUser, storedEmail;
        getline(ss, storedUser, ',');
        getline(ss, storedEmail, ',');

        if (storedEmail == emailToCheck) {
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}

void temp::login() {
    string inputEmail, inputPassword;
    cout << "\n-------- Login -------\n";
    cout << "Enter your registered email: ";
    cin >> inputEmail;

    // Convert input email to lowercase to match signup formatting logic
    transform(inputEmail.begin(), inputEmail.end(), inputEmail.begin(), ::tolower);

    cout << "Enter your password :: ";
    cin >> inputPassword;

    ifstream inFile("users.txt");
    if (!inFile.is_open()) {
        cout << "No user database found. Please create an account first." << endl;
        return;
    }

    string line;
    bool loggedIn = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string storedUser, storedEmail, storedPass;

        getline(ss, storedUser, ',');
        getline(ss, storedEmail, ',');
        getline(ss, storedPass, ',');

        if (inputEmail == storedEmail && inputPassword == storedPass) {
            loggedIn = true;
            cout << "\n🎇 Login successful!" << endl;
            cout << "🎉 Welcome back " << storedUser << "!" << endl;
            break;
        }
    }
    inFile.close();

    if (!loggedIn) {
        cout << "\n❌ Invalid email or password!" << endl;
    }
}

void temp::signup() {
    char pwdChoice;

    cout << "\nEnter your User Name (in full) :: ";
    getline(cin, userName);
    userName = sanitizeForCsv(userName);

    bool emailOk = false;
    do {
        cout << "Enter your email :: ";
        cin >> email;
        for (char &c : email) c = tolower(c);

        if (!isValidEmail(email)) {
            cout << "Invalid email format! Please try again." << endl << endl;
            continue;
        }

        if (emailExists(email)) {
            cout << "An account with this email already exists! Please use a different email." << endl << endl;
            continue;
        }

        emailOk = true;
    } while (!emailOk);

    bool pwdChoiceOk = false;
    do {
        cout << "\nHow do you want your password to be generated? (a)utomatic or (m)anual: ";
        cin >> pwdChoice;
        clearInputBuffer();

        switch (tolower(pwdChoice)) {
            case 'a':
                password = getPassword(10);
                pwdChoiceOk = true;
                break;
            case 'm':
                cout << "Enter your password :: ";
                cin >> password;
                clearInputBuffer();
                pwdChoiceOk = true;
                break;
            default:
                cout << "Invalid choice, please enter 'a' or 'm'." << endl;
        }
    } while (!pwdChoiceOk);

    string secretKey;
    cout << "⚒️ Enter your secret key/word/sentence: ";
    getline(cin, secretKey);
    secretKey = sanitizeForCsv(secretKey);

    // Display account details
    cout << "Your User name is :: " << userName << endl;
    cout << "Your Email is :: " << email << endl;
    cout << "Your Password is :: " << password << endl;
    cout << "Your secret key is :: " << secretKey << endl;
    cout << "NOTE: Keep your secret key safe. It is required for password recovery." << endl;

    ofstream outFile("users.txt", ios::app);

    if (outFile.is_open()) {
        outFile << userName << "," << email << "," << password << "," << secretKey << endl;
        outFile.close();
        cout << "Account created successfully!" << endl;
    } else {
        cout << "Error opening file" << endl;
    }
}

void temp::forgotPasswd() {
    string searchKey;
    cout << "\n--------- Forgot Password ---------\n";
    cout << "Enter your registered Email or Username: ";
    getline(cin, searchKey);

    string searchKeyLower = searchKey;
    transform(searchKeyLower.begin(), searchKeyLower.end(), searchKeyLower.begin(), ::tolower);

    ifstream inFile("users.txt");
    if (!inFile.is_open()) {
        cout << "❌ Error opening user database file." << endl;
        return;
    }

    string line;
    bool found = false;
    bool matchedRecordExists = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string storedUser, storedEmail, storedPassword, storedSecretKey;

        getline(ss, storedUser, ',');
        getline(ss, storedEmail, ',');
        getline(ss, storedPassword, ',');
        getline(ss, storedSecretKey, ',');

        string storedUserLower = storedUser;
        string storedEmailLower = storedEmail;
        transform(storedUserLower.begin(), storedUserLower.end(), storedUserLower.begin(), ::tolower);
        transform(storedEmailLower.begin(), storedEmailLower.end(), storedEmailLower.begin(), ::tolower);

        if (searchKeyLower == storedEmailLower || searchKeyLower == storedUserLower) {
            matchedRecordExists = true;

            cout << "What is your secret key? ";
            string inputSecretKey;
            getline(cin, inputSecretKey);

            if (inputSecretKey == storedSecretKey) {
                found = true;
                cout << "\n🎉 Your password is: " << storedPassword << endl;
            } else {
                cout << "\n❌ Invalid secret key!" << endl;
            }
            break;
        }
    }
    inFile.close();

    if (!matchedRecordExists) {
        cout << "\n❌ No account found with that email or username." << endl;
    } else if (!found) {
        cout << "\n❌ Secret key did not match our records." << endl;
    }
}