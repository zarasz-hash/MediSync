// MediSync.cpp : This file contains the 'main' function. Program execution begins and ends there.

//ROOOMS TO ADD SIMILAR TO HOW WE HAD HALLS AND LABS IN CAMPIX: Emergency Room (ER) Operating Room Patient Room ICU Room Imaging Room (covers X-ray/CT/MRI in general) Laboratory Room Recovery Room

// MediSync.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


bool login() {
    const std::string USERNAME = "admin";
    const std::string PASSWORD = "password";
    std::string inputUser, inputPass;
    std::cout << "\n--- Login ---\n";
    std::cout << "Username: ";
    std::getline(std::cin, inputUser);
    std::cout << "Password: ";
    std::getline(std::cin, inputPass);
    if (inputUser == USERNAME && inputPass == PASSWORD) {
        std::cout << "Login successful!\n";
        return true;
    } else {
        std::cout << "Invalid credentials.\n";
        return false;
    }
}

int main() {
    bool loggedIn = false;
    while (true) {
        if (!loggedIn) {
            loggedIn = login();
        } else {
            std::cout << "\n--- Main Menu ---\n";
            std::cout << "1. Logout\n2. Exit\nChoose an option: ";
            std::string choice;
            std::getline(std::cin, choice);
            if (choice == "1") {
                loggedIn = false;
                std::cout << "Logged out.\n";
            } else if (choice == "2") {
                std::cout << "Exiting...\n";
                break;
            } else {
                std::cout << "Invalid option.\n";
            }
        }
    }
    return 0;
}



//ROOOMS TO ADD SIMILAR TO HOW WE HAD HALLS AND LABS IN CAMPIX: Emergency Room (ER) Operating Room Patient Room ICU Room Imaging Room (covers X-ray/CT/MRI in general) Laboratory Room Recovery Room

