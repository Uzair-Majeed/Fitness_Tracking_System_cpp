#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include<time.h>
using namespace std;


class Trainer : public User {
private:
    string gender;
    string specialization;
    string successStory;
    string certification;
    double price;
    int age;
    int experience;
    int clientNum;
    Regular* clients;

public:
    Trainer() : User(), gender(""), specialization(""), successStory(""), certification(""),
        price(0.0), age(0), experience(0), clientNum(0), clients(nullptr) {}

    Trainer(int _ID, string _name, string _email, string _password, string _gender, string _specialization,
        string _successStory, string _certification, double _price, int _age, int _experience)
        : User(_ID, _name, _email, _password), gender(_gender), specialization(_specialization),
        successStory(_successStory), certification(_certification), price(_price),
        age(_age), experience(_experience), clientNum(0), clients(nullptr) {}

    ~Trainer() {
        delete[] clients;
    }

    string getSpec() {
        return specialization;
    }
    void operator=(const Trainer& obj) {

        ID = obj.ID;
        name = obj.name;
        email = obj.email;
        password = obj.password;
        gender = obj.gender;
        specialization = obj.specialization;
        successStory = obj.successStory;
        certification = obj.certification;
        price = obj.price;
        age = obj.age;
        experience = obj.experience;
        clientNum = obj.clientNum;

        if (obj.clients != nullptr) {
            clients = new Regular[clientNum];

            for (int i = 0; i < clientNum; i++) {
                clients[i] = obj.clients[i];
            }
        }
        else {
            clients = nullptr;
        }

    }

    void encryption(ofstream& obj) const {
        size_t nameSize = name.size();
        size_t emailSize = email.size();
        size_t passwordSize = password.size();
        size_t genderSize = gender.size();
        size_t specSize = specialization.size();
        size_t storySize = successStory.size();
        size_t certSize = certification.size();

        obj.write(reinterpret_cast<const char*>(&ID), sizeof(int));

        obj.write(reinterpret_cast<const char*>(&nameSize), sizeof(size_t));
        obj.write(name.data(), nameSize);

        obj.write(reinterpret_cast<const char*>(&emailSize), sizeof(size_t));
        obj.write(email.data(), emailSize);

        obj.write(reinterpret_cast<const char*>(&passwordSize), sizeof(size_t));
        obj.write(password.data(), passwordSize);

        obj.write(reinterpret_cast<const char*>(&age), sizeof(int));

        obj.write(reinterpret_cast<const char*>(&genderSize), sizeof(size_t));
        obj.write(gender.data(), genderSize);

        obj.write(reinterpret_cast<const char*>(&specSize), sizeof(size_t));
        obj.write(specialization.data(), specSize);

        obj.write(reinterpret_cast<const char*>(&storySize), sizeof(size_t));
        obj.write(successStory.data(), storySize);

        obj.write(reinterpret_cast<const char*>(&certSize), sizeof(size_t));
        obj.write(certification.data(), certSize);

        obj.write(reinterpret_cast<const char*>(&price), sizeof(double));
        obj.write(reinterpret_cast<const char*>(&experience), sizeof(int));
        obj.write(reinterpret_cast<const char*>(&clientNum), sizeof(int));
    }

    bool decryption(ifstream& obj) {
        size_t nameSize = 0, emailSize = 0, passwordSize = 0, genderSize = 0, specSize = 0, storySize = 0, certSize = 0;

        obj.read(reinterpret_cast<char*>(&ID), sizeof(int));

        obj.read(reinterpret_cast<char*>(&nameSize), sizeof(size_t));
        name.resize(nameSize);
        obj.read(&name[0], nameSize);

        obj.read(reinterpret_cast<char*>(&emailSize), sizeof(size_t));
        email.resize(emailSize);
        obj.read(&email[0], emailSize);

        obj.read(reinterpret_cast<char*>(&passwordSize), sizeof(size_t));
        password.resize(passwordSize);
        obj.read(&password[0], passwordSize);

        obj.read(reinterpret_cast<char*>(&age), sizeof(int));

        obj.read(reinterpret_cast<char*>(&genderSize), sizeof(size_t));
        gender.resize(genderSize);
        obj.read(&gender[0], genderSize);

        obj.read(reinterpret_cast<char*>(&specSize), sizeof(size_t));
        specialization.resize(specSize);
        obj.read(&specialization[0], specSize);

        obj.read(reinterpret_cast<char*>(&storySize), sizeof(size_t));
        successStory.resize(storySize);
        obj.read(&successStory[0], storySize);

        obj.read(reinterpret_cast<char*>(&certSize), sizeof(size_t));
        certification.resize(certSize);
        obj.read(&certification[0], certSize);

        obj.read(reinterpret_cast<char*>(&price), sizeof(double));
        obj.read(reinterpret_cast<char*>(&experience), sizeof(int));
        obj.read(reinterpret_cast<char*>(&clientNum), sizeof(int));

        return true;
    }


