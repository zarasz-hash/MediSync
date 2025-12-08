// MediSync.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Purpose: This program reserves rooms for the staff so they can aid patients.


//ROOOMS TO ADD SIMILAR TO HOW WE HAD HALLS AND LABS IN CAMPIX: Emergency Room (ER) Operating Room Patient Room ICU Room Imaging Room (covers X-ray/CT/MRI in general) Laboratory Room Recovery Room

// MediSync.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// MediSync_colored.cpp : Hospital Staff & Room Management System (colored UI)

// MediSync_colored_full.cpp
// Original MediSync code with Theme A (Hospital Modern Blue) colors applied

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#ifdef _WIN32
#include <Windows.h>
#endif
using namespace std;

// Color constants (Theme A) - no white/gray
const int COLOR_HEADER = 11;    // Bright Cyan
const int COLOR_TITLE  = 3;     // Teal
const int COLOR_MENU   = 9;     // Light Blue
const int COLOR_SUCCESS= 10;    // Green
const int COLOR_ERROR  = 12;    // Red
const int COLOR_RESET  = 1;     // Blue (used as non-white reset)

// Forward declaration for color function
void changeColors(int color);

// Department class
class Department {
private:
    int deptNum;
    string deptName;
    string abbreviation;
    int floor;
    int availBeds;
public:
    Department(int num = 0, const string &name = "", const string &abbr = "", 
               int fl = 0, int beds = 0)
        : deptNum(num), deptName(name), abbreviation(abbr), floor(fl), availBeds(beds) {}

    int getDeptNum() const { return deptNum; }
    string getDeptName() const { return deptName; }
    string getAbbreviation() const { return abbreviation; }
    int getFloor() const { return floor; }
    int getAvailBeds() const { return availBeds; }

    void print() const {
        changeColors(COLOR_MENU);
        cout << "Dept #" << deptNum << " | " << deptName << " (" << abbreviation 
             << ") | Floor: " << floor << " | Available Beds: ";
        changeColors(availBeds > 0 ? COLOR_SUCCESS : COLOR_ERROR);
        cout << availBeds << "\n";
        changeColors(COLOR_RESET);
    }
};

// MedicalStaff

class Staff {
private:
    int staffID;
    string fname;
    string lname;
    int deptNum;
    string phonePwd;
    string password;
public:
    string email;  // Made public for easier assignment
public:
    Staff(int id = 0, const string &f = "", const string &l = "", int dept = 0,
          const string &phone = "", const string &pwd = "")
        : staffID(id), fname(f), lname(l), deptNum(dept), phonePwd(phone), password(pwd), email("") {}

    // Getters
    int getStaffID() const { return staffID; }
    string getFname() const { return fname; }
    string getLname() const { return lname; }
    int getDeptNum() const { return deptNum; }
    string getPhonePwd() const { return phonePwd; }
    string getEmail() const { return email; }
    string getPassword() const { return password; }

    // For quick display
    void print() const {
        changeColors(COLOR_MENU);
        cout << "StaffID: R" << staffID << " | Name: " << fname << " " << lname 
             << " | Dept: " << deptNum << " | Email: " << email << " | Phone: " << phonePwd << "\n";
        changeColors(COLOR_RESET);
    }
};

// Demo function to create and show a sample staff member
void demoStaff() {
    changeColors(COLOR_HEADER);
    cout << "\n--- Sample Staff Record ---\n";
    changeColors(COLOR_RESET);

    Staff s(1001, "Alice", "Smith", 12, "555-1234/pwd", "alice.smith@hospital.org");
    s.print();

    changeColors(COLOR_HEADER);
    cout << "---------------------------\n\n";
    changeColors(COLOR_RESET);
}

bool login() {
    const std::string USERNAME = "admin";
    const std::string PASSWORD = "password";
    std::string inputUser, inputPass;

    // header
    changeColors(COLOR_HEADER);
    std::cout << "\n--- Admin Login ---\n";
    changeColors(COLOR_RESET);

    std::cout << "Username: ";
    std::getline(std::cin, inputUser);
    std::cout << "Password: ";
    std::getline(std::cin, inputPass);
    if (inputUser == USERNAME && inputPass == PASSWORD) {
        changeColors(COLOR_SUCCESS);
        std::cout << "Login successful!\n";
        changeColors(COLOR_RESET);
        return true;
    } else {
        changeColors(COLOR_ERROR);
        std::cout << "Invalid credentials.\n";
        changeColors(COLOR_RESET);
        return false;
    }
}

