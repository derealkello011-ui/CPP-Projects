#include <iostream>
#include <string>
#include <random>
#include <limits>
#include <vector>
#include <iomanip>
#include <sstream>

class MoMoSystem {
private:
    double balance = 500.00;                 // starting simulated balance (GHS)
    const std::string pin = "1234";           // simulated MoMo PIN
    std::vector<std::string> history;         // mini statement
    std::mt19937 rng{std::random_device{}()};

    // ---------- shared UI helpers ----------

    template <typename T>
    void bannerForAll(T header, T options) {
        std::cout << "\n=================================================================\n"
                   << header
                   << "\n================================================================="
                   << options << std::endl;
    }

    void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int readChoice(int min, int max) {
        int choice;
        while (true) {
            std::cin >> choice;
            if (std::cin.eof()) return -1; // input stream exhausted, signal caller to stop
            if (std::cin.fail() || choice < min || choice > max) {
                clearInputBuffer();
                std::cout << "[!] Invalid Option (Enter from " << min << " to " << max << ")   : ";
                continue;
            }
            clearInputBuffer();
            return choice;
        }
    }

    std::string generateRef() {
        std::uniform_int_distribution<int> dist(100000, 999999);
        return "MM" + std::to_string(dist(rng));
    }

    void logTransaction(const std::string& type, double amount, const std::string& ref) {
        std::ostringstream oss;
        oss << std::left << std::setw(22) << type
            << "GHS " << std::fixed << std::setprecision(2) << std::setw(10) << amount
            << "Ref: " << ref;
        history.push_back(oss.str());
    }

    // Prompts for an amount, re-prompting until it's positive and <= balance.
    double promptAmount() {
        double amount = 0;
        while (true) {
            std::cout << "Enter Amount (GHS)  : ";
            std::cin >> amount;
            if (std::cin.eof()) return -1; // caller treats negative as "abort"
            if (std::cin.fail()) {
                clearInputBuffer();
                std::cout << "[!] Invalid amount, numbers only.\n";
                continue;
            }
            clearInputBuffer();
            if (amount <= 0) {
                std::cout << "[!] Amount must be greater than 0.\n";
            } else if (amount > balance) {
                std::cout << std::fixed << std::setprecision(2)
                           << "[!] Insufficient balance. Current balance: GHS " << balance << "\n";
            } else {
                return amount;
            }
        }
    }

    bool confirmTransaction(double amount, const std::string& recipient) {
        char choice;
        std::cout << std::fixed << std::setprecision(2)
                   << "\nConfirm: Send GHS " << amount << " to " << recipient << "? (y/n) : ";
        std::cin >> choice;
        clearInputBuffer();
        return (choice == 'y' || choice == 'Y');
    }

    void printReceipt(const std::string& ref) {
        std::cout << std::fixed << std::setprecision(2)
                   << "\n[OK] Transaction successful. Ref: " << ref
                   << "\nNew balance: GHS " << balance << "\n";
    }

    // Generic money-out flow shared by every "send/pay" style menu option,
    // so we don't repeat the same amount/confirm/deduct/log block 6 times.
    void sendMoney(const std::string& label, const std::string& promptText) {
        std::string recipient;
        std::cout << "\n" << promptText << " : ";
        std::cin >> recipient;

        double amount = promptAmount();
        if (amount < 0) return; // input stream ended
        if (!confirmTransaction(amount, recipient)) {
            std::cout << "\n[x] Transaction cancelled.\n";
            return;
        }

        balance -= amount;
        std::string ref = generateRef();
        logTransaction(label + " -> " + recipient, amount, ref);
        printReceipt(ref);
    }

    // ---------- authentication ----------

    bool authenticate() {
        int attempts = 3;
        while (attempts > 0) {
            std::string input;
            std::cout << "Enter MoMo PIN     : ";
            std::cin >> input;
            clearInputBuffer();
            if (input == pin) return true;
            attempts--;
            std::cout << "[!] Incorrect PIN. Attempts left: " << attempts << "\n";
        }
        std::cout << "\n[X] Too many failed attempts. Exiting...\n";
        return false;
    }

    // ---------- Transfer Money submenu ----------

    void transferMoney() {
        std::string header = "More Offers await on the new MoMo App";
        std::string values = R"(
    1. MoMo User
    2. Non MoMo User
    3. Send with Care
    4. Favorite
    5. Other Networks
    6. Bank Account
    7. #Next
    8. #Back)";
        int choice;
        do {
            bannerForAll(header, values);
            std::cout << "Option    : ";
            choice = readChoice(1, 8);
            if (choice == -1) { std::cout << "\n[X] Input ended.\n"; return; }

            switch (choice) {
            case 1: sendMoney("MoMo User", "Enter Mobile Number"); break;
            case 2: sendMoney("Non MoMo User", "Enter Mobile Number"); break;
            case 3: sendMoney("Send with Care", "Enter Mobile Number"); break;
            case 4: sendMoney("Favorite", "Select Favorite (Number)"); break;
            case 5: sendMoney("Other Networks", "Enter Mobile Number"); break;
            case 6: sendMoney("Bank Account", "Enter Account Number"); break;
            case 7: std::cout << "\n[i] No more offers right now.\n"; break;
            case 8: std::cout << "\n## Going Back ##\n"; break;
            }
        } while (choice != 8);
    }