    bool addClient(Regular& c) {
        clientNum++;

        Regular* temp = new Regular[clientNum];

        for (int i = 0; i < clientNum - 1; i++) {
            temp[i] = clients[i];
        }

        temp[clientNum - 1] = c;

        delete[]clients;
        clients = temp;
        temp = nullptr;

        ofstream obj("clients.bin", ios::binary | ios::app);

        if (!obj) {
            cout << "Error: Unable to open file for writing." << endl;
            return false;
        }

        c.encryption(obj);
        obj.close();
        return true;

    }

    void viewClients() {

    }


};
bool registerTrainer(const Trainer& trainer) {
    ofstream file("registered_Trainer.bin", ios::binary | ios::app);
    if (!file) {
        cout << "Error: Unable to open file for writing." << endl;
        return false;
    }

    trainer.encryption(file);

    file.close();
    return true;
}

bool authenticateTrainer(const string& _email, const string& _password, Trainer& obj) {
    ifstream file("registered_Trainer.bin", ios::binary);
    if (!file) {
        cout << "Error: Unable to open file for authentication." << endl;
        return false;
    }

    bool found = false;
    Trainer temp;
    while (temp.decryption(file)) {
        if (temp.getEmail() == _email && temp.getPassword() == _password) {
            obj = temp;
            found = true;
            break;
        }
    }

    file.close();
    return found;
}

bool resetTpass(const string& newP, const string& _email) {
    ifstream inFile("registered_Trainer.bin", ios::binary);
    if (!inFile) {
        cout << "Error: Unable to open file for password reset." << endl;
        return false;
    }

    ofstream outFile("temp.bin", ios::binary | ios::app);
    if (!outFile) {
        cout << "Error: Unable to create temporary file." << endl;
        inFile.close();
        return false;
    }

    Trainer temp;
    bool found = false;

    while (inFile.peek() != EOF) {
        if (!temp.decryption(inFile)) {
            break;
        }


        if (temp.getEmail() == _email) {
            cout << "Checking email: " << temp.getEmail() << endl;
            temp.setPassword(newP);
            found = true;
        }
        temp.encryption(outFile);
    }

    inFile.close();
    outFile.close();

    if (!found) {
        cout << "Error: Email not found for password reset." << endl;
        remove("temp.bin");
        return false;
    }

    remove("registered_Trainer.bin");
    if (rename("temp.bin", "registered_Trainer.bin") != 0) {
        cout << "Error: Unable to update password file." << endl;
        return false;
    }

    return true;
}




bool forgotTpass(const string& _email) {
    string newP = "", p = "";
    do {
        cout << "\nEnter New password: ";
        cin.ignore();
        getline(cin, newP);

        cout << "Confirm New Password: ";
        cin.ignore();
        getline(cin, p);
    } while (p != newP);

    if (resetTpass(p, _email)) {
        cout << "Password reset successfully." << endl;
        return true;
    }
    else {
        cout << "Unable to reset password." << endl;
        return false;
    }
}

static Trainer findTrainerByName(const string& name) {

    if (name != "") {
        ifstream trainerFile("registered_Trainer.bin", ios::binary);
        if (!trainerFile) {
            cout << "Error opening trainer file." << endl;
            return Trainer();
        }

        Trainer t;
        while (t.decryption(trainerFile)) {
            if (t.getName() == name) {
                trainerFile.close();
                return t;
            }
        }
        trainerFile.close();
    }


    return Trainer();
}