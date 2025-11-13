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


