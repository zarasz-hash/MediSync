// MediSync.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Purpose: This program reserves rooms for the staff so they can aid patients.


//ROOOMS TO ADD SIMILAR TO HOW WE HAD HALLS AND LABS IN CAMPIX: Emergency Room (ER) Operating Room Patient Room ICU Room Imaging Room (covers X-ray/CT/MRI in general) Laboratory Room Recovery Room

// MediSync.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

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
        cout << "Dept #" << deptNum << " | " << deptName << " (" << abbreviation 
             << ") | Floor: " << floor << " | Available Beds: " << availBeds << "\n";
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
        cout << "StaffID: R" << staffID << " | Name: " << fname << " " << lname 
             << " | Dept: " << deptNum << " | Email: " << email << " | Phone: " << phonePwd << "\n";
    }
};

// Demo function to create and show a sample staff member
void demoStaff() {
    Staff s(1001, "Alice", "Smith", 12, "555-1234/pwd", "alice.smith@hospital.org");
    cout << "\n--- Sample Staff Record ---\n";
    s.print();
    cout << "---------------------------\n\n";
}




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
vector<Staff> loadStaffFromCSV(const string& filename);
vector<Department> loadDepartmentsFromCSV(const string& filename);
void displayStaff(const vector<Staff>& staffList);
void displayDepartments(const vector<Department>& depts);
void saveDepartmentsToCSV(const vector<Department>& depts, const string& filename);
void manageDepartments(vector<Department>& depts, const string& filename);
int authenticate(const vector<Staff>& staffList, const vector<Department>& depts);

// Load staff from CSV file
vector<Staff> loadStaffFromCSV(const string& filename) {
    vector<Staff> staffList;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
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
            int id = stoi(staffID.substr(1)); // Remove 'R' prefix
            int dept = stoi(deptStr);
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
        cerr << "Error: Could not open file " << filename << endl;
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
            int num = stoi(deptNum);
            int fl = stoi(floor);
            int availBeds = stoi(beds);
            depts.push_back(Department(num, deptName, abbr, fl, availBeds));
        }
    }
    
    file.close();
    return depts;
}

// Display staff
void displayStaff(const vector<Staff>& staffList) {
    cout << "\n========== STAFF MEMBERS ==========\n";
    if (staffList.empty()) {
        cout << "No staff found.\n";
        return;
    }
    
    for (const auto& staff : staffList) {
        staff.print();
    }
    cout << "==================================\n";
    cout << "Press Enter to continue...";
    cin.ignore();
    string dummy;
    getline(cin, dummy);
}

// Display departments (read-only)
void displayDepartments(const vector<Department>& depts) {
    cout << "\n========== DEPARTMENTS ==========\n";
    if (depts.empty()) {
        cout << "No departments found.\n";
        return;
    }
    
    for (const auto& dept : depts) {
        dept.print();
    }
    cout << "=================================\n";
}

// Save departments back to CSV
void saveDepartmentsToCSV(const vector<Department>& depts, const string& filename) {
    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Error: could not open " << filename << " for writing." << endl;
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
        cout << "\nDo you want to update department beds? (y/n): ";
        char c;
        cin >> c;
        if (c == 'n' || c == 'N') {
            // consume rest of line
            string rest; getline(cin, rest);
            break;
        }
        if (c != 'y' && c != 'Y') {
            string rest; getline(cin, rest);
            cout << "Invalid choice. Returning to departments menu." << endl;
            break;
        }
        // consume newline
        string rest; getline(cin, rest);

        cout << "Enter Department Number (numeric ID) to update: ";
        int dnum;
        if (!(cin >> dnum)) {
            cin.clear();
            getline(cin, rest);
            cout << "Invalid number. Aborting update." << endl;
            break;
        }
        getline(cin, rest); // consume end of line

        int idx = -1;
        for (size_t i = 0; i < depts.size(); ++i) {
            if (depts[i].getDeptNum() == dnum) { idx = (int)i; break; }
        }
        if (idx < 0) {
            cout << "Department " << dnum << " not found." << endl;
            continue;
        }

        cout << "Selected: "; depts[idx].print();
        cout << "Choose action: 1) Mark beds free (increase)  2) Reserve bed(s) (decrease)\nEnter 1 or 2: ";
        int action;
        if (!(cin >> action)) {
            cin.clear(); getline(cin, rest);
            cout << "Invalid action. Aborting update." << endl;
            break;
        }
        getline(cin, rest);
        cout << "How many beds to change?: ";
        int delta;
        if (!(cin >> delta)) {
            cin.clear(); getline(cin, rest);
            cout << "Invalid number. Aborting update." << endl;
            break;
        }
        getline(cin, rest);

        if (action == 1) {
            int newVal = depts[idx].getAvailBeds() + delta;
            // update by creating a new Department object? use setter pattern — we don't have setters, so recreate
            Department updated = depts[idx];
            // can't assign to private members, so use a workaround: create a copy and replace via constructor
            depts[idx] = Department(depts[idx].getDeptNum(), depts[idx].getDeptName(), depts[idx].getAbbreviation(), depts[idx].getFloor(), newVal);
            cout << "Updated. Available beds for dept " << depts[idx].getDeptNum() << " is now " << depts[idx].getAvailBeds() << ".\n";
        } else if (action == 2) {
            int newVal = depts[idx].getAvailBeds() - delta;
            if (newVal < 0) {
                cout << "Cannot reserve that many beds; not enough available. Current: " << depts[idx].getAvailBeds() << "\n";
                continue;
            }
            depts[idx] = Department(depts[idx].getDeptNum(), depts[idx].getDeptName(), depts[idx].getAbbreviation(), depts[idx].getFloor(), newVal);
            cout << "Updated. Available beds for dept " << depts[idx].getDeptNum() << " is now " << depts[idx].getAvailBeds() << ".\n";
        } else {
            cout << "Unknown action." << endl;
            continue;
        }

        // save changes
        saveDepartmentsToCSV(depts, filename);
        cout << "Changes saved to " << filename << ".\n";
    }
}


