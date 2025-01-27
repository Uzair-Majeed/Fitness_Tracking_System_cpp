#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include<time.h>
using namespace std;

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
