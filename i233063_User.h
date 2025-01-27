#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include<time.h>
using namespace std;

class User {
protected:
    int ID;
    string name;
    string email;
    string password;
public:
    User() : ID(0), name(""), email(""), password("") {}
    User(int ID, string name, string email, string password) : ID(ID), name(name), email(email), password(password) {}

    int getID() const {
        return ID;
    }
    string getName() const {
        return name;
    }
    string getEmail() const {
        return email;
    }
    string getPassword() const {
        return password;
    }

    void setPassword(const string& pass) {
        password = pass;
    }
};