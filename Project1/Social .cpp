//#include <iostream>
//using namespace std;
//
//template<typename T>
//class Vector
//{
//private:
//	T* arr;
//	int capacity;
//	int size;
//
//public:
//	Vector(int initialCapacity = 10) 
//	{
//		capacity = initialCapacity;
//		size = 0;
//		arr = new T[capacity];
//	}
//
//	~Vector()
//	{
//		delete[] arr;
//	}
//
//	void push_back(const T& element)
//	{
//		if (size == capacity)
//		{
//			resize();
//		}
//		arr[size++] = element;
//	}
//
//	void erase(int index)
//	{
//		if (index < 0 || index >= size) return;
//		for (int i = index; i < size - 1; ++i)
//		{
//			arr[i] = arr[i + 1];
//		}
//		size--;
//	}
//
//	T& operator[](int index)
//	{
//		return arr[index];
//	}
//
//	int getSize() const {
//		return size;
//	}
//
//private:
//	void resize()
//	{
//		capacity *= 2;
//		T* temp = new T[capacity];
//		for (int i = 0; i < size; ++i)
//		{
//			temp[i] = arr[i];
//		}
//		delete[] arr;
//		arr = temp;
//	}
//};
//
//class Graph
//{
//private:
//	int V;
//	Vector<Vector<int>> adjList;
//
//public:
//	Graph(int vertices) : V(vertices), adjList(vertices) {}
//
//	void addEdge(int v, int w)
//	{
//		adjList[v].push_back(w);
//	}
//
//	void removeEdge(int v, int w)
//	{
//		for (int i = 0; i < adjList[v].getSize(); ++i)
//		{
//			if (adjList[v][i] == w)
//			{
//				adjList[v].erase(i);
//				break;
//			}
//		}
//	}
//
//	void display()
//	{
//		for (int i = 0; i < V; ++i)
//		{
//			cout << "User " << i << " follows: ";
//			for (int j = 0; j < adjList[i].getSize(); ++j)
//			{
//				cout << adjList[i][j] << " ";
//			}
//			cout << endl;
//		}
//	}
//};
//
//int main()
//{
//	Graph socialNetwork(5);
//
//	socialNetwork.addEdge(0, 1);
//	socialNetwork.addEdge(0, 2);
//	socialNetwork.addEdge(1, 3);
//	socialNetwork.addEdge(2, 3);
//	socialNetwork.addEdge(3, 4);
//	socialNetwork.addEdge(4, 0); // Creating a cycle
//
//	cout << "Initial Social Network:" << endl;
//	socialNetwork.display();
//
//	// Unfollow a user
//	socialNetwork.removeEdge(0, 1);
//
//	cout << "\nSocial Network after User 0 unfollows User 1:" << endl;
//	socialNetwork.display();
//
//	return 0;
//}