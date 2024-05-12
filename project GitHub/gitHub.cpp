#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int MAX_FILES = 100;
const int MAX_COMMITS = 100;

class Commit {
private:
    string message;
    string author;

public:
    Commit() {}  // Default constructor

    Commit(const string& mess, const string& auth) {
        message = mess;
        author = auth;
    }

    // Getter methods
    string getMessage() const {
        return message;
    }
    string getAuthor() const {
        return author;
    }
};

class File {
private:
    string name;

public:
    File() {}  // Default constructor

    File(const string& n) {
        name = n;
    }

    // Getter method
    string getName() const {
        return name;
    }
};

class Repository {
private:
    string name;
    File files[MAX_FILES];
    Commit commits[MAX_COMMITS];
    int fileCount;
    int commitCount;
    bool isPublic;

public:
    Repository() {
        fileCount = 0;
        commitCount = 0;
        isPublic = false;
    }  // Default constructor

    Repository(const string& n, bool visibility) {
        name = n;
        fileCount = 0;
        commitCount = 0;
        isPublic = visibility;
    }

    void addFile(const File& file) {
        if (fileCount < MAX_FILES) {
            files[fileCount++] = file;
        }
        else {
            cout << "Cannot add file. Maximum file limit reached." << endl;
        }
    }

    void deleteFile(const string& filename) {
        for (int i = 0; i < fileCount; ++i) {
            if (files[i].getName() == filename) {
                for (int j = i; j < fileCount - 1; ++j) {
                    files[j] = files[j + 1];
                }
                --fileCount;
                cout << "File deleted from the repository!" << endl;
                return;
            }
        }
        cout << "File not found in the repository." << endl;
    }

    void addCommit(const Commit& commit) {
        if (commitCount < MAX_COMMITS) {
            commits[commitCount++] = commit;
        }
        else {
            cout << "Cannot add commit. Maximum commit limit reached." << endl;
        }
    }

    void displayDetails() const {
        cout << "Repository Name: " << name << endl;
        cout << "Visibility: " << (isPublic ? "Public" : "Private") << endl;
        cout << "Files:" << endl;
        for (int i = 0; i < fileCount; ++i) {
            cout << "- " << files[i].getName() << endl;
        }
        cout << "Commits:" << endl;
        for (int i = 0; i < commitCount; ++i) {
            cout << "- Message: " << commits[i].getMessage() << ", Author: " << commits[i].getAuthor() << endl;
        }
    }

    void saveToCSV(ofstream& file) const {
        file << name << "," << isPublic << ",";
        for (int i = 0; i < fileCount; ++i) {
            file << files[i].getName() << ",";
        }
        file << ",";
        for (int i = 0; i < commitCount; ++i) {
            file << commits[i].getMessage() << ";" << commits[i].getAuthor() << ",";
        }
        file << endl;
    }

    void loadFromCSV(ifstream& file) {
        string line;
        if (getline(file, line)) {
            stringstream ss(line);
            string token;

            getline(ss, name, ',');
            getline(ss, token, ',');
            isPublic = stoi(token);

            fileCount = 0;
            while (getline(ss, token, ',')) {
                if (!token.empty() && token.find(";") == string::npos) {
                    files[fileCount++] = File(token);
                }
            }

            commitCount = 0;
            while (getline(ss, token, ',')) {
                stringstream commit_ss(token);
                string message, author;
                getline(commit_ss, message, ';');
                getline(commit_ss, author, ';');
                if (!message.empty() && !author.empty()) {
                    commits[commitCount++] = Commit(message, author);
                }
            }
        }
    }
};

class LinkedList {
public:
    struct Node {
        string data;
        Node* next;
    };

    Node* head;
    int size;

    LinkedList() {
        head = nullptr;
        size = 0;
    }

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void add(const string& data) {
        Node* newNode = new Node{ data, head };
        head = newNode;
        size++;
    }

    void remove(const string& data) {
        if (head == nullptr) {
            return;
        }

        if (head->data == data) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
            size--;
            return;
        }

        Node* current = head;
        while (current->next != nullptr) {
            if (current->next->data == data) {
                Node* toDelete = current->next;
                current->next = current->next->next;
                delete toDelete;
                size--;
                return;
            }
            current = current->next;
        }
    }

    int getSize() const {
        return size;
    }

    bool contains(const string& data) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == data) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

