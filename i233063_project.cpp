/*
            OOP-PROJECT-2024

            NAME:UZAIR MAJEED
            ROLL NUMBER : 23i-3063
            SECTION : SE-B
            COURSE-INSTRUCTOR: DR.NAVEED AHMED

            FITNESS MANAGEMENT SYSTEM
*/

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








const string groups[] = { "Fitness Group","Pakistan-Yoga Group","Cardio Veterans","Gym Rats","Gymnastics","Boxers","Pain-Lovers" };

class SocialMedia {

private:
    string userID;
    int postID;
    string posts;
    int commentsNum;
    string* comments;
    int likes;
    Time time;
    string recieverID;
    string messageContent;
    int groupID;


public:

    SocialMedia() :posts(""), comments(nullptr), likes(0), time(0, 0), messageContent(""), groupID(-1), recieverID(""), commentsNum(0), userID(""), postID(-1) {}

    void DM(const string& senderID, const string& receiverID, const string& messageContent, int h, int m) {

        ofstream file("messages.bin", ios::binary | ios::app);
        if (!file) {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        time.setH(h);
        time.setM(m);

        size_t senderSize = senderID.size();
        size_t receiverSize = receiverID.size();
        size_t contentSize = messageContent.size();

        file.write(reinterpret_cast<const char*>(&senderSize), sizeof(size_t));
        file.write(senderID.data(), senderSize);
        file.write(reinterpret_cast<const char*>(&receiverSize), sizeof(size_t));
        file.write(receiverID.data(), receiverSize);
        file.write(reinterpret_cast<const char*>(&time), sizeof(Time));
        file.write(reinterpret_cast<const char*>(&contentSize), sizeof(size_t));
        file.write(messageContent.data(), contentSize);

        file.close();

        cout << "Message sent successfully." << endl;
    }

    void viewGroupChats() {
        ifstream file("group_messages.bin", ios::binary);
        if (!file) {
            cout << "Error opening file for reading." << endl;
            return;
        }

        cout << "\n----------------------------------------------------------------" << endl;
        cout << "Previous Group Chats:" << endl;

        while (!file.eof()) {
            string senderID;
            int groupID = 0;
            Time time;
            string messageContent;

            size_t senderSize = 0;
            file.read(reinterpret_cast<char*>(&senderSize), sizeof(size_t));
            senderID.resize(senderSize);
            file.read(&senderID[0], senderSize);

            file.read(reinterpret_cast<char*>(&groupID), sizeof(int));
            file.read(reinterpret_cast<char*>(&time), sizeof(Time));

            size_t contentSize = 0;
            file.read(reinterpret_cast<char*>(&contentSize), sizeof(size_t));
            messageContent.resize(contentSize);
            file.read(&messageContent[0], contentSize);

            cout << "Sender: " << senderID << endl;
            cout << "Group ID: " << groups[groupID] << endl;
            cout << "Time: " << time.getH() << ":" << time.getM() << endl;
            cout << "Message: " << messageContent << endl;
            cout << "\n----------------------------------------------------------------" << endl;
        }

        file.close();
    }

    void viewDirectMessages() {
        ifstream file("messages.bin", ios::binary);
        if (!file) {
            cout << "Error opening file for reading." << endl;
            return;
        }
        cout << "\n----------------------------------------------------------------" << endl;

        cout << "Previous Direct Messages:" << endl;

        while (!file.eof()) {
            string senderID, receiverID;
            Time time;
            string messageContent;

            size_t senderSize = 0, receiverSize = 0;
            file.read(reinterpret_cast<char*>(&senderSize), sizeof(size_t));
            senderID.resize(senderSize);
            file.read(&senderID[0], senderSize);

            file.read(reinterpret_cast<char*>(&receiverSize), sizeof(size_t));
            receiverID.resize(receiverSize);
            file.read(&receiverID[0], receiverSize);

            file.read(reinterpret_cast<char*>(&time), sizeof(Time));

            size_t contentSize = 0;
            file.read(reinterpret_cast<char*>(&contentSize), sizeof(size_t));
            messageContent.resize(contentSize);
            file.read(&messageContent[0], contentSize);

            cout << "Sender: " << senderID << endl;
            cout << "Receiver: " << receiverID << endl;
            cout << "Time: " << time.getH() << ":" << time.getM() << endl;
            cout << "Message: " << messageContent << endl;
            cout << "\n----------------------------------------------------------------" << endl;
        }

        file.close();
    }


    void messageInGroup(const string& senderID, int groupID, const string& messageContent, int h, int m) {

        ofstream file("group_messages.bin", ios::binary | ios::app);
        if (!file) {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        time.setH(h);
        time.setM(m);

        size_t senderSize = senderID.size();
        size_t contentSize = messageContent.size();

        file.write(reinterpret_cast<const char*>(&senderSize), sizeof(size_t));
        file.write(senderID.data(), senderSize);
        file.write(reinterpret_cast<const char*>(&groupID), sizeof(int));
        file.write(reinterpret_cast<const char*>(&time), sizeof(Time));
        file.write(reinterpret_cast<const char*>(&contentSize), sizeof(size_t));
        file.write(messageContent.data(), contentSize);


        file.close();

        cout << "Message sent to group successfully." << endl;
    }



    void post(string userID, const string& content, int h, int m) {

        ofstream file("posts.bin", ios::binary | ios::app);
        if (!file) {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        postID++;
        comments = nullptr;
        likes = 0;
        commentsNum = 0;
        time.setH(h);
        time.setM(m);



        file.write(reinterpret_cast<const char*>(&postID), sizeof(postID));

        size_t userSize = userID.size();
        file.write(reinterpret_cast<const char*>(&userSize), sizeof(size_t));
        file.write(userID.data(), userSize);
        file.write(reinterpret_cast<const char*>(&time), sizeof(Time));
        size_t contentSize = content.size();

        file.write(reinterpret_cast<const char*>(&contentSize), sizeof(size_t));
        file.write(content.data(), contentSize);

        file.close();

        cout << "Post created successfully." << endl;
        cout << "Post ID is " << postID << endl;
    }
    void likePost(int postID) {
        ifstream file("likes.bin", ios::binary);
        ofstream temp("temp.bin", ios::binary | ios::app);
        if (!file || !temp) {
            cerr << "Error opening file for reading and writing." << endl;
            return;
        }

        bool postFound = false;
        while (!file.eof()) {
            int readPostID = 0;
            file.read(reinterpret_cast<char*>(&readPostID), sizeof(int));

            if (file.eof()) {
                break;
            }

            if (readPostID == postID) {
                postFound = true;

                int existingLikes = 0;
                file.read(reinterpret_cast<char*>(&existingLikes), sizeof(int));

                existingLikes++;

                temp.write(reinterpret_cast<const char*>(&postID), sizeof(int));
                temp.write(reinterpret_cast<const char*>(&existingLikes), sizeof(int));
            }
            else {

                temp.write(reinterpret_cast<const char*>(&readPostID), sizeof(int));
                int existingLikes = 0;
                file.read(reinterpret_cast<char*>(&existingLikes), sizeof(int));
                temp.write(reinterpret_cast<const char*>(&existingLikes), sizeof(int));
            }
        }

        if (!postFound) {
            temp.write(reinterpret_cast<const char*>(&postID), sizeof(int));
            int initialLikes = 1;
            temp.write(reinterpret_cast<const char*>(&initialLikes), sizeof(int));
        }

        file.close();
        temp.close();

        remove("likes.bin");

        bool f = rename("temp.bin", "likes.bin");

        cout << "Post with ID " << postID << " liked successfully." << endl;
    }


    void commentOnPost(string userID, int postID, const string& newComment) {

        ofstream file("comments.bin", ios::binary | ios::app);
        if (!file) {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        file.write(reinterpret_cast<const char*>(&postID), sizeof(postID));


        size_t commentSize = newComment.size();
        file.write(reinterpret_cast<const char*>(&commentSize), sizeof(size_t));


        file.write(newComment.data(), commentSize);

        cout << "Comment added to post with ID " << postID << " successfully." << endl;
    }

    void viewComments(int postID) {

        ifstream file("comments.bin", ios::binary);
        if (!file) {
            cout << "Error opening file for reading." << endl;
            return;
        }
        cout << "\n----------------------------------------------------------------" << endl;

        bool postFound = false;

        int count = 0;

        while (!file.eof()) {
            int ID = 0;
            file.read(reinterpret_cast<char*>(&ID), sizeof(int));

            if (file.eof()) {
                break;
            }

            if (ID == postID) {
                postFound = true;
                cout << "\nComments under Post ID: " << postID << endl;


                while (true) {
                    size_t commentSize = 0;
                    file.read(reinterpret_cast<char*>(&commentSize), sizeof(size_t));

                    if (commentSize == 0) {
                        break;
                    }

                    string comment;
                    comment.resize(commentSize);
                    file.read(&comment[0], commentSize);
                    cout << "Comment " << ++count << " : ";
                    cout << comment << endl;
                }
                break;
            }
            else {

                size_t commentSize = 0;
                file.read(reinterpret_cast<char*>(&commentSize), sizeof(size_t));
                file.ignore(commentSize);
            }
            cout << "\n----------------------------------------------------------------" << endl;

        }

        if (!postFound) {
            cout << "No comments found for Post ID: " << postID << endl;
        }


        file.close();
    }



    void viewPosts() {
        ifstream file("posts.bin", ios::binary);
        if (!file) {
            cout << "Error opening file for reading." << endl;
            return;
        }
        cout << "\n----------------------------------------------------------------" << endl;

        cout << "Posts:" << endl;
        while (true) {

            int postID = 0;
            file.read(reinterpret_cast<char*>(&postID), sizeof(int));


            if (file.eof()) {
                break;
            }


            size_t userIDSize = 0;
            file.read(reinterpret_cast<char*>(&userIDSize), sizeof(size_t));

            string userID;
            userID.resize(userIDSize);
            file.read(&userID[0], userIDSize);

            Time postTime(0, 0);
            file.read(reinterpret_cast<char*>(&postTime), sizeof(Time));


            size_t contentSize = 0;
            file.read(reinterpret_cast<char*>(&contentSize), sizeof(size_t));



            string content = "";
            content.resize(contentSize);
            file.read(&content[0], contentSize);

            cout << "User ID: " << userID << endl;
            cout << "Post ID: " << postID << endl;
            cout << "Time: " << postTime.getH() << ":" << postTime.getM() << endl;
            cout << "Content: " << content << endl;
            cout << "\n----------------------------------------------------------------" << endl;
        }

        file.close();
    }



};


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


void Workout::newSession() {

    int h = 0, m = 0;

    cout << "\nEnter category of workout (e.g., cardio, strength training, yoga, etc.) : ";
    cin.ignore();
    getline(cin, category);


    do {
        cout << "Enter the  Duration of the workout session in minutes : ";
        cin >> duration;
    } while (duration <= 0);

    cout << "Intensity level of the workout (e.g., low, medium, high) : ";
    cin.ignore();
    getline(cin, intensity);

    do {
        cout << "Enter the Calories burnt during the workout session: ";
        cin >> caloriesBurnt;
    } while (caloriesBurnt < 0);



    cout << "Enter TimeStamp : " << endl;

    do {
        cout << "Enter Hour : ";
        cin >> h;
    } while (h < 0 || h>24);
    do {
        cout << "Enter minutes : ";
        cin >> m;
    } while (m < 0 || m > 59);


    timestamp.setH(h);
    timestamp.setM(m);


    char ch = '\0';
    do {
        cout << "\nLastly,Do You want a trainer for this workout : ";
        cin >> ch;
    } while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N');

    if (ch == 'y' || ch == 'Y') {

        ifstream obj("registered_Trainer.bin", ios::binary);
        if (!obj) {
            cout << "Error opening trainer file." << endl;
            return;
        }

        Trainer t;
        cout << "\nAvailable Trainers:" << endl;
        while (!obj.eof()) {
            if (t.decryption(obj)) {
                cout << "- " << t.getName() << "----" << t.getSpec() << endl;
            }
        }
        obj.close();


        cout << "Enter trainer name You want : ";
        cin.ignore();
        getline(cin, trainer);

        cout << "Trainer " << trainer << " Selected " << endl;

    }
    else {
        trainer = "";
    }

}



void Regular::addWorkout(Workout& w) {
    ofstream obj("Workout.bin", ios::binary | ios::app);
    if (!obj) {
        cout << "Error opening workout file." << endl;
        return;
    }

    obj.write(reinterpret_cast<const char*>(&ID), sizeof(int));
    obj.write(reinterpret_cast<const char*>(&w), sizeof(Workout));

    obj.close();

    if (w.getTName() != "") {
        Trainer t = findTrainerByName(w.getTName());
        if (t.addClient(*this)) {
            cout << "Workout request sent to trainer" << endl;
        }
    }
}

void Regular::deleteWorkout(const string& categoryToDelete) {
    fstream file("Workout.bin", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "Error opening workout file." << endl;
        return;
    }

    ofstream temp("temp.bin", ios::binary | ios::app);
    if (!temp) {
        cout << "Error creating temporary file." << endl;
        file.close();
        return;
    }

    int userIDFromFile = 0;
    Workout work;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&userIDFromFile), sizeof(int)) &&
        file.read(reinterpret_cast<char*>(&work), sizeof(Workout))) {

        if (file.eof()) {
            break;
        }
        if (userIDFromFile == ID && work.getCategory() == categoryToDelete) {
            found = true;
            cout << "Workout with category " << categoryToDelete << " deleted." << endl;
        }
        else {
            temp.write(reinterpret_cast<char*>(&userIDFromFile), sizeof(int));
            temp.write(reinterpret_cast<char*>(&work), sizeof(Workout));
        }
    }

    file.close();
    temp.close();

    if (!found) {
        cout << "No workout found with category: " << categoryToDelete << " for user: " << ID << endl;
        remove("temp.bin");
        return;
    }

    remove("Workout.bin");

    if (rename("temp.bin", "Workout.bin") != 0) {
        cout << "Error: Unable to delete." << endl;
        return;
    }
}

void Regular::updateWorkout(const string& categoryToUpdate, const Workout& updatedWorkout) {
    ifstream file("Workout.bin", ios::binary);
    if (!file) {
        cout << "Error opening workout file." << endl;
        return;
    }

    ofstream temp("temp.bin", ios::binary | ios::app);
    if (!temp) {
        cout << "Error opening workout file." << endl;
        return;
    }

    int userIDFromFile = 0;
    Workout work;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&userIDFromFile), sizeof(int)) &&
        file.read(reinterpret_cast<char*>(&work), sizeof(Workout))) {
        if (file.eof()) {
            break;
        }
        if (userIDFromFile == ID && work.getCategory() == categoryToUpdate) {
            found = true;
            temp.write(reinterpret_cast<const char*>(&userIDFromFile), sizeof(int));
            temp.write(reinterpret_cast<const char*>(&updatedWorkout), sizeof(Workout));
            cout << "Workout with category " << categoryToUpdate << " updated." << endl;
        }
        else {
            temp.write(reinterpret_cast<const char*>(&userIDFromFile), sizeof(int));
            temp.write(reinterpret_cast<const char*>(&work), sizeof(Workout));
        }
    }

    file.close();
    temp.close();

    if (!found) {
        cout << "No workout found with category: " << categoryToUpdate << " for user: " << ID << endl;
        remove("temp.bin");
        return;
    }

    remove("Workout.bin");

    if (rename("temp.bin", "Workout.bin") != 0) {
        cout << "Error: Unable to update file." << endl;
        return;
    }
}




