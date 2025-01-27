#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include<time.h>
using namespace std;

string easy[3] = { "Challenge : Walk 10 Thousand Steps in 1 Day ","Challenge : Drink 8 glasses of water every day for a week.",
                    "Perform 20 minutes of stretching exercises daily." };

string medium[3] = { "Complete a 60-minute yoga session three times a week.","Cycle 50 kilometers in a single ride.",
                        "Perform 100 push-ups and 100 sit-ups within 30 minutes." };

string hard[3] = { "Complete a full marathon (26.2 miles) within 4 hours","Swim 2 kilometers non-stop in open water.",
                        "Complete a triathlon (1.5 km swim, 40 km bike, 10 km run) in under 3 hours." };
class Challenges {
    int badge;
    string challenge;
    string difficulty;
    int highScore;
    int duration;

public:

    Challenges() :badge(0), challenge(""), duration(0), difficulty(""), highScore(0) {}

    void newChallenge(string diff) {
        srand(time(0));



        if (diff == "easy") {
            challenge = easy[rand() % 3];
        }
        else if (diff == "medium") {
            challenge = medium[rand() % 3];
        }
        else if (diff == "hard") {
            challenge = hard[rand() % 3];
        }

        cout << "\nDifficulty Level -" << diff << endl;
        cout << challenge << endl;
        cout << "Upon completion in the given time period , You will recieve a Badge " << endl;
        cout << "GoodLuck! Soldier" << endl;
    }

    void completedChallenge(Regular& obj, int duration) {
        this->duration = duration;

        ofstream file("completed_Challenge.bin", ios::binary | ios::app);
        if (!file) {
            cout << "Error opening file." << endl;
            return;
        }

        string name = obj.getName();
        size_t nameSize = name.size();

        file.write(reinterpret_cast<const char*>(&nameSize), sizeof(size_t));
        file.write(name.data(), nameSize);

        file.write(reinterpret_cast<const char*>(&duration), sizeof(int));

        file.close();

        badge++;

        cout << "Congratulations! You have completed the challenge." << endl;
        cout << "You have received a badge." << endl;

        ifstream file2("highScores.bin", ios::binary);
        ofstream temp("temp.bin", ios::binary);
        if (!file2) {
            cout << "Error opening file." << endl;
            return;
        }
        if (!temp) {
            cout << "Error opening file." << endl;
            return;
        }

        while (true) {
            int score = 0;
            size_t size = 0;
            string challengeName = "";

            file2.read(reinterpret_cast<char*>(&size), sizeof(size_t));
            if (file2.eof()) {
                break;
            }
            challengeName.resize(size);
            file2.read(&challengeName[0], size);

            file2.read(reinterpret_cast<char*>(&score), sizeof(int));

            if (challengeName == challenge && duration > score) {
                temp.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
                temp.write(challengeName.data(), size);
                temp.write(reinterpret_cast<const char*>(&duration), sizeof(int));
            }
            else {
                temp.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
                temp.write(challengeName.data(), size);
                temp.write(reinterpret_cast<const char*>(&score), sizeof(int));
            }
        }

        file2.close();
        temp.close();

        remove("highScores.bin");
        if (rename("temp.bin", "highScores.bin") != 0) {
            cout << "Error renaming temp file." << endl;
        }
    }

    void viewHighScores(string difficulty) {
        this->difficulty = difficulty;

        ifstream file("highScores.bin", ios::binary);
        if (!file) {
            cout << "Error opening highScores.bin file." << endl;
            return;
        }

        cout << "High Scores for (Difficulty: " << difficulty << ")" << endl;

        while (true) {
            size_t size = 0;
            string challengeName = "";
            int score = 0;

            file.read(reinterpret_cast<char*>(&size), sizeof(size_t));
            if (file.eof()) {
                break;
            }
            challengeName.resize(size);
            file.read(&challengeName[0], size);

            file.read(reinterpret_cast<char*>(&score), sizeof(int));

            cout << " - " << challengeName << ": " << score << endl;
        }

        file.close();
    }


};