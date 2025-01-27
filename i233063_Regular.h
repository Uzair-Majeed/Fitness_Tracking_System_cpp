#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include<time.h>
using namespace std;

class Regular : public User {
private:



    int age;
    double weight;
    double height;
    string gender;

    int workNum;
    Workout* workouts;

    SocialMedia media;

    int num;
    Nutrition* nutritions;

    ProgressAnalysis progress;

public:
    Regular() : User(), age(0), weight(0.0), height(0.0), gender(""), workouts(nullptr), workNum(0), num(0), nutritions(nullptr), media(), progress() {}
    Regular(int ID, string name, string email, string password, int age, double weight, double height, string gender)
        : User(ID, name, email, password), age(age), weight(weight), height(height), gender(gender), workouts(nullptr), num(0), nutritions(nullptr), workNum(0), media(), progress() {}

    ~Regular() {
        delete[]workouts;
        delete[]nutritions;
    }
    int getAge() const {
        return age;
    }
    double getWeight() const {
        return weight;
    }
    double getHeight() const {
        return height;
    }
    string getGender() const {
        return gender;
    }
    SocialMedia& getMedia() {
        return media;
    }
    void operator=(const Regular& obj) {
        ID = obj.ID;
        name = obj.name;
        email = obj.email;
        password = obj.password;
        gender = obj.gender;

        age = obj.age;
        height = obj.height;
        weight = obj.weight;

        workNum = obj.workNum;

        if (workouts != nullptr) {
            workouts = new Workout[workNum];
            for (int i = 0; i < workNum; i++) {
                workouts[i] = obj.workouts[i];
            }
        }
        else {
            workouts = nullptr;
        }
    }

    void encryption(ofstream& obj)const {
        size_t nameSize = name.size();
        size_t emailSize = email.size();
        size_t passwordSize = password.size();
        size_t genderSize = gender.size();

        obj.write(reinterpret_cast<const char*>(&ID), sizeof(int));

        obj.write(reinterpret_cast<const char*>(&nameSize), sizeof(size_t));
        obj.write(name.data(), nameSize);

        obj.write(reinterpret_cast<const char*>(&emailSize), sizeof(size_t));
        obj.write(email.data(), emailSize);

        obj.write(reinterpret_cast<const char*>(&passwordSize), sizeof(size_t));
        obj.write(password.data(), passwordSize);

        obj.write(reinterpret_cast<const char*>(&age), sizeof(int));
        obj.write(reinterpret_cast<const char*>(&weight), sizeof(double));
        obj.write(reinterpret_cast<const char*>(&height), sizeof(double));

        obj.write(reinterpret_cast<const char*>(&genderSize), sizeof(size_t));
        obj.write(gender.data(), genderSize);
    }

    bool decryption(ifstream& obj) {
        size_t nameSize = 0, emailSize = 0, passwordSize = 0, genderSize = 0;

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
        obj.read(reinterpret_cast<char*>(&weight), sizeof(double));
        obj.read(reinterpret_cast<char*>(&height), sizeof(double));

        obj.read(reinterpret_cast<char*>(&genderSize), sizeof(size_t));
        gender.resize(genderSize);
        obj.read(&gender[0], genderSize);

        return true;
    }
    void updateProgressFromFiles() {
        ifstream file1("Workout.bin", ios::binary);
        if (!file1) {
            cerr << "Error opening workout file" << endl;
            return;
        }

        int id = 0;
        double totalCaloriesBurnt = 0.0;
        Workout currentWorkout;

        while (file1.read(reinterpret_cast<char*>(&id), sizeof(int))) {
            if (id == ID) {
                file1.read(reinterpret_cast<char*>(&currentWorkout), sizeof(Workout));
                totalCaloriesBurnt += currentWorkout.getCaloriesBurnt();
            }
        }
        file1.close();

        ifstream file2("nutrition.bin", ios::binary);
        if (!file2) {
            cerr << "Error opening nutrition file" << endl;
            return;
        }

        double quantity = 0.0;
        string mostConsumed = "";
        double totalCaloriesConsumed = 0.0;
        Nutrition currentNutrition;

        while (file2) {
            size_t categorySize = 0;
            if (!file2.read(reinterpret_cast<char*>(&categorySize), sizeof(size_t))) {
                break;
            }

            string category;
            category.resize(categorySize);
            file2.read(&category[0], categorySize);

            Nutrition nut;
            file2.read(reinterpret_cast<char*>(&nut), sizeof(Nutrition));

            totalCaloriesConsumed += nut.getCalories();

            if (quantity < nut.getMostQuantity()) {
                quantity = nut.getMostQuantity();
                mostConsumed = nut.getMostConsumedNutrient();
            }
        }
        file2.close();

        progress.setCaloriesBurnt(totalCaloriesBurnt);
        progress.setMostQuantity(quantity);
        progress.setMostConsumed(mostConsumed);
        progress.setCaloriesConsumed(totalCaloriesConsumed);

        progress.displayGraph();
    }