class Admin {
    const string adminKey = "Fitness is gold";

public:
    bool authenticateAdmin(const string& inputKey) {
        return inputKey == adminKey;
    }
};


void displayLoginOptions() {
    cout << "\nPress 1: To Login" << endl;
    cout << "Press 2: To Signup" << endl;
    cout << "Press 3: If You Forgot Password" << endl;
    cout << "Press 4: To Go Back" << endl;
}

int displayUserOptions() {
    int c = 0;

    do {
        cout << "\nPress 1: For Workout Tracking" << endl;
        cout << "Press 2: For Social Interaction" << endl;
        cout << "Press 3: For Nutrition Tracking" << endl;
        cout << "Press 4: For Progess Analysis" << endl;
        cout << "Press 5: For Challenges And Competition" << endl;
        cout << "Press 6 : To Go Back" << endl;
        cout << "Enter your choice : " << endl;
        cin >> c;
    } while (c < 1 || c>6);

    return c;
}

int displayWorkoutOptions() {
    int c = 0;
    do {
        cout << "\nWorkout Tracking Menu:" << endl;
        cout << "1. Log a New Workout Session" << endl;
        cout << "2. View Logged Workouts" << endl;
        cout << "3. Delete Workout" << endl;
        cout << "4. Update Workout" << endl;
        cout << "5. Apply Filters" << endl;
        cout << "6. Go Back" << endl;
        cout << "Enter your choice : " << endl;
        cin >> c;
    } while (c < 1 || c>6);

    return c;
}

