#include <iostream>
#include <string>

using namespace std;

const int MAX_FILES = 100;//max number of files and commit
const int MAX_COMMITS = 100;

class Commit {
private:
    string message;
    string author;

public:
    Commit() {}  // Default constructor

    Commit(const string& mess, const string& auth)
    {
        message = mess;
        author = auth;
    }

    string getMessage() const
    {
        return message;
    }
    string getAuthor() const
    {
        return author;
    }
};

class File
{
private:
    string name;

public:
    File() {}  // Default constructor

    File(const string& n)
    {
        name = n;
    }

    string getName() const
    {
        return name;
    }
};

class Repository
{
private:
    string name;
    File files[MAX_FILES];
    Commit commits[MAX_COMMITS];
    int fileCount;
    int commitCount;
    bool isPublic;

public:
    Repository()
    {
        fileCount = 0;
        commitCount = 0;
    }

    Repository(const string& _name, bool isPublic)
    {
        name = _name;
        fileCount = 0;
        commitCount = 0;
        isPublic = isPublic;
    }
    void displayDetails() const
    {
        cout << "Repository Name: " << name << endl;
        cout << "Visibility: " << (isPublic ? "Public" : "Private") << endl;
    }
};
int main() 
{
    Repository repositories[10];
    int repoCount = 0;
    int choice;

    do 
    {
        cout << "\nMenu:" << endl;
        cout << "1. Create Repository" << endl;
        cout << "2. View Repository Details" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string name;
            bool isPublic;
            cout << "Enter repository name: ";
            cin >> name;
            cout << "Is the repository public? (1 for yes, 0 for no): ";
            cin >> isPublic;
            repositories[repoCount++] = Repository(name, isPublic);
            cout << "Repository created successfully!" << endl;
            break;
        }
        case 2: 
        {
            int repoIndex;
            cout << "Enter repository index: ";
            cin >> repoIndex;
            repositories[repoIndex].displayDetails();
            break;
        }
        case 3:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
