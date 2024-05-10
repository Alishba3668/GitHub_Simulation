//// blueprint of repository in which we are going to use linklist 
//// for structure of repositories and creation and deletion of repository
//// A linked list to store commits and File
//
//#include <iostream>
//#include <string>
//using namespace std;
//
//struct Commit
//{
//    string message;
//    Commit* next;
//};
//struct File
//{
//    string name;
//    File* next;
//};
//struct Repository
//{
//    string name;
//    bool isPublic;
//    Commit* commits;
//    File* files;
//    Repository(string n, bool view)
//    {
//        name = n;
//        isPublic = view;
//        commits = nullptr;
//        files = nullptr;
//    }
//};
//struct TreeNode
//{
//    Repository* repository;
//    TreeNode* parent;
//    TreeNode* child;
//    TreeNode* sibling;
//    TreeNode(Repository* repo)
//    {
//        repository = repo;
//        parent = nullptr;
//        child = nullptr;
//        sibling = nullptr;
//    }
//};
//class RepositoryManager
//{
//private:
//    TreeNode* root;
//public:
//    RepositoryManager()
//    {
//        root = nullptr;
//    }
//    void createRepository(string name, bool isPublic) // creating a new repository
//    {
//        Repository* repo = new Repository(name, isPublic);
//        TreeNode* newNode = new TreeNode(repo);
//        if (root == nullptr)
//        {
//            root = newNode;
//        }
//        else
//        {
//            // tree insertion logic
//        }
//    }
//    void deleteRepository(string name) //Deletion 
//    {
//        // deletion logic
//        //Users have the option to delete their repositories
//    }
//    void forkRepository(string sourceRepoName, string newRepoName)
//    {
//        // Implement repository forking logic
//        //Users can copy the public repository including files and commits from any other use.
//    }
//    void addCommit(string repoName, string commitMessage)//commit
//    {
//        // commit addition logic
//        //Implement commits, allowing users to add “commits” to their repositories
//    }
//    void viewStats(string repoName)
//    {
//        // stats viewing logic
//        //Users can view repository stats such as : Repo name, Repo files, Repo commits, Repo fork
//            //count
//    }
//
//    // Function to add a file to a repository
//    void addFile(string repoName, string fileName)
//    {
//        // File addition logic
//        // Users can add/push files to a specific repository.
//    }
//    void deleteFile(string repoName, string fileName)
//    {
//        // deletion logic
//        //Users can add/push files to a specific repository.
//        // Users can delete files from a specific repository.
//    }
//};
//
//int main()
//{
//    RepositoryManager manager;
//    manager.createRepository("MyRepo", true);
//    manager.addCommit("MyRepo", "Initial commit");
//    manager.viewStats("MyRepo");
//    manager.addFile("MyRepo", "example.txt");
//    manager.deleteFile("MyRepo", "example.txt");
//    manager.deleteRepository("MyRepo");
//
//    return 0;
//}
