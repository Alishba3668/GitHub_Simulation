#include "Repository.h"

using namespace std;

// Commit class methods
Commit::Commit() {}

Commit::Commit(const string& mess, const string& auth) : message(mess), author(auth) {}

string Commit::getMessage() const {
    return message;
}

string Commit::getAuthor() const {
    return author;
}

// File class methods
File::File() {}

File::File(const string& n) : name(n) {}

string File::getName() const {
    return name;
}

// Repository class methods
Repository::Repository() {
    fileCount = 0;
    commitCount = 0;
    isPublic = false;
}

Repository::Repository(const string& n, bool visibility) : name(n), isPublic(visibility) {
    fileCount = 0;
    commitCount = 0;
}

void Repository::addFile(const File& file) {
    if (fileCount < MAX_FILES) {
        files[fileCount++] = file;
    }
    else {
        cout << "Cannot add file. Maximum file limit reached." << endl;
    }
}

void Repository::deleteFile(const string& filename) {
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

void Repository::addCommit(const Commit& commit) {
    if (commitCount < MAX_COMMITS) {
        commits[commitCount++] = commit;
    }
    else {
        cout << "Cannot add commit. Maximum commit limit reached." << endl;
    }
}

void Repository::displayDetails() const {
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

void Repository::saveToCSV(ofstream& file) const {
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

void Repository::loadFromCSV(ifstream& file) {
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