    // ---------- MoMoPay & Pay Bill ----------

    void payBill() {
        std::string header = "MoMoPay & Pay Bill";
        std::string values = "\n    1. Pay Merchant (MoMoPay)\n    2. Pay Bill (ECG, Water, DSTV, etc.)\n    3. #Back";
        int choice;
        do {
            bannerForAll(header, values);
            std::cout << "Option    : ";
            choice = readChoice(1, 3);
            if (choice == -1) { std::cout << "\n[X] Input ended.\n"; return; }
            switch (choice) {
            case 1: sendMoney("MoMoPay Merchant", "Enter Merchant Code"); break;
            case 2: sendMoney("Bill Payment", "Enter Biller Code"); break;
            case 3: std::cout << "\n## Going Back ##\n"; break;
            }
        } while (choice != 3);
    }

    // ---------- Airtime & Bundles ----------

    void airtimeBundles() {
        std::string header = "Airtime & Bundles";
        std::string values = "\n    1. Buy Airtime\n    2. Buy Data Bundle\n    3. #Back";
        int choice;
        do {
            bannerForAll(header, values);
            std::cout << "Option    : ";
            choice = readChoice(1, 3);
            if (choice == -1) { std::cout << "\n[X] Input ended.\n"; return; }
            switch (choice) {
            case 1: sendMoney("Airtime Purchase", "Enter Mobile Number"); break;
            case 2: sendMoney("Data Bundle Purchase", "Enter Mobile Number"); break;
            case 3: std::cout << "\n## Going Back ##\n"; break;
            }
        } while (choice != 3);
    }

    // ---------- Cash Out ----------

    void cashOut() {
        std::string agent;
        std::cout << "\nEnter Agent Number  : ";
        std::cin >> agent;

        double amount = promptAmount();
        if (amount < 0) return; // input stream ended
        double fee = amount * 0.01; // simulated 1% cash-out fee

        if (amount + fee > balance) {
            std::cout << std::fixed << std::setprecision(2)
                       << "[!] Insufficient balance to cover amount + fee (GHS " << fee << ").\n";
            return;
        }
        if (!confirmTransaction(amount, "Agent " + agent)) {
            std::cout << "\n[x] Transaction cancelled.\n";
            return;
        }

        balance -= (amount + fee);
        std::string ref = generateRef();
        logTransaction("Cash Out -> Agent " + agent, amount, ref);
        std::cout << std::fixed << std::setprecision(2) << "Fee charged: GHS " << fee << "\n";
        printReceipt(ref);
    }

    // ---------- Financial (balance + mini statement) ----------

    void financial() {
        std::string header = "Financial Services";
        std::string values = "\n    1. Check Balance\n    2. Mini Statement\n    3. #Back";
        int choice;
        do {
            bannerForAll(header, values);
            std::cout << "Option    : ";
            choice = readChoice(1, 3);
            if (choice == -1) { std::cout << "\n[X] Input ended.\n"; return; }
            switch (choice) {
            case 1:
                std::cout << std::fixed << std::setprecision(2)
                           << "\nCurrent Balance: GHS " << balance << "\n";
                break;
            case 2:
                std::cout << "\n--- Mini Statement (last " << history.size() << ") ---\n";
                if (history.empty()) {
                    std::cout << "No transactions yet.\n";
                } else {
                    for (const auto& h : history) std::cout << h << "\n";
                }
                break;
            case 3:
                std::cout << "\n## Going Back ##\n";
                break;
            }
        } while (choice != 3);
    }

    // ---------- Main menu ----------

    void printMainMenu() {
        std::cout << "\n================================================================="
                   << R"(
 __  __       __  __         ____            _
|  \/  | ___ |  \/  | ___   / ___| _   _ ___| |_ ___ _ __ ___
| |\/| |/ _ \| |\/| |/ _ \  \___ \| | | / __| __/ _ \ '_ ` _ \
| |  | | (_) | |  | | (_) |  ___) | |_| \__ \ ||  __/ | | | | |
|_|  |_|\___/|_|  |_|\___/  |____/ \__, |___/\__\___|_| |_| |_|
                                  |___/                v2.0.0  )"
                   << "\n================================================================="
                   << "\n1) Transfer Money"
                   << "\n2) MoMoPay & Pay Bill"
                   << "\n3) Airtime & Bundles"
                   << "\n4) Allow Cash Out"
                   << "\n5) Financial"
                   << "\n6) Exit"
                   << "\nOption    : ";
    }

    void mainMenuLoop() {
        int choice;
        do {
            printMainMenu();
            choice = readChoice(1, 6);
            if (choice == -1) { std::cout << "\n[X] Input ended. Exiting...\n"; break; }
            switch (choice) {
            case 1: transferMoney(); break;
            case 2: payBill(); break;
            case 3: airtimeBundles(); break;
            case 4: cashOut(); break;
            case 5: financial(); break;
            case 6: std::cout << "\nThank you for using MoMo System. Goodbye!\n"; break;
            }
        } while (choice != 6);
    }

public:
    void run() {
        std::cout << "=================================================================\n"
                   << "                      Welcome to MoMo System\n"
                   << "=================================================================\n";
        if (!authenticate()) return;
        mainMenuLoop();
    }
};

int main() {
    MoMoSystem momoApp;
    momoApp.run();
    return 0;
}
