#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include<time.h>
using namespace std;


class ProgressAnalysis {
private:
    double totalCaloriesConsumed;
    double CaloriesBurnt;
    string mostConsumedNutrient;
    double quantity;

public:
    ProgressAnalysis() :totalCaloriesConsumed(0.0), CaloriesBurnt(0.0), mostConsumedNutrient(""), quantity(0.0) {}

    double getCaloriesBurnt() const {
        return CaloriesBurnt;
    }

    double getMostQuantity() const {
        return quantity;
    }

    string getMostConsumedNutrient() const {
        return mostConsumedNutrient;
    }

    double getCaloriesConsumed() const {
        return totalCaloriesConsumed;
    }
    void setCaloriesBurnt(double calories) {
        CaloriesBurnt = calories;
    }

    void setMostQuantity(double qty) {
        quantity = qty;
    }

    void setMostConsumed(const string& nutrient) {
        mostConsumedNutrient = nutrient;
    }

    void setCaloriesConsumed(double calories) {
        totalCaloriesConsumed = calories;
    }

    void displayGraph() {
        cout << "---------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                    Progress Analysis - Horizontal Bar Chart           " << endl;
        cout << "---------------------------------------------------------------------------------------------------------------" << endl;

        string array[3] = { "Total Calories Consumed", "Calories Burnt", mostConsumedNutrient };
        double values[3] = { totalCaloriesConsumed, CaloriesBurnt, quantity };

        for (int i = 0; i < 3; i++) {
            cout << setw(30) << left << array[i] << "|";

            int numAsterisks = 0;
            if (values[i] >= 10) {
                numAsterisks = 1;
            }
            if (values[i] >= 20) {
                numAsterisks = 2;
            }
            if (values[i] >= 30) {
                numAsterisks = 3;
            }
            if (values[i] >= 40) {
                numAsterisks = 4;
            }
            if (values[i] >= 50) {
                numAsterisks = 5;
            }
            if (values[i] >= 60) {
                numAsterisks = 6;
            }
            if (values[i] >= 70) {
                numAsterisks = 7;
            }
            if (values[i] >= 80) {
                numAsterisks = 8;
            }
            if (values[i] >= 90) {
                numAsterisks = 9;
            }
            if (values[i] >= 100) {
                numAsterisks = 10;
            }

            for (int j = 0; j < numAsterisks; j++) {
                cout << " *    ";
            }
            cout << endl;
        }

        cout << "---------------------------------------------------------------------------------------------------------------" << endl;
        cout << setw(30) << left << " " << " >=10  >=20  >=30  >=40  >=50  >=60  >=70  >=80  >=90  >=100   (units)" << endl;
        cout << "---------------------------------------------------------------------------------------------------------------" << endl;

        cout << "\n\nThe most Consumed Nutrient was : " << mostConsumedNutrient << " (" << quantity << ") units" << endl;
        cout << "The total Calorie Consumption was : " << totalCaloriesConsumed << endl;
        cout << "The total Calorie Burnt was : " << CaloriesBurnt << endl;
    }

};