    void addWorkout(Workout& w);


    void deleteWorkout(const string& categoryToDelete);
    void updateWorkout(const string& categoryToUpdate, const Workout& updatedWorkout);

    void viewLoggedWorkouts() const {
        ifstream file("Workout.bin", ios::binary);
        if (!file) {
            cout << "Error opening workout file." << endl;
            return;
        }

        cout << "Logged Workouts:" << endl;
        int userIDFromFile = 0;
        Workout currentWorkout;
        while (file.read(reinterpret_cast<char*>(&userIDFromFile), sizeof(int))) {
            if (userIDFromFile == ID) {
                if (!file.read(reinterpret_cast<char*>(&currentWorkout), sizeof(Workout))) {
                    cout << "Error reading workout data." << endl;
                    break;
                }

                cout << "Category: " << currentWorkout.getCategory() << endl;
                cout << "Duration: " << currentWorkout.getDuration() << " minutes" << endl;
                cout << "Intensity: " << currentWorkout.getIntensity() << endl;
                cout << "Calories Burnt: " << currentWorkout.getCaloriesBurnt() << endl;
                cout << "Timestamp: " << currentWorkout.getTimestamp().getH() << ":" << currentWorkout.getTimestamp().getM() << endl;
                cout << "Trainer: " << currentWorkout.getTrainer() << endl;
                cout << "-------------------------" << endl;
            }
        }

        if (file.bad()) {
            cout << "Error reading workout file." << endl;
        }

        file.close();
    }


    void filterByIntensity(const string& intensity)const {
        ifstream file("Workout.bin", ios::binary);
        if (!file) {
            cerr << "Error opening workout file." << endl;
            return;
        }

        bool found = false;
        int userIDFromFile = 0;
        Workout currentWorkout;
        int count = 0;
        while (file.read(reinterpret_cast<char*>(&userIDFromFile), sizeof(int)) &&
            file.read(reinterpret_cast<char*>(&currentWorkout), sizeof(Workout))) {
            if (userIDFromFile == ID && currentWorkout.getIntensity() == intensity) {
                found = true;
                cout << "Workout: " << ++count << endl;
                cout << "Category: " << currentWorkout.getCategory() << endl;
                cout << "Duration: " << currentWorkout.getDuration() << " minutes" << endl;
                cout << "Calories Burnt: " << currentWorkout.getCaloriesBurnt() << endl;
                cout << "Timestamp: " << currentWorkout.getTimestamp().getH() << " : " << currentWorkout.getTimestamp().getM() << " o'clock" << endl;
            }
        }

        file.close();

        if (!found) {
            cout << "No workouts found for intensity: " << intensity << endl;
        }
    }

