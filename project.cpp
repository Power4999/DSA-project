#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <sqlite3.h>
#include <fstream>
using namespace std;

// User class representing each node in the social network
class User {
public:
    string name;
    string username;
    string dob;
    string gender;
    
    User() {}
    
    User(string n, string u, string d, string g) 
        : name(n), username(u), dob(d), gender(g) {}
    
    void display() const {
        cout << "Name: " << name << endl;
        cout << "Username: @" << username << endl;
        cout << "DOB: " << dob << endl;
        cout << "Gender: " << gender << endl;
    }
};

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <sqlite3.h>
#include <fstream>
using namespace std;

// User class representing each node in the social network
class User {
public:
    string name;
    string username;
    string dob;
    string gender;
    
    User() {}
    
    User(string n, string u, string d, string g) 
        : name(n), username(u), dob(d), gender(g) {}
    
    void display() const {
        cout << "Name: " << name << endl;
        cout << "Username: @" << username << endl;
        cout << "DOB: " << dob << endl;
        cout << "Gender: " << gender << endl;
    }
};

// Authentication System
class AuthSystem {
private:
    const string CREDENTIALS_FILE = "credentials.txt";
    
public:
    // Save credentials to file
    bool saveCredentials(string username, string password) {
        ofstream file(CREDENTIALS_FILE, ios::app);
        if (!file.is_open()) {
            cerr << "❌ Error opening credentials file!" << endl;
            return false;
        }
        file << username << " " << password << endl;
        file.close();
        return true;
    }
    
    // Check if username already exists
    bool usernameExists(string username) {
        ifstream file(CREDENTIALS_FILE);
        if (!file.is_open()) return false;
        
        string user, pass;
        while (file >> user >> pass) {
            if (user == username) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
    
    // Verify login credentials
    bool verifyLogin(string username, string password) {
        ifstream file(CREDENTIALS_FILE);
        if (!file.is_open()) {
            cerr << "❌ No users registered yet!" << endl;
            return false;
        }
        
        string user, pass;
        while (file >> user >> pass) {
            if (user == username && pass == password) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
    
    // Sign up new user
    string signUp() {
        string username, password, confirmPass;
        
        cout << "\n===== SIGN UP =====" << endl;
        cout << "Enter username: ";
        cin >> username;
        
        if (usernameExists(username)) {
            cout << "❌ Username already exists! Try logging in." << endl;
            return "";
        }
        
        cout << "Enter password: ";
        cin >> password;
        cout << "Confirm password: ";
        cin >> confirmPass;
        
        if (password != confirmPass) {
            cout << "❌ Passwords don't match!" << endl;
            return "";
        }
        
        if (saveCredentials(username, password)) {
            cout << "✅ Account created successfully!" << endl;
            return username;
        }
        return "";
    }
    
    // Login existing user
    string login() {
        string username, password;
        
        cout << "\n===== LOGIN =====" << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        
        if (verifyLogin(username, password)) {
            cout << "✅ Login successful! Welcome back, @" << username << endl;
            return username;
        } else {
            cout << "❌ Invalid username or password!" << endl;
            return "";
        }
    }
};

int main() {
    SocialNetworkGraph network;
    AuthSystem auth;
    
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║   SOCIAL NETWORK GRAPH - DSA PROJECT  ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    while (true) {
        int choice;
        cout << "\n1. Login" << endl;
        cout << "2. Sign Up" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        string loggedInUser;
        
        switch (choice) {
            case 1:
                loggedInUser = auth.login();
                if (!loggedInUser.empty()) {
                    // Check if user profile exists in network
                    if (network.findUser(loggedInUser) == nullptr) {
                        string name, dob, gender;
                        cout << "\nComplete your profile:" << endl;
                        cout << "Enter full name: ";
                        cin.ignore();
                        getline(cin, name);
                        cout << "Enter DOB (YYYY-MM-DD): ";
                        cin >> dob;
                        cout << "Enter gender: ";
                        cin >> gender;
                        network.addUser(name, loggedInUser, dob, gender);
                    }
                    userMenu(network, loggedInUser);
                }
                break;
                
            case 2:
                loggedInUser = auth.signUp();
                if (!loggedInUser.empty()) {
                    string name, dob, gender;
                    cout << "\nCreate your profile:" << endl;
                    cout << "Enter full name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter DOB (YYYY-MM-DD): ";
                    cin >> dob;
                    cout << "Enter gender: ";
                    cin >> gender;
                    
                    if (network.addUser(name, loggedInUser, dob, gender)) {
                        cout << "\n✅ Profile created! Logging you in..." << endl;
                        userMenu(network, loggedInUser);
                    }
                }
                break;
                
            case 3:
                cout << "\n👋 Thank you for using Social Network! Goodbye!" << endl;
                return 0;
                
            default:
                cout << "❌ Invalid choice!" << endl;
        }
    }
    
    return 0;
}