// Function Prototypes
vector<Staff> loadStaffFromCSV(const string& filename);
vector<Department> loadDepartmentsFromCSV(const string& filename);
void displayStaff(const vector<Staff>& staffList);
void displayDepartments(const vector<Department>& depts);
void saveDepartmentsToCSV(const vector<Department>& depts, const string& filename);
void manageDepartments(vector<Department>& depts, const string& filename);
int authenticate(const vector<Staff>& staffList, const vector<Department>& depts);
void displayMenu();

// Load staff from CSV file
vector<Staff> loadStaffFromCSV(const string& filename) {
    vector<Staff> staffList;
    ifstream file(filename);
    
    if (!file.is_open()) {
        changeColors(COLOR_ERROR);
        cerr << "Error: Could not open file " << filename << endl;
        changeColors(COLOR_RESET);
        return staffList;
    }

    string line;
    bool firstLine = true;
    
    while (getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue; // Skip header
        }
        
        stringstream ss(line);
        string staffID, fname, lname, email, phone, password, deptStr;
        
        getline(ss, staffID, ',');
        getline(ss, fname, ',');
        getline(ss, lname, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');
        getline(ss, password, ',');
        getline(ss, deptStr, ',');
        
        if (!staffID.empty()) {
            int id = 0;
            try {
                if (staffID.size() > 0 && (staffID[0] == 'R' || staffID[0] == 'r')) {
                    id = stoi(staffID.substr(1)); // Remove 'R' prefix
                } else {
                    id = stoi(staffID);
                }
            } catch (...) { id = 0; }
            int dept = 0;
            try { dept = stoi(deptStr); } catch (...) { dept = 0; }
            Staff staff(id, fname, lname, dept, phone, password);
            staff.email = email;
            staffList.push_back(staff);
        }
    }
    
    file.close();
    return staffList;
}

// Load departments from CSV file
vector<Department> loadDepartmentsFromCSV(const string& filename) {
    vector<Department> depts;
    ifstream file(filename);
    
    if (!file.is_open()) {
        changeColors(COLOR_ERROR);
        cerr << "Error: Could not open file " << filename << endl;
        changeColors(COLOR_RESET);
        return depts;
    }

    string line;
    bool firstLine = true;
    
    while (getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue; // Skip header
        }
        
        stringstream ss(line);
        string deptNum, deptName, abbr, floor, beds;
        
        getline(ss, deptNum, ',');
        getline(ss, deptName, ',');
        getline(ss, abbr, ',');
        getline(ss, floor, ',');
        getline(ss, beds, ',');
        
        if (!deptNum.empty()) {
            int num = 0, fl = 0, availBeds = 0;
            try { num = stoi(deptNum); } catch(...) { num = 0; }
            try { fl = stoi(floor); } catch(...) { fl = 0; }
            try { availBeds = stoi(beds); } catch(...) { availBeds = 0; }
            depts.push_back(Department(num, deptName, abbr, fl, availBeds));
        }
    }
    
    file.close();
    return depts;
}

// Display staff
void displayStaff(const vector<Staff>& staffList) {
    changeColors(COLOR_HEADER);
    cout << "\n========== STAFF MEMBERS ==========\n";
    changeColors(COLOR_RESET);

    if (staffList.empty()) {
        changeColors(COLOR_ERROR);
        cout << "No staff found.\n";
        changeColors(COLOR_RESET);
        return;
    }
    
    for (const auto& staff : staffList) {
        changeColors(COLOR_MENU);
        staff.print();
    }
    changeColors(COLOR_RESET);
    cout << "==================================\n";
    changeColors(COLOR_MENU);
    cout << "Press Enter to continue...";
    changeColors(COLOR_RESET);
    cin.ignore();
    string dummy;
    getline(cin, dummy);
}

// Display departments (read-only)
void displayDepartments(const vector<Department>& depts) {
    changeColors(COLOR_HEADER);
    cout << "\n========== DEPARTMENTS ==========\n";
    changeColors(COLOR_RESET);

    if (depts.empty()) {
        changeColors(COLOR_ERROR);
        cout << "No departments found.\n";
        changeColors(COLOR_RESET);
        return;
    }
    
    for (const auto& dept : depts) {
        dept.print();
    }
    changeColors(COLOR_RESET);
    cout << "=================================\n";
}