    void filterByDuration(int duration)const {
        ifstream file("Workout.bin", ios::binary);
        if (!file) {
            cerr << "Error opening workout file." << endl;
            return;
        }

        bool found = false;
        int userIDFromFile = 0;
        Workout currentWorkout;
        int count = 0;
        while (file.read(reinterpret_cast<char*>(&userIDFromFile), sizeof(int)) &&
            file.read(reinterpret_cast<char*>(&currentWorkout), sizeof(Workout))) {
            if (userIDFromFile == ID && currentWorkout.getDuration() == duration) {
                found = true;
                cout << "Workout: " << ++count << endl;
                cout << "Category: " << currentWorkout.getCategory() << endl;
                cout << "Intensity: " << currentWorkout.getIntensity() << endl;
                cout << "Calories Burnt: " << currentWorkout.getCaloriesBurnt() << endl;
                cout << "Timestamp: " << currentWorkout.getTimestamp().getH() << " : " << currentWorkout.getTimestamp().getM() << " o'clock" << endl;
            }
        }

        file.close();

        if (!found) {
            cout << "No workouts found for duration: " << duration << endl;
        }
    }

    void filterByCategory(const string& category)const {
        ifstream file("Workout.bin", ios::binary);
        if (!file) {
            cerr << "Error opening workout file." << endl;
            return;
        }

        bool found = false;
        int userIDFromFile = 0;
        Workout currentWorkout;
        int count = 0;
        while (file.read(reinterpret_cast<char*>(&userIDFromFile), sizeof(int)) &&
            file.read(reinterpret_cast<char*>(&currentWorkout), sizeof(Workout))) {
            if (userIDFromFile == ID && currentWorkout.getCategory() == category) {
                found = true;
                cout << "Workout: " << ++count << endl;
                cout << "Duration: " << currentWorkout.getDuration() << " minutes" << endl;
                cout << "Intensity: " << currentWorkout.getIntensity() << endl;
                cout << "Calories Burnt: " << currentWorkout.getCaloriesBurnt() << endl;
                cout << "Timestamp: " << currentWorkout.getTimestamp().getH() << " : " << currentWorkout.getTimestamp().getM() << " o'clock" << endl;
            }
        }

        file.close();

        if (!found) {
            cout << "No workouts found for category: " << category << endl;
        }
    }


    void insertNutrition(string category, const Nutrition& obj) {
        ofstream file("nutrition.bin", ios::binary | ios::app);

        if (!file) {
            cout << "Error : while opening file " << endl;
            return;
        }

        size_t categorySize = category.size();
        file.write(reinterpret_cast<const char*>(&categorySize), sizeof(size_t));
        file.write(category.data(), categorySize);

        file.write(reinterpret_cast<const char*>(&obj), sizeof(Nutrition));

        file.close();

    }

    void deleteNutrition(string cat) {
        ifstream file("nutrition.bin", ios::binary);

        if (!file) {
            cout << "Error opening file" << endl;
            return;
        }

        ofstream temp("temp.bin", ios::binary | ios::app);

        if (!temp) {
            cout << "Error creating temp file" << endl;
            file.close();
            return;

        }

        while (true) {
            size_t categorySize = 0;
            file.read(reinterpret_cast<char*>(&categorySize), sizeof(size_t));

            if (file.eof()) {
                break;
            }

            string category = "";
            category.resize(categorySize);
            file.read(&category[0], categorySize);

            Nutrition nut;

            file.read(reinterpret_cast<char*>(&nut), sizeof(Nutrition));

            if (category != cat) {
                temp.write(reinterpret_cast<const char*>(&categorySize), sizeof(size_t));
                temp.write(category.data(), categorySize);
                temp.write(reinterpret_cast<const char*>(&nut), sizeof(Nutrition));
            }

        }
        file.close();
        temp.close();

        remove("nutrition.bin");

        if (rename("temp.bin", "nutrition.bin") != 0) {
            cout << "Error renaming file" << endl;
            return;
        }
        else {
            cout << "Nutrition with category " << cat << " deleted" << endl;
        }


    }

