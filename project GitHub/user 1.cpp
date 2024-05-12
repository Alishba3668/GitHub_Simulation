//#include <iostream>
//#include <string>
//
//using namespace std;
//class LinkedList
//{
//public:
//    struct Node
//    {
//        string data;
//        Node* next;
//    };
//
//    Node* head; 
//    int size;   
//
//    LinkedList()
//    {
//        head = nullptr;
//        size = 0;
//    }
//
//    ~LinkedList()
//    {
//        Node* current = head;
//        while (current != nullptr)
//        {
//            Node* next = current->next;
//            delete current;
//            current = next;
//        }
//    }
//
//    void add(const string& data)
//    {
//        Node* newNode = new Node{ data, head };
//        head = newNode;
//        size++;
//    }
//
//    void remove(const string& data)
//    {
//        if (head == nullptr)
//        {
//            return;
//        }
//
//        if (head->data == data)
//        {
//            Node* toDelete = head;
//            head = head->next;
//            delete toDelete;
//            size--;
//            return;
//        }
//
//        Node* current = head;
//        while (current->next != nullptr)
//        {
//            if (current->next->data == data)
//            {
//                Node* toDelete = current->next;
//                current->next = current->next->next;
//                delete toDelete;
//                size--;
//                return;
//            }
//            current = current->next;
//        }
//    }
//
//    int getSize() const
//    {
//        return size;
//    }
//
//    bool contains(const string& data) const
//    {
//        Node* current = head;
//        while (current != nullptr)
//        {
//            if (current->data == data)
//            {
//                return true;
//            }
//            current = current->next;
//        }
//        return false;
//    }
//};
//
//class User
//{
//public:
//    string username;
//    string password;
//    LinkedList following;
//    LinkedList followers;
//    User* next;
//
//    User(const string& uname, const string& pwd)
//    {
//        username = uname;
//        password = pwd;
//        next = nullptr;
//    }
//};
//
//class UserAccounts
//{
//private:
//    int capacity;
//    User** table; // Hash table to storing users
//
//    int hashFunction(const string& key)
//    {
//        int hash = 0;
//        int prime = 31; // Prime multiplier for better distribution
//        for (char c : key)
//        {
//            hash = (hash * prime + c) % capacity;
//        }
//        return hash;
//    }
//
//public:
//    UserAccounts(int size = 10) : capacity(size)
//    {
//        table = new User * [capacity];
//        for (int i = 0; i < capacity; i++)
//        {
//            table[i] = nullptr;
//        }
//    }
//
//    ~UserAccounts()
//    {
//        for (int i = 0; i < capacity; i++)
//        {
//            User* current = table[i];
//            while (current != nullptr)
//            {
//                User* next = current->next;
//                delete current;
//                current = next;
//            }
//        }
//        delete[] table;
//    }
//
//    bool registerUser(const string& username, const string& password)
//    {
//        int index = hashFunction(username);
//
//        User* current = table[index];
//        while (current != nullptr)
//        {
//            if (current->username == username)
//            {
//                return false;
//            }
//            current = current->next;
//        }
//
//        User* newUser = new User(username, password);
//        newUser->next = table[index]; // chaining
//        table[index] = newUser;
//
//        return true; // User registered
//    }
//
//    // Login a user
//    bool login(const string& username, const string& password)
//    {
//        int index = hashFunction(username);
//
//        User* current = table[index];
//        while (current != nullptr)
//        {
//            if (current->username == username && current->password == password)
//            {
//                return true;
//            }
//            current = current->next;
//        }
//
//        return false;
//    }
//   
//    User* getProfile(const string& username) // user profile
//    {
//        int index = hashFunction(username);
//
//        User* current = table[index];
//        while (current != nullptr)
//        {
//            if (current->username == username)
//            {
//                return current; // User found
//            }
//            current = current->next;
//        }
//
//        return nullptr;
//    }
//
//    bool follow(const string& follower, const string& followee)  // Follow user
//    {
//        User* followerUser = getProfile(follower);
//        User* followeeUser = getProfile(followee);
//
//        if (followerUser && followeeUser)
//        {
//            if (!followerUser->following.contains(followee))
//            {
//                followerUser->following.add(followee);
//                followeeUser->followers.add(follower);
//                return true;
//            }
//        }
//        return false;
//    }
//
//    // Unfollow a user
//    bool unfollow(const string& follower, const string& followee)
//    {
//        User* followerUser = getProfile(follower);
//        User* followeeUser = getProfile(followee);
//        if (followerUser && followeeUser)
//        {
//            if (followerUser->following.contains(followee))
//            {
//                followerUser->following.remove(followee);
//                followeeUser->followers.remove(follower);
//                return true;
//            }
//        }
//        return false;
//    }
//};
//
//int main()
//{
//    UserAccounts userAccounts;
//    bool running = true;
//    while (running)
//    {
//        cout << "\nUser Account Menu:\n";
//        cout << "1. Register User\n";
//        cout << "2. Login\n";
//        cout << "3. Follow User\n";
//        cout << "4. Unfollow User\n";
//        cout << "5. View Profile\n";
//        cout << "6. Exit\n";
//
//        int choice;
//        cin >> choice;
//
//        switch (choice)
//        {
//        case 1: // Register User
//        {
//            cout << "Enter username: ";
//            string username;
//            cin >> username;
//
//            cout << "Enter password: ";
//            string password;
//            cin >> password;
//
//            if (userAccounts.registerUser(username, password))
//            {
//                cout << "User registered successfully.\n";
//            }
//            else
//            {
//                cout << "Username already exists.\n";
//            }
//            break;
//        }
//
//        case 2: // Login
//        {
//            cout << "Enter username: ";
//            string username;
//            cin >> username;
//
//            cout << "Enter password: ";
//            string password;
//            cin >> password;
//
//            if (userAccounts.login(username, password))
//            {
//                cout << "Login successful.\n";
//            }
//            else
//            {
//                cout << "Invalid credentials.\n";
//            }
//            break;
//        }
//
//        case 3: // Follow User
//        {
//            cout << "Enter your username: ";
//            string follower;
//            cin >> follower;
//
//            cout << "Enter username to follow: ";
//            string followee;
//            cin >> followee;
//
//            if (userAccounts.follow(follower, followee))
//            {
//                cout << "Followed successfully.\n";
//            }
//            else
//            {
//                cout << "Follow failed. Check if usernames are correct.\n";
//            }
//            break;
//        }
//
//        case 4: // Unfollow User
//        {
//            cout << "Enter your username: ";
//            string follower;
//            cin >> follower;
//
//            cout << "Enter username to unfollow: ";
//            string followee;
//            cin >> followee;
//
//            if (userAccounts.unfollow(follower, followee))
//            {
//                cout << "Unfollowed successfully.\n";
//            }
//            else
//            {
//                cout << "Unfollow failed. Check if usernames are correct.\n";
//            }
//            break;
//        }
//
//        case 5: // View Profile
//        {
//            cout << "Enter username to view profile: ";
//            string username;
//            cin >> username;
//
//            User* user = userAccounts.getProfile(username);
//            if (user != nullptr) {
//                cout << "Profile of " << user->username << ":\n";
//                cout << "Followers: " << user->followers.getSize() << "\n";
//                cout << "Following: " << user->following.getSize() << "\n";
//            }
//            else
//            {
//                cout << "User not found.\n";
//            }
//            break;
//        }
//
//        case 6: // Exit
//            running = false;
//            break;
//
//        default:
//            cout << "Invalid choice. Try again.\n";
//            break;
//        }
//    }
//
//    return 0;
//}