// Save departments back to CSV
void saveDepartmentsToCSV(const vector<Department>& depts, const string& filename) {
    ofstream out(filename);
    if (!out.is_open()) {
        changeColors(COLOR_ERROR);
        cerr << "Error: could not open " << filename << " for writing." << endl;
        changeColors(COLOR_RESET);
        return;
    }
    // write header matching original file
    out << "Department Num,Department Number,Abbreviation,Floor,AvailBeds\n";
    for (const auto &d : depts) {
        out << d.getDeptNum() << "," << d.getDeptName() << "," << d.getAbbreviation() << "," << d.getFloor() << "," << d.getAvailBeds() << "\n";
    }
    out.close();
}

// Interactive department manager: view and update available beds
void manageDepartments(vector<Department>& depts, const string& filename) {
    while (true) {
        displayDepartments(depts);

        changeColors(COLOR_TITLE);
        cout << "\nDo you want to update department beds? (y/n): ";
        changeColors(COLOR_RESET);

        char c;
        cin >> c;
        if (c == 'n' || c == 'N') {
            // consume rest of line
            string rest; getline(cin, rest);
            changeColors(COLOR_MENU);
            cout << "Returning to main menu...\n";
            changeColors(COLOR_RESET);
            break;
        }
        if (c != 'y' && c != 'Y') {
            string rest; getline(cin, rest);
            changeColors(COLOR_ERROR);
            cout << "Invalid choice. Returning to departments menu." << endl;
            changeColors(COLOR_RESET);
            break;
        }
        // consume newline
        string rest; getline(cin, rest);

        changeColors(COLOR_TITLE);
        cout << "Enter Department Number (numeric ID) to update: ";
        changeColors(COLOR_RESET);

        int dnum;
        if (!(cin >> dnum)) {
            cin.clear();
            getline(cin, rest);
            changeColors(COLOR_ERROR);
            cout << "Invalid number. Aborting update." << endl;
            changeColors(COLOR_RESET);
            break;
        }
        getline(cin, rest); // consume end of line

        int idx = -1;
        for (size_t i = 0; i < depts.size(); ++i) {
            if (depts[i].getDeptNum() == dnum) { idx = (int)i; break; }
        }
        if (idx < 0) {
            changeColors(COLOR_ERROR);
            cout << "Department " << dnum << " not found." << endl;
            changeColors(COLOR_RESET);
            continue;
        }

        changeColors(COLOR_MENU);
        cout << "Selected: ";
        changeColors(depts[idx].getAvailBeds() > 0 ? COLOR_SUCCESS : COLOR_ERROR);
        depts[idx].print();
        changeColors(COLOR_RESET);

        changeColors(COLOR_TITLE);
        cout << "Choose action: 1) Mark beds free (increase)  2) Reserve bed(s) (decrease)\nEnter 1 or 2: ";
        changeColors(COLOR_RESET);

        int action;
        if (!(cin >> action)) {
            cin.clear(); getline(cin, rest);
            changeColors(COLOR_ERROR);
            cout << "Invalid action. Aborting update." << endl;
            changeColors(COLOR_RESET);
            break;
        }
        getline(cin, rest);
        changeColors(COLOR_TITLE);
        cout << "How many beds to change?: ";
        changeColors(COLOR_RESET);

        int delta;
        if (!(cin >> delta)) {
            cin.clear(); getline(cin, rest);
            changeColors(COLOR_ERROR);
            cout << "Invalid number. Aborting update." << endl;
            changeColors(COLOR_RESET);
            break;
        }
        getline(cin, rest);

        if (action == 1) {
            int newVal = depts[idx].getAvailBeds() + delta;
            depts[idx] = Department(depts[idx].getDeptNum(), depts[idx].getDeptName(), depts[idx].getAbbreviation(), depts[idx].getFloor(), newVal);
            changeColors(COLOR_SUCCESS);
            cout << "Updated. Available beds for dept " << depts[idx].getDeptNum() << " is now " << depts[idx].getAvailBeds() << ".\n";
            changeColors(COLOR_RESET);
        } else if (action == 2) {
            int newVal = depts[idx].getAvailBeds() - delta;
            if (newVal < 0) {
                changeColors(COLOR_ERROR);
                cout << "Cannot reserve that many beds; not enough available. Current: " << depts[idx].getAvailBeds() << "\n";
                changeColors(COLOR_RESET);
                continue;
            }
            depts[idx] = Department(depts[idx].getDeptNum(), depts[idx].getDeptName(), depts[idx].getAbbreviation(), depts[idx].getFloor(), newVal);
            changeColors(COLOR_SUCCESS);
            cout << "Updated. Available beds for dept " << depts[idx].getDeptNum() << " is now " << depts[idx].getAvailBeds() << ".\n";
            changeColors(COLOR_RESET);
        } else {
            changeColors(COLOR_ERROR);
            cout << "Unknown action." << endl;
            changeColors(COLOR_RESET);
            continue;
        }

        // save changes
        saveDepartmentsToCSV(depts, filename);
        changeColors(COLOR_MENU);
        cout << "Changes saved to " << filename << ".\n";
        changeColors(COLOR_RESET);
    }
}