    void updateNutrition(string cat, Nutrition& update) {
        ifstream file("nutrition.bin", ios::binary);
        if (!file) {
            cout << "Error opening workout file." << endl;
            return;
        }

        ofstream temp("temp.bin", ios::binary | ios::app);
        if (!temp) {
            cout << "Error opening workout file." << endl;
            file.close();
            return;
        }

        bool found = false;


        while (true) {
            size_t categorySize = 0;
            file.read(reinterpret_cast<char*>(&categorySize), sizeof(size_t));
            if (file.eof()) {
                break;
            }

            string category;
            category.resize(categorySize);
            file.read(&category[0], categorySize);

            Nutrition nutrition;
            file.read(reinterpret_cast<char*>(&nutrition), sizeof(Nutrition));


            if (category == cat) {
                temp.write(reinterpret_cast<const char*>(&categorySize), sizeof(size_t));
                temp.write(category.data(), categorySize);
                temp.write(reinterpret_cast<const char*>(&update), sizeof(Nutrition));
                found = true;
            }
            else {

                temp.write(reinterpret_cast<const char*>(&categorySize), sizeof(size_t));
                temp.write(category.data(), categorySize);


                temp.write(reinterpret_cast<const char*>(&nutrition), sizeof(Nutrition));
            }
        }

        file.close();
        temp.close();

        remove("nutrition.bin");

        bool result = rename("temp.bin", "nutrition.bin");

        if (result != 0) {
            cout << "Error renaming file" << endl;
            return;
        }
        else if (found) {
            cout << "Nutrition with category " << cat << " updated" << endl;
        }
        else {
            cout << "No nutrition with category " << cat << " found" << endl;
        }
    }

    double calculateCalorieConsumption(string cat) {
        ifstream file1("nutrition.bin", ios::binary);
        double totalCalories = 0.0;

        if (!file1) {
            cout << "Error opening workout file." << endl;
            return -1;
        }

        string mostConsumed = "";
        double totalCaloriesConsumed = 0.0;
        Nutrition currentNutrition;

        while (file1) {
            size_t categorySize = 0;
            if (!file1.read(reinterpret_cast<char*>(&categorySize), sizeof(size_t))) {
                break;
            }

            string category;
            category.resize(categorySize);
            file1.read(&category[0], categorySize);

            Nutrition nut;
            file1.read(reinterpret_cast<char*>(&nut), sizeof(Nutrition));

            totalCaloriesConsumed += nut.getCalories();

        }

        file1.close();

        return totalCaloriesConsumed;
    }



    void recommendations(double currWeight, Nutrition& obj) {
        double calories = obj.getCalories();
        double protein = obj.getProtein();
        double carbs = obj.getCarbs();
        double fats = obj.getFats();
        char vitamin = obj.getVitamin();
        double vitQuantity = obj.getVitQuantity();
        Time b(obj.getDate());

        cout << "\nAnalyzing your physicality and diet : " << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << "Your current weight is : " << currWeight << endl;
        obj.display();
        cout << "-------------------------------------------------------" << endl;


        string exercise[5];

        if (currWeight < 45) {
            cout << "You are extremely underWeight" << endl;
            calories += 50;
            protein += 2.0;
            carbs += 50;
            fats += 20;
            vitQuantity += 100;

            exercise[0] = "Push-ups: 3 sets of 10 reps";
            exercise[1] = "Pull-ups: 3 sets of 8 reps";
            exercise[2] = "Dumbbell Rows: 3 sets of 12 reps";
            exercise[3] = "Bicep Curls: 3 sets of 10 reps";
            exercise[4] = "Squats: 3 sets of 15 reps";

        }
        else if (currWeight >= 45 && currWeight <= 75) {
            cout << "Your weight seems fine " << endl;


            exercise[0] = "Bench Press: 4 sets of 8 reps";
            exercise[1] = "Deadlifts: 4 sets of 6 reps";
            exercise[2] = "Tricep Dips: 3 sets of 12 reps";
            exercise[3] = "Hammer Curls: 3 sets of 10 reps";
            exercise[4] = "Leg Press: 4 sets of 12 reps";
        }
        else {
            cout << "You are overweight" << endl;
            calories -= 50;
            protein -= 2.0;
            carbs -= 20;
            fats -= 10;

            exercise[0] = "Cardio: 30 minutes of jogging";
            exercise[1] = "Elliptical Trainer: 20 minutes";
            exercise[2] = "Bodyweight Squats: 3 sets of 15 reps";
            exercise[3] = "Walking Lunges: 3 sets of 12 reps per leg";
            exercise[4] = "Jump Rope: 3 sets of 1 minute";
        }
        obj.setCalories(calories);
        obj.setProtein(protein);
        obj.setCarbs(carbs);
        obj.setFats(fats);
        obj.setVitQuantity(vitQuantity);

        cout << "\nRecommended Diet Plan is :" << endl;
        cout << "-------------------------------------------------------" << endl;
        obj.display();
        cout << "-------------------------------------------------------" << endl;

        cout << "\nRecommendedExercise is : " << endl;

        cout << "-------------------------------------------------------" << endl;
        for (int i = 0; i < 5; i++) {
            cout << "Exercise : " << i + 1 << " " << exercise[i] << endl;
        }
        cout << "-------------------------------------------------------" << endl;

    }

