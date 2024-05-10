#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int MAX_FILES = 100;
const int MAX_COMMITS = 100;

class Commit
{
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

    // Getter methods
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

    // Getter method
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
    }  // Default constructor

    Repository(const string& n, bool isPublic)
    {
        name = name;
        fileCount = 0;
        commitCount = 0;
        isPublic = isPublic;
    }
    void addFile(const File& file)
    {
        if (fileCount < MAX_FILES) 
        {
            files[fileCount++] = file;
        }
        else 
        {
            cout << "Cannot add file. Maximum file limit reached." << endl;
        }
    }

    void deleteFile(const string& filename) 
    {
        for (int i = 0; i < fileCount; ++i) 
        {
            if (files[i].getName() == filename) 
            {
                for (int j = i; j < fileCount - 1; ++j)
                {
                    files[j] = files[j + 1];
                }
                --fileCount;
                cout << "File deleted from the repository!" << endl;
                return;
            }
        }
        cout << "File not found in the repository." << endl;
    }

    // Method to add a commit to the repository
    void addCommit(const Commit& commit)
    {
        if (commitCount < MAX_COMMITS) 
        {
            commits[commitCount++] = commit;
        }
        else 
        {
            cout << "Cannot add commit. Maximum commit limit reached." << endl;
        }
    }

    void displayDetails() const 
    {
        cout << "Repository Name: " << name << endl;
        cout << "Visibility: " << (isPublic ? "Public" : "Private") << endl;
        cout << "Files:" << endl;
        for (int i = 0; i < fileCount; ++i)
        {
            cout << "- " << files[i].getName() << endl;
        }
        cout << "Commits:" << endl;
        for (int i = 0; i < commitCount; ++i)
        {
            cout << "- Message: " << commits[i].getMessage() << ", Author: " << commits[i].getAuthor() << endl;
        }
    }

    void saveToCSV(ofstream& file) const 
    {
        file << name << "," << isPublic << ",";
        for (int i = 0; i < fileCount; ++i)
        {
            file << files[i].getName() << ",";
        }
        file << ",";
        for (int i = 0; i < commitCount; ++i)
        {
            file << commits[i].getMessage() << ";" << commits[i].getAuthor() << ",";
        }
        file << endl;
    }

    void loadFromCSV(ifstream& file)
    {
        string line;
        if (getline(file, line))
        {
            stringstream ss(line);
            string token;

            getline(ss, name, ',');
            getline(ss, token, ',');
            isPublic = stoi(token);

            fileCount = 0;
            while (getline(ss, token, ','))
            {
                if (!token.empty())
                {
                    files[fileCount++] = File(token);
                }
            }

            // Read commits
            commitCount = 0;
            while (getline(ss, token, ','))
            {
                stringstream commit_ss(token);
                string message, author;
                getline(commit_ss, message, ';');
                getline(commit_ss, author, ';');
                if (!message.empty() && !author.empty())
                {
                    commits[commitCount++] = Commit(message, author);
                }
            }
        }
    }
};

// Function to save repository data to "data.csv"
void saveRepositoriesToCSV(const Repository repositories[], int repoCount)
{
    ofstream file("data.csv");
    if (file.is_open())
    {
        for (int i = 0; i < repoCount; ++i)
        {
            repositories[i].saveToCSV(file);
        }
        file.close();
        cout << "Data saved to data.csv" << endl;
    }
    else 
    {
        cout << "Unable to open data.csv for writing!" << endl;
    }
}

// Function to load repository data from "data.csv"
void loadRepositoriesFromCSV(Repository repositories[], int& repoCount)
{
    ifstream file("data.csv");
    if (file.is_open()) 
    {
        repoCount = 0;
        while (!file.eof())
        {
            repositories[repoCount++].loadFromCSV(file);
        }
        file.close();
        --repoCount; 
        cout << "Data loaded from data.csv" << endl;
    }
    else
    {
        cout << "Unable to open data.csv for reading!" << endl;
    }
}

int main() 
{
    Repository repositories[10];
    int repoCount = 0;
    int choice;

    loadRepositoriesFromCSV(repositories, repoCount);

    do
    {
        cout << "\nMenu:" << endl;
        cout << "1. Create Repository" << endl;
        cout << "2. Add File to Repository" << endl;
        cout << "3. Delete File from Repository" << endl;
        cout << "4. Add Commit to Repository" << endl;
        cout << "5. View Repository Details" << endl;
        cout << "6. Exit" << endl;
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
            string filename;
            cout << "Enter repository index: ";
            cin >> repoIndex;
            cout << "Enter file name: ";
            cin >> filename;
            repositories[repoIndex].addFile(File(filename));
            break;
        }
        case 3:
        {
            int repoIndex;
            string filename;
            cout << "Enter repository index: ";
            cin >> repoIndex;
            cout << "Enter file name: ";
            cin >> filename;
            repositories[repoIndex].deleteFile(filename);
            break;
        }
        case 4:
        {
            int repoIndex;
            string message, author;
            cout << "Enter repository index: ";
            cin >> repoIndex;
            cout << "Enter commit message: ";
            cin.ignore();
            getline(cin, message);
            cout << "Enter author name: ";
            getline(cin, author);
            repositories[repoIndex].addCommit(Commit(message, author));
            break;
        }
        case 5: 
        {
            int repoIndex;
            cout << "Enter repository index: ";
            cin >> repoIndex;
            repositories[repoIndex].displayDetails();
            break;
        }
        case 6:
            saveRepositoriesToCSV(repositories, repoCount);
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
