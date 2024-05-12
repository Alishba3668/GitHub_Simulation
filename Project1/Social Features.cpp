//void githubsimulation::Follow(const string& follower, const string& following) {
//	if (users.find(follower) == users.end() || users.find(following) == users.end()) {
//		cout << "no user found !" << endl;
//		return;
//	}
//
//	followGraph[follower].insert(following);
//	users[follower].Followers_add();
//	cout << follower << " is now follow  " << following << endl;
//}
//
//void githubsimulation::Unfollow(const string& follower, const string& following) {
//
//	bool Find_Follow = users.find(follower) != users.end();
//	bool followingFound = users.find(following) != users.end();
//
//	if (!Find_Follow || !followingFound) {
//		cout << "no user exist " << endl;
//		return;
//	}
//
//
//	bool isFollowing = false;
//	auto add_f = followGraph.find(follower);
//	if (add_f != followGraph.end()) {
//		auto followingIt = add_f->second.find(following);
//		if (followingIt != add_f->second.end()) {
//			add_f->second.erase(followingIt);
//			isFollowing = true;
//		}
//	}
//
//	if (isFollowing) {
//		users[follower].Followers_delete();
//		cout << follower << " is unfollow " << following << endl;
//	}
//	else {
//		cout << follower << " was not follow " << following << endl;
//	}
//}