    void viewNutrition() {
        ifstream file("nutrition.bin", ios::binary);
        if (!file) {
            cerr << "Error opening nutrition file." << endl;
            return;
        }

        cout << "Nutrition Information:" << endl;
        cout << "-------------------------------------------------------" << endl;

        while (true) {
            size_t categorySize = 0;
            file.read(reinterpret_cast<char*>(&categorySize), sizeof(size_t));
            if (file.eof()) {
                break;
            }

            string category;
            category.resize(categorySize);
            file.read(&category[0], categorySize);

            Nutrition nutrition;
            file.read(reinterpret_cast<char*>(&nutrition), sizeof(Nutrition));

            cout << "Category: " << category << endl;
            cout << "Date: " << nutrition.getDate().getH() << " : " << nutrition.getDate().getM() << " o'clock" << endl;
            cout << "Calories: " << nutrition.getCalories() << " kCal" << endl;
            cout << "Protein: " << nutrition.getProtein() << " g" << endl;
            cout << "Carbs: " << nutrition.getCarbs() << " g" << endl;
            cout << "Fats: " << nutrition.getFats() << " g" << endl;
            cout << "Vitamin: " << nutrition.getVitamin() << " - " << nutrition.getVitQuantity() << " units" << endl;
            cout << "-------------------------------------------------------" << endl;
        }

        file.close();
    }

};


bool registeration(const Regular& reg) {
    ofstream file("registered_Regular.bin", ios::binary | ios::app);
    if (!file) {
        cout << "Error: Unable to open file for writing." << endl;
        return false;
    }


    reg.encryption(file);

    file.close();
    return true;
}

bool authenticate(const string& _email, const string& _password, Regular& obj) {
    ifstream file("registered_Regular.bin", ios::binary);
    if (!file) {
        cout << "Error: Unable to open file for authentication." << endl;
        return false;
    }

    bool found = false;
    Regular temp;
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
bool resetPassword(const string& newP, const string& _email) {
    ifstream inFile("registered_Regular.bin", ios::binary);
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

    Regular temp;
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

    remove("registered_Regular.bin");
    if (rename("temp.bin", "registered_Regular.bin") != 0) {
        cout << "Error: Unable to update password file." << endl;
        return false;
    }

    return true;
}




bool forgotPassword(const string& _email) {
    string newP = "", p = "";

    do {
        cout << "\nEnter New password: ";
        cin >> newP;

        cout << "Confirm New Password: ";
        cin >> p;
    } while (p != newP);

    if (resetPassword(p, _email)) {
        cout << "Password reset successfully." << endl;
        return true;
    }
    else {
        cout << "Unable to reset password." << endl;
        return false;
    }
}