class User {
public:
    string username;
    string password;
    LinkedList following;
    LinkedList followers;
    User* next;

    User(const string& uname, const string& pwd) {
        username = uname;
        password = pwd;
        next = nullptr;
    }
};

class UserAccounts {
private:
    int capacity;
    User** table; // Hash table for storing users

    int hashFunction(const string& key) {
        int hash = 0;
        int prime = 31; // Prime multiplier for better distribution
        for (char c : key) {
            hash = (hash * prime + c) % capacity;
        }
        return hash;
    }

public:
    UserAccounts(int size = 10) : capacity(size) {
        table = new User * [capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    ~UserAccounts() {
        for (int i = 0; i < capacity; i++) {
            User* current = table[i];
            while (current != nullptr) {
                User* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] table;
    }

    bool registerUser(const string& username, const string& password) {
        int index = hashFunction(username);

        User* current = table[index];
        while (current != nullptr) {
            if (current->username == username) {
                return false;
            }
            current = current->next;
        }

        User* newUser = new User(username, password);
        newUser->next = table[index]; // Chaining
        table[index] = newUser;

        return true; // User registered
    }

    bool login(const string& username, const string& password) {
        int index = hashFunction(username);

        User* current = table[index];
        while (current != nullptr) {
            if (current->username == username && current->password == password) {
                return true;
            }
            current = current->next;
        }

        return false;
    }

    User* getProfile(const string& username) {
        int index = hashFunction(username);

        User* current = table[index];
        while (current != nullptr) {
            if (current->username == username) {
                return current; // User found
            }
            current = current->next;
        }

        return nullptr;
    }

    bool follow(const string& follower, string& followee) {
        User* followerUser = getProfile(follower);
        User* followeeUser = getProfile(followee);

        if (followerUser && followeeUser) {
            if (!followerUser->following.contains(followee)) {
                followerUser->following.add(followee);
                followeeUser->followers.add(follower);
                return true;
            }
        }
        return false;
    }

    bool unfollow(const string& follower, string& followee) {
        User* followerUser = getProfile(follower);
        User* followeeUser = getProfile(followee);
        if (followerUser && followeeUser) {
            if (followerUser->following.contains(followee)) {
                followerUser->following.remove(followee);
                followeeUser->followers.remove(follower);
                return true;
            }
        }
        return false;
    }
};

void saveRepositoriesToCSV(const Repository repositories[], int repoCount) {
    ofstream file("data.csv");
    if (file.is_open()) {
        for (int i = 0; i < repoCount; ++i) {
            repositories[i].saveToCSV(file);
        }
        file.close();
        cout << "Data saved to data.csv" << endl;
    }
    else {
        cout << "Unable to open data.csv for writing!" << endl;
    }
}

void loadRepositoriesFromCSV(Repository repositories[], int& repoCount) {
    ifstream file("data.csv");
    if (file.is_open()) {
        repoCount = 0;
        while (!file.eof()) {
            repositories[repoCount++].loadFromCSV(file);
        }
        file.close();
        --repoCount; // Adjusting count after EOF
        cout << "Data loaded from data.csv" << endl;
    }
    else {
        cout << "Unable to open data.csv for reading!" << endl;
    }
}

int main() {
    UserAccounts userAccounts;
    Repository repositories[10];
    int repoCount = 0;

    // Load existing data
    loadRepositoriesFromCSV(repositories, repoCount);

    bool running = true;
    while (running) {
        cout << "\nMain Menu:\n";
        cout << "1. User Account Management\n";
        cout << "2. Repository Management\n";
        cout << "3. Exit\n";

        int mainChoice;
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
        case 1: {  // User account management
            int userChoice;
            cout << "\nUser Account Menu:\n";
            cout << "1. Register User\n";
            cout << "2. Login\n";
            cout << "3. Follow User\n";
            cout << "4. Unfollow User\n";
            cout << "5. View Profile\n";
            cout << "Enter your choice: ";
            cin >> userChoice;

            switch (userChoice) {
            case 1: {  // Register User
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                if (userAccounts.registerUser(username, password)) {
                    cout << "User registered successfully.\n";
                }
                else {
                    cout << "Username already exists.\n";
                }
                break;
            }
            case 2: {  // Login
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                if (userAccounts.login(username, password)) {
                    cout << "Login successful.\n";
                }
                else {
                    cout << "Invalid credentials.\n";
                }
                break;
            }
            case 3: {  // Follow User
                string follower, followee;
                cout << "Enter your username: ";
                cin >> follower;
                cout << "Enter username to follow: ";
                cin >> followee;

                if (userAccounts.follow(follower, followee)) {
                    cout << "Followed successfully.\n";
                }
                else {
                    cout << "Follow failed. Check if usernames are correct.\n";
                }
                break;
            }
            case 4: {  // Unfollow User
                string follower, followee;
                cout << "Enter your username: ";
                cin >> follower;
                cout << "Enter username to unfollow: ";
                cin >> followee;

                if (userAccounts.unfollow(follower, followee)) {
                    cout << "Unfollowed successfully.\n";
                }
                else {
                    cout << "Unfollow failed. Check if usernames are correct.\n";
                }
                break;
            }
            case 5: {  // View Profile
                string username;
                cout << "Enter username to view profile: ";
                cin >> username;

                User* user = userAccounts.getProfile(username);
                if (user) {
                    cout << "Profile of " << user->username << ":\n";
                    cout << "Followers: " << user->followers.getSize() << "\n";
                    cout << "Following: " << user->following.getSize() << "\n";
                }
                else {
                    cout << "User not found.\n";
                }
                break;
            }
            default:
                cout << "Invalid choice. Try again.\n";
                break;
            }
            break;
        }
        case 2: {  // Repository management
            int repoChoice;
            cout << "\nRepository Management Menu:\n";
            cout << "1. Create Repository\n";
            cout << "2. Add File to Repository\n";
            cout << "3. Delete File from Repository\n";
            cout << "4. Add Commit to Repository\n";
            cout << "5. View Repository Details\n";
            cout << "6. Save and Exit\n";
            cout << "Enter your choice: ";
            cin >> repoChoice;

            switch (repoChoice) {
            case 1: {  // Create Repository
                string name;
                bool isPublic;
                cout << "Enter repository name: ";
                cin >> name;
                cout << "Is the repository public? (1 for yes, 0 for no): ";
                cin >> isPublic;
                if (repoCount < 10) {
                    repositories[repoCount++] = Repository(name, isPublic);
                    cout << "Repository created successfully!" << endl;
                }
                else {
                    cout << "Maximum number of repositories reached!" << endl;
                }
                break;
            }
            case 2: {  // Add File to Repository
                int repoIndex;
                string filename;
                cout << "Enter repository index: ";
                cin >> repoIndex;
                if (repoIndex < repoCount) {
                    cout << "Enter file name: ";
                    cin >> filename;
                    repositories[repoIndex].addFile(File(filename));
                }
                else {
                    cout << "Invalid repository index!" << endl;
                }
                break;
            }
            case 3: {  // Delete File from Repository
                int repoIndex;
                string filename;
                cout << "Enter repository index: ";
                cin >> repoIndex;
                if (repoIndex < repoCount) {
                    cout << "Enter file name to delete: ";
                    cin >> filename;
                    repositories[repoIndex].deleteFile(filename);
                }
                else {
                    cout << "Invalid repository index!" << endl;
                }
                break;
            }
            case 4: {  // Add Commit to Repository
                int repoIndex;
                string message, author;
                cout << "Enter repository index: ";
                cin >> repoIndex;
                if (repoIndex < repoCount) {
                    cout << "Enter commit message: ";
                    cin.ignore();
                    getline(cin, message);
                    cout << "Enter author name: ";
                    getline(cin, author);
                    repositories[repoIndex].addCommit(Commit(message, author));
                }
                else {
                    cout << "Invalid repository index!" << endl;
                }
                break;
            }
            case 5: {  // View Repository Details
                int repoIndex;
                cout << "Enter repository index: ";
                cin >> repoIndex;
                if (repoIndex < repoCount) {
                    repositories[repoIndex].displayDetails();
                }
                else {
                    cout << "Invalid repository index!" << endl;
                }
                break;
            }
            case 6:  // Save and Exit
                saveRepositoriesToCSV(repositories, repoCount);
                cout << "Exiting program..." << endl;
                running = false;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
            }
            break;
        }
        case 3:
            cout << "Exiting Main Menu..." << endl;
            running = false;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
            break;
        }
    }

    return 0;
}