int displayFilterOption() {
    int c = 0;
    do {
        cout << "\nFilter Options:" << endl;
        cout << "1. To Filter By Category" << endl;
        cout << "2. To Filter By Intensity" << endl;
        cout << "3. To Filter By Duration" << endl;
        cout << "4. Go Back" << endl;
        cout << "Enter your choice : " << endl;
        cin >> c;
    } while (c < 1 || c>4);

    return c;
}

int displaySocialOptions() {
    int c = 0;
    do {
        cout << "\nSocial Media Options:" << endl;
        cout << "1. To Message Someone Privately" << endl;
        cout << "2. To Display Previous DM's" << endl;
        cout << "3. To Message in a Group" << endl;
        cout << "4. To Display Group Chats" << endl;
        cout << "5. To Post Something new" << endl;
        cout << "6. To view Posts" << endl;
        cout << "7: To Go Back" << endl;
        cout << "Enter your choice : " << endl;
        cin >> c;
    } while (c < 1 || c>7);

    return c;
}


int displayNutritionOptions() {
    int c = 0;
    do {
        cout << "\nNutrition/Diet Options:" << endl;
        cout << "1. To Insert Daily Diet Nutrition" << endl;
        cout << "2. To Delete Daily Diet Nutrition" << endl;
        cout << "3. To Update Daily Diet Nutrition" << endl;
        cout << "4. To Calculate total Calories Consumption" << endl;
        cout << "5. For Recommendated Diet Plan/Exercises" << endl;
        cout << "6. To View Diet Nutrition" << endl;
        cout << "7: To Go Back" << endl;
        cout << "Enter your choice : " << endl;
        cin >> c;
    } while (c < 1 || c>7);

    return c;
}