// Authenticate user at startup
int authenticate(const vector<Staff>& staffList, const vector<Department>& depts) {
    const int maxAttempts = 3;
    for (int attempt = 1; attempt <= maxAttempts; ++attempt) {
        cout << "\nAttempt " << attempt << " of " << maxAttempts << "\n";
        cout << "Enter Staff ID (e.g. R1001) or Email: ";
        string identifier;
        // consume any leftover newline
        if (cin.peek() == '\n') cin.get();
        getline(cin, identifier);

        if (identifier.empty()) {
            cout << "No identifier entered.\n";
            continue;
        }

        cout << "Enter password: ";
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
                        cout << "Login successful. Welcome, " << staffList[i].getFname() << " " << staffList[i].getLname() << "!\n";
                        // Print department info from departments list if available
                        int staffDept = staffList[i].getDeptNum();
                        for (const auto &d : depts) {
                            if (d.getDeptNum() == staffDept) {
                                cout << "Your department: (" << staffDept << ") " << d.getDeptName() << " [" << d.getAbbreviation() << "]\n";
                                break;
                            }
                        }
                        return (int)i;
                    } else {
                        cout << "Incorrect password for ID " << identifier << ".\n";
                        break;
                    }
                }
            } else {
                // match by email
                if (!staffList[i].getEmail().empty() && staffList[i].getEmail() == identifier) {
                    found = true;
                    if (pwd == staffList[i].getPassword()) {
                        cout << "Login successful. Welcome, " << staffList[i].getFname() << " " << staffList[i].getLname() << "!\n";
                        int staffDept2 = staffList[i].getDeptNum();
                        for (const auto &d : depts) {
                            if (d.getDeptNum() == staffDept2) {
                                cout << "Your department: (" << staffDept2 << ") " << d.getDeptName() << " [" << d.getAbbreviation() << "]\n";
                                break;
                            }
                        }
                        return (int)i;
                    } else {
                        cout << "Incorrect password for email " << identifier << ".\n";
                        break;
                    }
                }
            }
        }

        if (!found) {
            cout << "No account found for '" << identifier << "'.\n";
        }

        cout << "Authentication failed for this attempt." << endl;
    }

    cout << "Maximum attempts reached. Exiting...\n";
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
    cout << "\n**********************************************************" << endl;
    cout << "***            Welcome to MediSync v1.0              ***" << endl;
    cout << "***  Hospital room & staff reservation management    ***" << endl;
    cout << "**********************************************************\n" << endl;

    int userIndex = authenticate(staffList, departments);
    if (userIndex < 0) {
        return; // exit if authentication failed
    }

    cout << endl << endl;
    cout << "********************************************************************" << endl;
    cout << "***********************  WELCOME TO MEDISYNC  **********************" << endl;
    cout << "********************************************************************" << endl;

    do {
        cout << endl;
        cout << "----------------------- MAIN MENU -----------------------" << endl;
        cout << "1. View Staff Members" << endl;
        cout << "2. View Departments" << endl;
        cout << "3. Exit Program" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "Enter Choice: ";

        cin >> choice;

        switch (choice) {
        case 1:
            changeColors(14);
            displayStaff(staffList);
            changeColors(15);
            break;

        case 2:
            changeColors(14);
            manageDepartments(departments, "Departments - Sheet1.csv");
            changeColors(15);
            break;

        case 3:
            cout << "Thank you for using MediSync. Program Terminated." << endl;
            break;

        default:
            changeColors(12);
            cout << "ERROR: Invalid Choice! Please select an option 1–3." << endl;
            changeColors(15);
        }

    } while (choice != 3);
}


void changeColors(int color) {
    // Note: Color changing is Windows-specific (GetStdHandle/SetConsoleTextAttribute)
    // On Linux, you can use ANSI escape codes if needed
    // For now, this function does nothing on non-Windows systems
    #ifdef _WIN32
    static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, color);
    #endif
}

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








