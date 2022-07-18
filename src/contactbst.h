#ifndef ContactBST_H
#define ContactBST_H

#include<iostream>
#include<sstream>
#include<cstdlib>
#include <algorithm> //library to use max(a,b) function
#include "contact.h"
#include "myvector.h" 

using namespace std;

//our BST will comprise of nodes
class Node
{
	private:
		string key; //noda has a key...
		MyVector<Contact>* contactVector; //data, which, in our case, is a vector containing objects of type Contact
		Node* left; //pointer to the left child
		Node* right; //pointer to the right child
	public:
		Node(string key, MyVector<Contact>* contactVector);//constrcutors
		~Node();
		string getKey() { return this->key;} //getter method for a key
		MyVector<Contact>* getData() { return this->contactVector;} //getter method for a data
		friend class ContactBST; //our ContactBST class is declared as a friend of Node class
};

//

//=============================================================================
class ContactBST
{
	private:
		Node* root;
	public:
		ContactBST();									//constructor
		~ContactBST();									//destructor
		Node* getRoot();						//returns the root of the Tree
		Node* add(Node* ptr,string key, Contact* data);		//add key into tree/subtree with root ptr
		Node* update(Node* ptr, string key); //Edit the node with key --- ADD
		Node* del(Node* ptr,string key);		//Delete a node with key from the tree/subtree with root
		Node* search(Node* ptr,string key);	//Find and returns the node with key
		bool markFav(Node* ptr, string key);  //Mark a contact as favorite  --- ADD
		bool unmarkFav(Node* ptr, string key);  //Unmark a contact as favorite  --- ADD
		void printASC(Node* ptr);			//Print the data at nodes in an ascending order --- ADD
		void printDES(Node* ptr);			//Print the data at nodes in a descending order --- ADD
		void printFav(Node* ptr);           //Print the favorite data at nodes in an ascending order --- ADD
		int importCSV(Node* ptr, string path); //Load all the contacts from the CSV file to the BST --- ADD
		int exportCSV(Node* ptr, string path); //Export all the contacts from the BST to a CSV file in an ascending order --- ADD

	public:	//helper methods
		void insert_helper(string key, Contact* data);				//Helper method for insert method
		void remove_helper(string key);								//Helper method for remove method
	private:
		void printTreeHelper(string* A, bool* B, Node* ptr, int n); //Helper method for PrintTree()


	//  methods that i've added
	public:
		int height(Node *ptr);
		void printTree();
		Node* findMin(Node *ptr);
		Node* deleteFromVector(Node *ptr);
		void dumpASC(Node* ptr, string array[]);
		Node* updateNew(Node* ptr, string key);
};




#endif