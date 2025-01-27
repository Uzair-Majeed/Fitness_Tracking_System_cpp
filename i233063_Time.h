#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include<time.h>
using namespace std;

class Time {
    int hour;
    int min;
public:
    Time() :hour(0), min(0) {}
    Time(int _hour, int _minute) : hour(_hour), min(_minute) {}
    Time(const Time& t) :hour(t.hour), min(t.min) {}

    void displayTime() const {
        cout << hour << ":";
        if (min < 10) {
            cout << "0";
        }
        else {
            cout << "";
        }
        cout << min;
    }

    void setH(int h) {
        hour = h;
    }
    void setM(int m) {
        min = m;
    }

    int getH() const {
        return hour;
    }
    int getM()const {
        return min;
    }
};