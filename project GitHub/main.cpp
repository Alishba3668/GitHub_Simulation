#include "Repository.h"

using namespace std;

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
    Repository repositories[10];
    int repoCount = 0;

    // Load existing data
    loadRepositoriesFromCSV(repositories, repoCount);

    bool running = true;
    while (running) {
        cout << "\nMain Menu:\n";
        cout << "1. Repository Management\n";
        cout << "2. Save and Exit\n";
        cout << "Enter your choice: ";
        int mainChoice;
        cin >> mainChoice;

        switch (mainChoice) {
        case 1: {  // Repository management
            int repoChoice;
            cout << "\nRepository Management Menu:\n";
            cout << "1. Create Repository\n";
            cout << "2. Add File to Repository\n";
            cout << "3. Delete File from Repository\n";
            cout << "4. Add Commit to Repository\n";
            cout << "5. View Repository Details\n";
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
            default:
                cout << "Invalid choice! Please try again." << endl;
            }
            break;
        }
        case 2:  // Save and Exit
            saveRepositoriesToCSV(repositories, repoCount);
            cout << "Exiting program..." << endl;
            running = false;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
            break;
        }
    }

    return 0;
}
