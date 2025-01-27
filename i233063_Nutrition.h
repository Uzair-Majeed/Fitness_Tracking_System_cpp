#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include<time.h>
using namespace std;


class Nutrition {
private:
    Time date;
    double calories;
    double protein;
    double carbs;
    double fats;
    char vitamin;
    double vitQuantity;
public:
    Nutrition() :date(), calories(0.0), protein(0.0), carbs(0.0), fats(0.0), vitamin('\0'), vitQuantity(0.0) {}
    Nutrition(Time& obj, double calories, double protein, double carbs, double fats, char vitamin, double quantity) :date(obj), calories(calories), protein(protein), carbs(carbs), fats(fats), vitamin(vitamin), vitQuantity(quantity) {}

    double getCalories()const {
        return calories;
    }
    double getProtein()const {
        return calories;
    }
    double getCarbs()const {
        return carbs;
    }
    double getFats()const {
        return fats;
    }
    char getVitamin()const {
        return vitamin;
    }
    double getVitQuantity() const {
        return vitQuantity;
    }
    void setCalories(double c) {
        calories = c;
    }
    void setProtein(double p) {
        protein = p;
    }
    void setCarbs(double c) {
        carbs = c;
    }
    void setFats(double f) {
        fats = f;
    }
    void setVitQuantity(double v) {
        vitQuantity = v;
    }
    Time getDate() {
        return date;
    }

    void display()const {
        cout << "Calorie Intake : " << calories << " kCal" << endl;
        cout << "Protein Intake : " << protein << " g" << endl;
        cout << "CarboHydrate Intake : " << carbs << " g" << endl;
        cout << "Fats Consumption : " << fats << " g" << endl;
        cout << "Vitamin : " << vitamin << " Consumption : " << vitQuantity << " mg" << endl;
    }

    string getMostConsumedNutrient() {
        std::string nutrientNames[5] = { "Calories", "Protein", "Carbs", "Fats", "Vitamin" };
        double array[5] = { calories, protein, carbs, fats, vitQuantity };

        int maxIndex = 0;
        for (int i = 1; i < 5; ++i) {
            if (array[i] > array[maxIndex]) {
                maxIndex = i;
            }
        }

        return nutrientNames[maxIndex];
    }
    double getMostQuantity() {
        double array[5] = { calories, protein, carbs, fats, vitQuantity };

        int maxIndex = 0;
        for (int i = 1; i < 5; ++i) {
            if (array[i] > array[maxIndex]) {
                maxIndex = i;
            }
        }

        return array[maxIndex];
    }
};