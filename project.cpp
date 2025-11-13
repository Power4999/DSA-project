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