// Authenticate user at startup
int authenticate(const vector<Staff>& staffList, const vector<Department>& depts) {
    const int maxAttempts = 3;
    for (int attempt = 1; attempt <= maxAttempts; ++attempt) {
        changeColors(COLOR_HEADER);
        cout << "\nAttempt " << attempt << " of " << maxAttempts << "\n";
        changeColors(COLOR_RESET);

        changeColors(COLOR_TITLE);
        cout << "Enter Staff ID (e.g. R1001) or Email: ";
        changeColors(COLOR_RESET);
        string identifier;
        // consume any leftover newline
        if (cin.peek() == '\n') cin.get();
        getline(cin, identifier);

        if (identifier.empty()) {
            changeColors(COLOR_ERROR);
            cout << "No identifier entered.\n";
            changeColors(COLOR_RESET);
            continue;
        }

        changeColors(COLOR_TITLE);
        cout << "Enter password: ";
        changeColors(COLOR_RESET);
        string pwd;
        getline(cin, pwd);

        bool found = false;
        // Determine if identifier looks like an ID (starts with R or r)
        bool looksLikeID = false;
        if (!identifier.empty() && (identifier[0] == 'R' || identifier[0] == 'r')) {
            looksLikeID = true;
        }

        for (size_t i = 0; i < staffList.size(); ++i) {
            if (looksLikeID) {
                string expectedID = string("R") + to_string(staffList[i].getStaffID());
                if (expectedID == identifier) {
                    found = true;
                    if (pwd == staffList[i].getPassword()) {
                        changeColors(COLOR_SUCCESS);
                        cout << "Login successful. Welcome, " << staffList[i].getFname() << " " << staffList[i].getLname() << "!\n";
                        changeColors(COLOR_RESET);
                        // Print department info from departments list if available
                        int staffDept = staffList[i].getDeptNum();
                        for (const auto &d : depts) {
                            if (d.getDeptNum() == staffDept) {
                                changeColors(COLOR_HEADER);
                                cout << "Your department: (" << staffDept << ") " << d.getDeptName() << " [" << d.getAbbreviation() << "]\n";
                                changeColors(COLOR_RESET);
                                break;
                            }
                        }
                        return (int)i;
                    } else {
                        changeColors(COLOR_ERROR);
                        cout << "Incorrect password for ID " << identifier << ".\n";
                        changeColors(COLOR_RESET);
                        break;
                    }
                }
            } else {
                // match by email
                if (!staffList[i].getEmail().empty() && staffList[i].getEmail() == identifier) {
                    found = true;
                    if (pwd == staffList[i].getPassword()) {
                        changeColors(COLOR_SUCCESS);
                        cout << "Login successful. Welcome, " << staffList[i].getFname() << " " << staffList[i].getLname() << "!\n";
                        changeColors(COLOR_RESET);
                        int staffDept2 = staffList[i].getDeptNum();
                        for (const auto &d : depts) {
                            if (d.getDeptNum() == staffDept2) {
                                changeColors(COLOR_HEADER);
                                cout << "Your department: (" << staffDept2 << ") " << d.getDeptName() << " [" << d.getAbbreviation() << "]\n";
                                changeColors(COLOR_RESET);
                                break;
                            }
                        }
                        return (int)i;
                    } else {
                        changeColors(COLOR_ERROR);
                        cout << "Incorrect password for email " << identifier << ".\n";
                        changeColors(COLOR_RESET);
                        break;
                    }
                }
            }
        }

        if (!found) {
            changeColors(COLOR_ERROR);
            cout << "No account found for '" << identifier << "'.\n";
            changeColors(COLOR_RESET);
        }

        changeColors(COLOR_ERROR);
        cout << "Authentication failed for this attempt." << endl;
        changeColors(COLOR_RESET);
    }

    changeColors(COLOR_ERROR);
    cout << "Maximum attempts reached. Exiting...\n";
    changeColors(COLOR_RESET);
    return -1;
}

