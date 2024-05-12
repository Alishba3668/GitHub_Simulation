//#include <iostream>
//#include <string>
//
//using namespace std;
//
//// Custom unordered_set implementation
//template<typename T>
//class CustomSet {
//private:
//	static const int SIZE = 1000; // Assuming a fixed size for simplicity
//	bool elements[SIZE];
//
//public:
//	CustomSet() {
//		for (int i = 0; i < SIZE; ++i) {
//			elements[i] = false;
//		}
//	}
//
//	void insert(const T& val) {
//		int index = hash(val);
//		elements[index] = true;
//	}
//
//	void erase(const T& val) {
//		int index = hash(val);
//		elements[index] = false;
//	}
//
//	bool count(const T& val) {
//		int index = hash(val);
//		return elements[index];
//	}
//
//private:
//	int hash(const T& val) {
//		// Simple hash function for demonstration purposes
//		return val.length() % SIZE;
//	}
//};
//
//// Custom unordered_map implementation
//template<typename K, typename V>
//class CustomMap {
//private:
//	static const int SIZE = 1000; // Assuming a fixed size for simplicity
//	pair<K, V> elements[SIZE];
//
//public:
//	CustomMap() {}
//
//	void insert(const K& key, const V& val) {
//		int index = hash(key);
//		elements[index] = make_pair(key, val);
//	}
//
//	void erase(const K& key) {
//		int index = hash(key);
//		elements[index] = make_pair(K(), V()); // Clear the pair
//	}
//
//	V& operator[](const K& key) {
//		int index = hash(key);
//		return elements[index].second;
//	}
//
//	bool count(const K& key) {
//		int index = hash(key);
//		return elements[index].first == key;
//	}
//
//private:
//	int hash(const K& key) {
//		// Simple hash function for demonstration purposes
//		return key.length() % SIZE;
//	}
//};
//
//class GitHubSocialGraph {
//private:
//	CustomMap<string, CustomSet<string>> graph;
//
//public:
//	// Function to add a follow relationship between two users
//	void followUser(const string& follower, const string& followee) {
//		// Add the followee to the follower's following list
//		graph.insert(follower, CustomSet<string>());
//		graph[follower].insert(followee);
//	}
//
//	// Function to remove a follow relationship between two users
//	void unfollowUser(const string& follower, const string& followee) {
//		// Check if the follower exists and if they are following the followee
//		if (graph.count(follower) && graph[follower].count(followee)) {
//			// Remove the followee from the follower's following list
//			graph[follower].erase(followee);
//		}
//	}
//
//	// Function to print the users followed by a particular user
//	void printFollowing(const string& user) {
//		cout << user << " is following: ";
//		if (graph.count(user)) {
//			for (int i = 0; i < graph[user].size(); ++i) {
//				cout << graph[user].get(i) << " ";
//			}
//		}
//		cout << endl;
//	}
//};
//
//int main() {
//	GitHubSocialGraph socialGraph;
//
//	// Adding follow relationships
//	socialGraph.followUser("user1", "user2");
//	socialGraph.followUser("user1", "user3");
//	socialGraph.followUser("user2", "user1");
//	socialGraph.followUser("user2", "user3");
//
//	// Printing follow relationships
//	socialGraph.printFollowing("user1");
//	socialGraph.printFollowing("user2");
//
//	// Removing follow relationships
//	socialGraph.unfollowUser("user1", "user2");
//
//	// Printing follow relationships after unfollowing
//	socialGraph.printFollowing("user1");
//	socialGraph.printFollowing("user2");
//
//	return 0;
//}