int displayChallenges() {
    int c = 0;
    do {
        cout << "\nChallenges Options:" << endl;
        cout << "1. To Select A New Challenge" << endl;
        cout << "2. If Challenge Is Completed" << endl;
        cout << "3. To View HighScores" << endl;
        cout << "4: To Go Back" << endl;
        cout << "Enter your choice : " << endl;
        cin >> c;
    } while (c < 1 || c>4);

    return c;
}

int main() {

    cout << "*****************Welcome To FitConnect*****************" << endl;



    while (true) {
        int choice;
        cout << "Press 1: For Regular Clients" << endl;
        cout << "Press 2: For Trainers" << endl;
        cout << "Press 3: For Admins" << endl;
        cout << "Press 4: To Exit" << endl;
        cout << "Enter your Choice: ";
        cin >> choice;

        //----------switch 1--------------------------
        switch (choice) {
        case 1: {
            bool check = true;
            while (check) {
                displayLoginOptions();

                int c;
                cout << "Enter your choice: ";
                cin >> c;
                //----------switch 2--------------------------
                switch (c) {
                case 1: {
                    string email, pass;
                    cout << "Enter Your Email Address: ";
                    cin.ignore();
                    getline(cin, email);

                    cout << "Enter your password: ";
                    cin.ignore();
                    getline(cin, pass);

                    Regular user;
                    if (authenticate(email, pass, user)) {
                        cout << "\n\n**************************************" << endl;
                        cout << "\tWelcome Back: " << user.getName() << endl;
                        cout << "**************************************" << endl;
                    }
                    else {
                        cout << "Invalid email or password. Please try again." << endl;
                    }

                    bool pl = true;
                    while (pl) {
                        int d = displayUserOptions();
                        //----------switch 3--------------------------
                        switch (d) {
                        case 1: {
                            bool eq = true;
                            while (eq) {
                                int e = displayWorkoutOptions();
                                //----------switch 4--------------------------
                                switch (e) {
                                case 1: {
                                    Workout session;
                                    session.newSession();
                                    user.addWorkout(session);

                                    break;
                                }
                                case 2: {
                                    user.viewLoggedWorkouts();
                                    break;
                                }
                                case 3: {
                                    string category = "";
                                    cout << "Enter the workout category to delete : ";
                                    cin.ignore();
                                    getline(cin, category);
                                    user.deleteWorkout(category);
                                    break;
                                }
                                case 4: {
                                    string category = "";
                                    cout << "Enter the workout category to update : ";
                                    cin.ignore();
                                    getline(cin, category);

                                    int h = 0, m = 0, duration = 0;
                                    string intensity = "", trainer = "";
                                    double caloriesBurnt = 0.0;


                                    do {
                                        cout << "Enter the  Duration of the workout session in minutes : ";
                                        cin >> duration;
                                    } while (duration <= 0);

                                    cout << "Intensity level of the workout (e.g., low, medium, high) : ";
                                    cin.ignore();
                                    getline(cin, intensity);

                                    do {
                                        cout << "Enter the Calories burnt during the workout session: ";
                                        cin >> caloriesBurnt;
                                    } while (caloriesBurnt < 0);



                                    cout << "Enter TimeStamp : " << endl;

                                    do {
                                        cout << "Enter Hour : ";
                                        cin >> h;
                                    } while (h < 0 || h>24);
                                    do {
                                        cout << "Enter minutes : ";
                                        cin >> m;
                                    } while (m < 0 || m > 59);

                                    char ch = '\0';
                                    do {
                                        cout << "\nLastly,Do You want a trainer for this workout : ";
                                        cin >> ch;
                                    } while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N');

                                    if (ch == 'y' || ch == 'Y') {

                                        ifstream obj("registered_Trainer.bin", ios::binary);
                                        if (!obj) {
                                            cout << "Error opening trainer file." << endl;
                                        }

                                        Trainer t;
                                        cout << "\nAvailable Trainers:" << endl;
                                        while (!obj.eof()) {
                                            if (t.decryption(obj)) {
                                                cout << "- " << t.getName() << "-" << t.getSpec() << endl;
                                            }
                                        }
                                        obj.close();


                                        cout << "Enter trainer name You want : ";
                                        cin.ignore();
                                        getline(cin, trainer);

                                        cout << "Trainer " << trainer << " Selected " << endl;
                                    }
                                    else {
                                        trainer = "";
                                    }

                                    Time time(h, m);

                                    Workout updated(category, duration, intensity, caloriesBurnt, time, trainer);
                                    user.updateWorkout(category, updated);
                                    break;
                                }
                                case 5: {
                                    int f = displayFilterOption();

                                    switch (f) {
                                    case 1: {
                                        string category = "";
                                        cout << "Enter the workout category : ";
                                        cin.ignore();
                                        getline(cin, category);

                                        user.filterByCategory(category);
                                        break;
                                    }
                                    case 2: {
                                        string intensity = "";
                                        cout << "Enter the workout intensity : ";
                                        cin.ignore();
                                        getline(cin, intensity);

                                        user.filterByIntensity(intensity);
                                        break;
                                    }
                                    case 3: {
                                        int duration = 0;
                                        cout << "Enter the workout duration : ";
                                        cin.ignore();
                                        cin >> duration;

                                        user.filterByDuration(duration);
                                        break;
                                    }
                                    }
                                    break;
                                }
                                case 6: {
                                    eq = false;
                                    break;
                                }
                                }
                            }

                            //------------end switch 4---------------------
                            break;
                        }
                        case 2: {
                            bool eq = true;
                            while (eq) {
                                int q = displaySocialOptions();

                                switch (q) {
                                case 1: {
                                    string recipient = "";
                                    string message = "";
                                    int hr = 0, min = 0;

                                    cout << "\nWould you be so kind to Enter the time right now, since all of our system is analog" << endl;
                                    do {
                                        cout << "Enter hour : ";
                                        cin >> hr;
                                    } while (hr < 0 || hr>24);

                                    do {
                                        cout << "Enter min : ";
                                        cin >> min;
                                    } while (min < 0 || min>59);

                                    cout << "Enter the name of reciepient you want to privately DM : ";
                                    cin.ignore();
                                    getline(cin, recipient);

                                    cout << "Enter the message you want to send : ";
                                    cin.ignore();
                                    getline(cin, message);

                                    user.getMedia().DM(user.getName(), recipient, message, hr, min);
                                    break;
                                }
                                case 2: {

                                    user.getMedia().viewDirectMessages();

                                    break;
                                }
                                case 3: {
                                    string recipient = "";
                                    string message = "";
                                    int hr = 0, min = 0, groupID = 0;

                                    cout << "\nWould you be so kind to Enter the time right now, since all of our system is analog" << endl;
                                    do {
                                        cout << "Enter hour : ";
                                        cin >> hr;
                                    } while (hr < 0 || hr>24);

                                    do {
                                        cout << "Enter min : ";
                                        cin >> min;
                                    } while (min < 0 || min>59);

                                    do {
                                        cout << "Groups " << endl;
                                        for (int i = 0; i < 7; i++) {
                                            cout << i + 1 << " : " << groups[i] << endl;
                                        }
                                        cout << "Enter the group ID you want to message On : ";
                                        cin >> groupID;
                                    } while (groupID < 1 || groupID>7);

                                    cout << "Enter the message you want to send : ";
                                    cin.ignore();
                                    getline(cin, message);

                                    user.getMedia().messageInGroup(user.getName(), groupID - 1, message, hr, min);

                                    break;
                                }
                                case 4: {
                                    user.getMedia().viewGroupChats();
                                    break;
                                }
                                case 5: {
                                    string message = "";
                                    int hr = 0, min = 0;

                                    cout << "\nWould you be so kind to Enter the time right now, since all of our system is analog" << endl;
                                    do {
                                        cout << "Enter hour : ";
                                        cin >> hr;
                                    } while (hr < 0 || hr>24);
                                    do {
                                        cout << "Enter min : ";
                                        cin >> min;
                                    } while (min < 0 || min>59);

                                    cout << "TWEET THE POST : ";
                                    cin.ignore();
                                    getline(cin, message);

                                    user.getMedia().post(user.getName(), message, hr, min);

                                    break;
                                }
                                case 6: {
                                    user.getMedia().viewPosts();


                                    int selectedPostID = 0;
                                    do {
                                        cout << "Enter the ID of the post you want to interact with: ";
                                        cin >> selectedPostID;
                                    } while (selectedPostID < 0);

                                    bool ew = true;
                                    while (ew) {
                                        int choice = 0;
                                        do {
                                            cout << "\nPost Interaction Options:" << endl;
                                            cout << "1. View comments" << endl;
                                            cout << "2. Like post" << endl;
                                            cout << "3. Comment on post" << endl;
                                            cout << "4. Go back" << endl;
                                            cout << "Enter your choice: ";
                                            cin >> choice;

                                        } while (choice < 1 || choice>4);

                                        switch (choice) {
                                        case 1: {

                                            user.getMedia().viewComments(selectedPostID);
                                            break;
                                        }
                                        case 2: {
                                            user.getMedia().likePost(selectedPostID);
                                            break;
                                        }
                                        case 3: {
                                            string comment = "";
                                            cout << "Enter your comment : ";
                                            cin.ignore();
                                            getline(cin, comment);

                                            user.getMedia().commentOnPost(user.getName(), selectedPostID, comment);
                                            break;
                                        }
                                        default: {
                                            ew = false;
                                            break;
                                        }
                                        }
                                    }
                                    break;
                                }
                                case 7: {
                                    eq = false;
                                    break;
                                }
                                }
                            }
                            break;
                        }
                        case 3: {
                            bool qe = true;
                            while (qe) {
                                int a = displayNutritionOptions();

                                switch (a) {
                                case 1: {
                                    string cat = "";
                                    int hr = 0, min = 0;
                                    double calories = 0.0, protein = 0.0, carbs = 0.0, vit = 0.0, fats = 0.0;
                                    char v = '\0';

                                    cout << "\nWould you be so kind to Enter the time right now, since all of our system is analog" << endl;
                                    do {
                                        cout << "Enter hour : ";
                                        cin >> hr;
                                    } while (hr < 0 || hr>24);
                                    do {
                                        cout << "Enter min : ";
                                        cin >> min;
                                    } while (min < 0 || min>59);

                                    cout << "Enter the type of workout you want to insert nutrition of : (cardio,yoga etc) ";
                                    cin.ignore();
                                    getline(cin, cat);

                                    do {
                                        cout << "Enter daily calories consumption (kCal) : ";
                                        cin >> calories;
                                    } while (calories <= 0.0);

                                    do {
                                        cout << "Enter daily protein consumption (g) : ";
                                        cin >> protein;
                                    } while (protein <= 0.0);

                                    do {
                                        cout << "Enter daily Carbohydrates consumption (g) : ";
                                        cin >> carbs;
                                    } while (carbs <= 0.0);

                                    do {
                                        cout << "Enter daily FATS consumption (g) : ";
                                        cin >> fats;
                                    } while (fats <= 0.0);

                                    do {
                                        cout << "Enter the name of vitamin you consume daily(A,B,C,D,E,K) : ";
                                        cin >> v;
                                    } while (v != 'A' && v != 'B' && v != 'C' && v != 'D' && v != 'E' && v != 'K');

                                    do {
                                        cout << "Enter daily Vitamin " << v << " consumption(kCal) : ";
                                        cin >> vit;
                                    } while (vit <= 0.0);

                                    Time o(hr, min);
                                    Nutrition obj(o, calories, protein, carbs, fats, v, vit);

                                    user.insertNutrition(cat, obj);
                                    break;
                                }
                                case 2: {
                                    string cat = "";

                                    cout << "Enter the type of workout you want to delete nutrition of : (cardio,yoga etc) ";
                                    cin.ignore();
                                    getline(cin, cat);

                                    user.deleteNutrition(cat);
                                    break;
                                }
                                case 3: {
                                    string cat = "";
                                    int hr = 0, min = 0;
                                    double calories = 0.0, protein = 0.0, carbs = 0.0, vit = 0.0, fats = 0.0;
                                    char v = '\0';

                                    cout << "\nWould you be so kind to Enter the time right now, since all of our system is analog" << endl;
                                    do {
                                        cout << "Enter hour : ";
                                        cin >> hr;
                                    } while (hr < 0 || hr>24);
                                    do {
                                        cout << "Enter min : ";
                                        cin >> min;
                                    } while (min < 0 || min>59);

                                    cout << "Enter the type of workout you want to update nutrition of : (cardio,yoga etc) ";
                                    cin.ignore();
                                    getline(cin, cat);

                                    do {
                                        cout << "Enter daily calories consumption (kCal) : ";
                                        cin >> calories;
                                    } while (calories <= 0.0);

                                    do {
                                        cout << "Enter daily protein consumption (g) : ";
                                        cin >> protein;
                                    } while (protein <= 0.0);

                                    do {
                                        cout << "Enter daily Carbohydrates consumption (g) : ";
                                        cin >> carbs;
                                    } while (carbs <= 0.0);

                                    do {
                                        cout << "Enter daily FATS consumption (g) : ";
                                        cin >> fats;
                                    } while (fats <= 0.0);

                                    do {
                                        cout << "Enter the name of vitamin you consume daily(A,B,C,D,E,K) : ";
                                        cin >> v;
                                    } while (v != 'A' && v != 'B' && v != 'C' && v != 'D' && v != 'E' && v != 'K');

                                    do {
                                        cout << "Enter daily Vitamin " << v << " consumption(kCal) : ";
                                        cin >> vit;
                                    } while (vit <= 0.0);

                                    Time o(hr, min);
                                    Nutrition obj(o, calories, protein, carbs, fats, v, vit);
                                    user.updateNutrition(cat, obj);
                                    break;
                                }
                                case 4: {

                                    string cat = "";

                                    cout << "Enter the type of workout for which u want to calculate Calorie Consumption(cardio,yoga etc) ";
                                    cin.ignore();
                                    getline(cin, cat);

                                    cout << "Total Calorie Consumption for " << cat << " is : " << user.calculateCalorieConsumption(cat);
                                    break;
                                }
                                case 5: {
                                    string cat = "";
                                    int hr = 0, min = 0, weight = 0;
                                    double calories = 0.0, protein = 0.0, carbs = 0.0, vit = 0.0, fats = 0.0;
                                    char v = '\0';

                                    cout << "\nWould you be so kind to Enter the time right now, since all of our system is analog" << endl;
                                    do {
                                        cout << "Enter hour : ";
                                        cin >> hr;
                                    } while (hr < 0 || hr>24);
                                    do {
                                        cout << "Enter min : ";
                                        cin >> min;
                                    } while (min < 0 || min>59);

                                    do {
                                        cout << "Enter you current weight sir : ";
                                        cin >> weight;
                                    } while (weight <= 0);
                                    do {
                                        cout << "Enter daily calories consumption (kCal) : ";
                                        cin >> calories;
                                    } while (calories <= 0.0);

                                    do {
                                        cout << "Enter daily protein consumption (g) : ";
                                        cin >> protein;
                                    } while (protein <= 0.0);

                                    do {
                                        cout << "Enter daily Carbohydrates consumption (g) : ";
                                        cin >> carbs;
                                    } while (carbs <= 0.0);

                                    do {
                                        cout << "Enter daily FATS consumption (g) : ";
                                        cin >> fats;
                                    } while (fats <= 0.0);

                                    do {
                                        cout << "Enter the name of vitamin you consume daily(A,B,C,D,E,K) : ";
                                        cin >> v;
                                    } while (v != 'A' && v != 'B' && v != 'C' && v != 'D' && v != 'E' && v != 'K');

                                    do {
                                        cout << "Enter daily Vitamin " << v << " consumption(kCal) : ";
                                        cin >> vit;
                                    } while (vit <= 0.0);

                                    Time o(hr, min);
                                    Nutrition obj(o, calories, protein, carbs, fats, v, vit);
                                    user.recommendations(weight, obj);

                                    break;
                                }
                                case 6: {
                                    user.viewNutrition();
                                    break;
                                }
                                case 7: {
                                    qe = false;
                                    break;
                                }
                                }
                            }
                            break;
                        }
                        case 4: {
                            user.updateProgressFromFiles();
                            break;
                        }
                        case 5: {
                            Challenges obj;
                            bool is = true;
                            while (is) {
                                int op = displayChallenges();
                                switch (op) {
                                case 1: {
                                    int choi = 0;
                                    string difficulty = "";
                                    do {
                                        cout << "Press 1 : For Easy Challenge" << endl;
                                        cout << "Press 2 : For Medium Challenge" << endl;
                                        cout << "Press 3 : For Hard Challenge" << endl;
                                        cin >> choi;
                                    } while (choi < 1 || choi>3);

                                    if (choi == 1) {
                                        difficulty = "easy";
                                    }
                                    else if (choi == 2) {
                                        difficulty = "medium";
                                    }
                                    else {
                                        difficulty = "hard";
                                    }

                                    obj.newChallenge(difficulty);
                                    break;
                                }
                                case 2: {
                                    int duration = 0;
                                    do {
                                        cout << "Enter the time duration during which u completed this challenge (in hours) : ";
                                        cin >> duration;
                                    } while (duration <= 0);

                                    obj.completedChallenge(user, duration);
                                    break;
                                }
                                case 3: {
                                    int choi = 0;
                                    string difficulty = "";
                                    do {
                                        cout << "Press 1 : For Easy Challenge" << endl;
                                        cout << "Press 2 : For Medium Challenge" << endl;
                                        cout << "Press 3 : For Hard Challenge" << endl;
                                        cin >> choi;
                                    } while (choi < 1 || choi>3);

                                    if (choi == 1) {
                                        difficulty = "easy";
                                    }
                                    else if (choi == 2) {
                                        difficulty = "medium";
                                    }
                                    else {
                                        difficulty = "hard";
                                    }

                                    obj.viewHighScores(difficulty);
                                    break;
                                }
                                case 4: {
                                    is = false;
                                    break;
                                }
                                }
                            }
                            break;
                        }
                        case 6: {
                            pl = false;
                            break;
                        }
                        }
                    }

                    //------------end switch 4---------------------

                    break;
                }
                case 2: {
                    int ID, age;
                    string name, email, pass, gender;
                    double weight, height;

                    cout << "\nEnter Your Name: ";
                    cin.ignore();
                    getline(cin, name);

                    do {
                        cout << "Enter your ID: ";
                        cin >> ID;
                    } while (ID <= 0);

                    cout << "Enter Your Email Address: ";
                    cin.ignore();
                    getline(cin, email);

                    cout << "Enter your password: ";
                    cin.ignore();
                    getline(cin, pass);

                    cout << "Enter your gender: ";
                    cin.ignore();
                    getline(cin, gender);

                    do {
                        cout << "Enter your age (in years): ";
                        cin >> age;
                    } while (age <= 15);

                    do {
                        cout << "Enter your weight (kilograms): ";
                        cin >> weight;
                    } while (weight < 28);

                    do {
                        cout << "Enter your height (feet.inches): ";
                        cin >> height;
                    } while (height < 3.0);

                    Regular obj(ID, name, email, pass, age, weight, height, gender);

                    if (registeration(obj)) {
                        cout << name << " Registered successfully" << endl;
                    }
                    else {
                        cout << name << " Could not be registered" << endl;
                    }

                    break;
                }
                case 3: {
                    string email;
                    cout << "Enter your email Address: ";
                    cin.ignore();
                    getline(cin, email);

                    forgotPassword(email);
                    cout << "You may login now" << endl;
                    break;
                }
                default: {
                    check = false;
                    break;
                }
                }
                //------------end switch 4---------------------
            }

            break;
        }
        case 2: {
            bool check = true;
            while (check) {
                displayLoginOptions();

                int c;
                cout << "Enter your choice: ";
                cin >> c;

                switch (c) {
                case 1: {
                    string email, pass;
                    cout << "\nEnter Your Email Address: ";
                    cin.ignore();
                    getline(cin, email);

                    cout << "Enter your password: ";
                    cin.ignore();
                    getline(cin, pass);

                    Trainer trainer;
                    if (authenticateTrainer(email, pass, trainer)) {
                        cout << "\n\n****************************************" << endl;
                        cout << "\tWelcome Back: " << trainer.getName() << endl;
                        cout << "****************************************" << endl;
                    }
                    else {
                        cout << "Invalid email or password. Please try again." << endl;
                    }
                    break;
                }
                case 2: {
                    int ID;
                    string name, email, pass;
                    string gender;
                    string spec;
                    string str;
                    string cert;
                    double fee;
                    int age;
                    int experience;

                    cout << "\nEnter Your Name: ";
                    cin.ignore();
                    getline(cin, name);

                    do {
                        cout << "Enter your ID: ";
                        cin >> ID;
                    } while (ID <= 0);

                    cout << "Enter Your Email Address: ";
                    cin.ignore();
                    getline(cin, email);

                    cout << "Enter your password: ";
                    cin.ignore();
                    getline(cin, pass);

                    cout << "Enter your gender: ";
                    cin.ignore();
                    getline(cin, gender);

                    cout << "Enter your age (in years): ";
                    cin >> age;

                    cout << "Enter Your field specification (gym expert,yoga expert etc): ";
                    cin.ignore();
                    getline(cin, spec);

                    cout << "Enter any certification title you have in field : ";
                    cin.ignore();
                    getline(cin, cert);

                    cout << "Enter your experience (in years): ";
                    cin >> experience;

                    cout << "Enter your story of success : ";
                    cin.ignore();
                    getline(cin, str);

                    do {
                        cout << "Lastly,Enter round estimate of the fee that you are happy to charge clients" << endl;
                        cin >> fee;
                    } while (fee <= 0);

                    Trainer trainer(ID, name, email, pass, gender, spec, str, cert, fee, age, experience);

                    if (registerTrainer(trainer)) {
                        cout << name << " Registered successfully" << endl;
                    }
                    else {
                        cout << name << " Could not be registered" << endl;
                    }

                    break;
                }
                case 3: {
                    string email;
                    cout << "Enter your email Address: ";
                    cin.ignore();
                    getline(cin, email);

                    forgotTpass(email);
                    cout << "You may login now" << endl;
                    break;
                }
                default: {
                    check = false;
                    break;
                }
                }
            }
            break;
        }
        case 3: {
            string key = "";

            cout << "Enter Admin Key : ";
            cin.ignore();
            getline(cin, key);

            Admin admin;
            if (admin.authenticateAdmin(key)) {
                cout << "**************************************" << endl;
                cout << "\t\tAdministration Mode On: " << endl;
                cout << "**************************************" << endl;
            }
            else {
                cout << "Invalid admin key" << endl;
            }
            break;
        }
        default: {
            exit(0);
            break;
        }
        }
    }

    return 0;
}
