#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include<time.h>
using namespace std;


class Workout {
    string category;
    int duration;
    string intensity;
    double caloriesBurnt;
    Time timestamp;
    string trainer;
public:

    Workout() :category(""), duration(0), intensity(""), caloriesBurnt(0.0), trainer("") {
        timestamp.setH(0);
        timestamp.setM(0);
    }

    Workout(string _category, int _duration, string _intensity, double _caloriesBurnt, const Time& _timestamp, string trainer)
        : category(_category), duration(_duration), intensity(_intensity), caloriesBurnt(_caloriesBurnt), timestamp(_timestamp), trainer(trainer) {}

    Workout(const Workout& w) :category(w.category), duration(w.duration), intensity(w.intensity), caloriesBurnt(w.caloriesBurnt), timestamp(w.timestamp), trainer(w.trainer) {}

    string getCategory() {
        return category;
    }
    string getTName() {
        return trainer;
    }
    int getDuration() const {
        return duration;
    }
    string getIntensity() {
        return intensity;
    }
    double getCaloriesBurnt() const {
        return caloriesBurnt;
    }

    Time getTimestamp() {
        return timestamp;
    }

    string getTrainer() {
        return trainer;
    }
    void displayDetails() const {
        cout << "Workout Category: " << category << endl;
        cout << "Duration: " << duration << " minutes" << endl;
        cout << "Intensity: " << intensity << endl;
        cout << "Calories Burned: " << caloriesBurnt << " kcal" << endl;
        cout << "Timestamp: ";
        timestamp.displayTime();
        cout << endl;
    }

    void newSession();//forward declared
};