int main() {
    displayMenu();
    return 0;
}

void displayMenu() {
    int choice = -1;
    vector<Staff> staffList = loadStaffFromCSV("Staff - Sheet1.csv");
    vector<Department> departments = loadDepartmentsFromCSV("Departments - Sheet1.csv");

    // Initial welcome banner shown before login
    changeColors(COLOR_HEADER);
    cout << "\n**********************************************************" << endl;
    cout << "***            Welcome to MediSync v1.0              ***" << endl;
    cout << "***  Hospital room & staff reservation management    ***" << endl;
    cout << "**********************************************************\n" << endl;
    changeColors(COLOR_RESET);

    int userIndex = authenticate(staffList, departments);
    if (userIndex < 0) {
        return; // exit if authentication failed
    }

    cout << endl << endl;
    changeColors(COLOR_HEADER);
    cout << "********************************************************************" << endl;
    cout << "***********************  WELCOME TO MEDISYNC  **********************" << endl;
    cout << "********************************************************************" << endl;
    changeColors(COLOR_RESET);

    do {
        cout << endl;
        changeColors(COLOR_TITLE);
        cout << "----------------------- MAIN MENU -----------------------" << endl;
        changeColors(COLOR_MENU);
        cout << "1. View Staff Members" << endl;
        cout << "2. View Departments" << endl;
        cout << "3. Exit Program" << endl;
        changeColors(COLOR_RESET);
        cout << "---------------------------------------------------------" << endl;
        changeColors(COLOR_TITLE);
        cout << "Enter Choice: ";
        changeColors(COLOR_RESET);

        cin >> choice;

        switch (choice) {
        case 1:
            changeColors(COLOR_MENU);
            displayStaff(staffList);
            changeColors(COLOR_RESET);
            break;

        case 2:
            changeColors(COLOR_MENU);
            manageDepartments(departments, "Departments - Sheet1.csv");
            changeColors(COLOR_RESET);
            break;

        case 3:
            changeColors(COLOR_SUCCESS);
            cout << "Thank you for using MediSync. Program Terminated." << endl;
            changeColors(COLOR_RESET);
            break;

        default:
            changeColors(COLOR_ERROR);
            cout << "ERROR: Invalid Choice! Please select an option 1–3." << endl;
            changeColors(COLOR_RESET);
        }

    } while (choice != 3);
}


// changeColors implementation
void changeColors(int color) {
    // Note: Color changing is Windows-specific (GetStdHandle/SetConsoleTextAttribute)
    // On Linux, this function will be a no-op (no color change)
    #ifdef _WIN32
    static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, color);
    #endif
}

// Encryption helper (kept from original)
void ecrypt(string entPwd) {
    //*Encrypt / Decrypt variables
    //* sepwd (string encrypted pwd) 
    //* sdpwd (string decrypted pwd) 
    //* vepwd (vector encrypted pwd)
    char temp;
    string sepwd = "";
    vector <char> vepwd;


    for (int i = 0; i < entPwd.length(); i++) {
        temp = entPwd.at(i);
        temp += 1;
        vepwd.push_back(temp);
        sepwd = sepwd + temp;

    }
    //store encrypted password in stage file
    //cout << sepwd;
}


//Encryt/Decrypt

string decrypt(string entPwd){
    //Decrypt
    char temp;
    string sdpwd = "";
    vector <char> vdpwd;

    for (int i = 0; i < entPwd.length(); i++) {
        temp = entPwd.at(i);
        temp -= 1;
        vdpwd.push_back(temp);
        sdpwd = sdpwd + temp;
    }
    return sdpwd;
    
    //use sdpwd compare to entPwd for authentication
}

//ROOOMS TO ADD SIMILAR TO HOW WE HAD HALLS AND LABS IN CAMPIX: Emergency Room (ER) Operating Room Patient Room ICU Room Imaging Room (covers X-ray/CT/MRI in general) Laboratory Room Recovery Room

