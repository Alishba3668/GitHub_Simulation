#ifndef REPOSITORY_H
#define REPOSITORY_H

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
    Commit();
    Commit(const string& mess, const string& auth);
    string getMessage() const;
    string getAuthor() const;
};

class File {
private:
    string name;

public:
    File();
    File(const string& n);
    string getName() const;
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
    Repository();
    Repository(const string& n, bool visibility);
    void addFile(const File& file);
    void deleteFile(const string& filename);
    void addCommit(const Commit& commit);
    void displayDetails() const;
    void saveToCSV(ofstream& file) const;
    void loadFromCSV(ifstream& file);
};

#endif // REPOSITORY_H
