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

// Function Prototypes
void changeColors(int color);
void displayMenu();

int main() {
    displayMenu();
    return 0;
}

void displayMenu() {
    int choice = -1;

    cout << endl << endl;
    cout << "********************************************************************" << endl;
    cout << "***********************  WELCOME TO MEDISYNC  **********************" << endl;
    cout << "********************************************************************" << endl;

    do {
        cout << endl;
        cout << "----------------------- MAIN MENU -----------------------" << endl;
        cout << "1. View Emergency Rooms (ER)" << endl;
        cout << "2. View Operating Rooms (OR)" << endl;
        cout << "3. View Patient Rooms" << endl;
        cout << "4. View ICU Rooms" << endl;
        cout << "5. View Imaging Rooms" << endl;
        cout << "6. View Laboratory Rooms" << endl;
        cout << "7. View Recovery Rooms" << endl;
        cout << "8. Reserve Room/Bed" << endl;
        cout << "9. Exit Program" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "Enter Choice: ";

        cin >> choice;

        switch (choice) {
        case 1:
            changeColors(14);
            cout << "Displaying Emergency Rooms..." << endl;
            changeColors(15);
            break;

        case 2:
            changeColors(14);
            cout << "Displaying Operating Rooms..." << endl;
            changeColors(15);
            break;

        case 3:
            changeColors(14);
            cout << "Displaying Patient Rooms..." << endl;
            changeColors(15);
            break;

        case 4:
            changeColors(14);
            cout << "Displaying ICU Rooms..." << endl;
            changeColors(15);
            break;

        case 5:
            changeColors(14);
            cout << "Displaying Imaging Rooms..." << endl;
            changeColors(15);
            break;

        case 6:
            changeColors(14);
            cout << "Displaying Laboratory Rooms..." << endl;
            changeColors(15);
            break;

        case 7:
            changeColors(14);
            cout << "Displaying Recovery Rooms..." << endl;
            changeColors(15);
            break;

        case 8:
            changeColors(14);
            cout << "Reserve Room/Bed option selected..." << endl;
            changeColors(15);
            break;

        case 9:
            cout << "Thank you for using MediSync. Program Terminated." << endl;
            break;

        default:
            changeColors(12);
            cout << "ERROR: Invalid Choice! Please select an option 1–9." << endl;
            changeColors(15);
        }

    } while (choice != 9);
}

// Color Function (same as CAMPiX)
void changeColors(int color) {
    static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, color);
}


//ROOOMS TO ADD SIMILAR TO HOW WE HAD HALLS AND LABS IN CAMPIX: Emergency Room (ER) Operating Room Patient Room ICU Room Imaging Room (covers X-ray/CT/MRI in general) Laboratory Room Recovery Room


