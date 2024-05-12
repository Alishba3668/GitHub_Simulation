//#include <iostream>
//using namespace std;
//// Constants for the maximum number of users and maximum number of follow relationships
//const int MAX_USERS = 10;
//const int MAX_RELATIONSHIPS = 20;
//
//class GitHubSocialNetwork
//{
//private:
//	bool adjacencyMatrix[MAX_USERS][MAX_USERS] = { false }; // Adjacency matrix to store follow relationships
//	int numUsers = 0;
//
//public:
//	// Function to add a user to the social network
//	void addUser()
//	{
//		if (numUsers < MAX_USERS)
//		{
//			numUsers++;
//			cout << "User " << numUsers << " added to the social network." << endl;
//		}
//		else
//		{
//			cout << "Cannot add more users. Social network is full." << endl;
//		}
//	}
//
//	// Function to follow another user
//	void follow(int follower, int followed)
//	{
//		if (follower <= numUsers && followed <= numUsers)
//		{
//			adjacencyMatrix[follower - 1][followed - 1] = true;
//			cout << "User " << follower << " is now following user " << followed << "." << endl;
//		}
//		else
//		{
//			cout << "Invalid user IDs. Please provide valid user IDs." << endl;
//		}
//	}
//
//	// Function to unfollow another user
//	void unfollow(int follower, int followed)
//	{
//		if (follower <= numUsers && followed <= numUsers)
//		{
//			adjacencyMatrix[follower - 1][followed - 1] = false;
//			cout << "User " << follower << " has unfollowed user " << followed << "." << endl;
//		}
//		else
//		{
//			cout << "Invalid user IDs. Please provide valid user IDs." << endl;
//		}
//	}
//
//	// Function to display users followed by a particular user
//	void displayFollowedUsers(int user)
//	{
//		cout << "Users followed by user " << user << ": ";
//		for (int i = 0; i < numUsers; ++i)
//		{
//			if (adjacencyMatrix[user - 1][i])
//			{
//				cout << i + 1 << " ";
//			}
//		}
//		cout << endl;
//	}
//};
//
//int main()
//{
//	GitHubSocialNetwork socialNetwork;
//
//	// Adding users
//	socialNetwork.addUser(); // User 1
//	socialNetwork.addUser(); // User 2
//	socialNetwork.addUser(); // User 3
//
//							 // Simulating follow relationships
//	socialNetwork.follow(1, 2);
//	socialNetwork.follow(1, 3);
//	socialNetwork.follow(2, 3);
//
//	// Displaying users followed by user 1
//	socialNetwork.displayFollowedUsers(1);
//
//	// Unfollowing user 1 from user 2
//	socialNetwork.unfollow(1, 2);
//
//	// Displaying users followed by user 1 after unfollowing
//	socialNetwork.displayFollowedUsers(1);
//	
//	return 0;
//}