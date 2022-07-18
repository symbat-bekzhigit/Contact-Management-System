
#include "contactbst.h"
#include "myfunctions.h"
#include<iostream>
#include<sstream>
#include<cstdlib>
#include<fstream>
#include <algorithm> //library to use max(a,b) function

using namespace std;


////  methods i've added
/// Some of the methods (and comments) used here are borrowed from my previous lab exercises
//=================================================

//constructor of a node class
Node::Node(string key, MyVector<Contact>* contactVector)
{
	this->key = key;
	this->left = nullptr;
	this->right = nullptr;
	this->contactVector = contactVector;
}
//destrcutor of a node class
Node::~Node()
{
	//print this message to keep track of all the nodes that have been succesfully deleted
	cout<<"deleted.."<<this->key<<endl;
}

//=================================================

//constructor of a BST class
ContactBST::ContactBST()
{
	this->root=nullptr;
}

//destructor of a BST class
ContactBST::~ContactBST()
{
	//Keep removing the root of the tree untill it becomes empty
	while(root)
		root=del(root,root->key);
}

//Helper method for insert method
void ContactBST::insert_helper(string key, Contact* data)
{	

	root = add(root,key,data);
	
}

//Helper method for delete method 
void ContactBST::remove_helper(string key)
{
	root = del(root,key);
}

//==================================================================
//  This method prints a Binary Tree in 2D format
//  Created by Saurabh Ray 
//  Copyright © 2020 Saurabh Ray. All rights reserved.

void ContactBST::printTree(){
   char *space = (char *) "  ";
   int d = height(this->getRoot());
   int n = (1<<(d+1))- 1; // n = 2^(d+1)-1

   string *A = new string[n];
   bool *B = new bool[n];
   for(int i=0; i<n; ++i) 
   	  B[i]=false;

   printTreeHelper(A,B,root,n);

   cout<<"\nTree:"<<endl;
   for(int t=(n+1)/2; t>0; t=t/2){
        for(int j=0; j<n; j++){
            if( ((j+1)%t == 0) && B[j]){
                cout<<A[j];
                B[j] = false;
            }
            else{
                cout<<space;
            }
        }
        cout<<endl;
   }
   cout<<endl;
   delete [] A;
   delete [] B;
}

void ContactBST::printTreeHelper(string* A, bool* B, Node *ptr, int n){
    if(ptr!=nullptr){
        int mid = (n-1)/2;
        A[mid] = ptr->key;
        B[mid] = true;
        printTreeHelper(A,B,ptr->left,mid);
        printTreeHelper(A+(mid+1),B+(mid+1), ptr->right, mid);
    }
}


//method to get a height of the BST, which will be used when printing the BST
int ContactBST::height(Node *ptr)
{
	if(ptr==NULL)//initially, when the tree is empty, height will be -1
		return -1;
	//othewise, height = max number of edges from root to any leaf
	return max(height(ptr->left),height(ptr->right))+1;//the +1 corresponds to the edge connecting root and its child(ren)
}

//get a root of the BST
Node* ContactBST::getRoot()
{
	return root;//return root of the tree
}

//find the minimum key in the tree
Node* ContactBST::findMin(Node* ptr)
{
	Node* current  = ptr;//create a node current which will be initially equal to root
	//since minimum of the tree is the left-most node's key with no further left node
	while(current->left != NULL)//while current pointer will not be pointing to Null..
		current = current->left;//keep moving curernt to the left, down the tree
	
	return current;//return the left-most node
}

//add method which inserts a new node with specified key using binary search tree algorithm 
Node* ContactBST::add(Node* ptr,string key,Contact* data)
{
	if(ptr==NULL)//base case
	{
		MyVector<Contact> *v = new MyVector<Contact>(); //create new vector of objects of type Contact
		v->push_back(*data); //push back the data received as argument into that vector

		//after doing a binary search,once we find a pointer pointing to NUll
		Node* n = new Node(key,v);//create a new pointer n with a new key
		ptr = n;//update the link by setting ptr point to n

		return ptr;//return ptr
		delete n;//delete dynamically allocated pointer n
	}

	else//general case
	{
		//the less-than and more-than operators on strings does a lexicographical comparison on the strings

		if(ptr->getKey()>key)//if key is smaller than the key of the root/subroot..
			ptr->left = add(ptr->left,key,data);//recursively call insert() to pointer on the left side of root/subroot

		else if(ptr->getKey()<key)//if key is larger than the key of the root/subroot..
			ptr->right = add(ptr->right,key,data);

		else ////if key is equal to the key of the root/subroot..
		{
			MyVector<Contact>* v; //no need to create a new vector...
			v = ptr->getData();//... instead, get access to the vector of the current node...

			v->push_back(*data);//.. and push back the data received as argument into that vector
		}
	}
	return ptr;//return pointer to the current node
}

//update method which is tailored for when there are 2 or more records of the key
Node* ContactBST::update(Node* ptr, string key)//if there are more than 1 records of that key, when editing the first name or the last name,
					//we remove a particular record from the vector and create a new node for that record with an updated key
{
	string record, field, k;
	string editMore = "y";//initially, editMore should be "y" for a folowing while loop to run
	string newValue;

	cout<<endl;
	cout<<"Please select the record you want to edit: ";
	getline(cin,record); //ask from the user the record that he/she wants to edit

	while(editMore == "y")
	{
		cout<<"Which field do you want to edit: 1)First Name, 2)Last Name, 3)Email, 4)Phone#, 5)City, or 6)Country: ";
		getline(cin,field);

		MyVector<Contact>* v;
		v = ptr->getData();//get access to the vector of the current node

		if(field == "1" || field == "2")//if the user wants to edit the first name or the last name
		{

			if(field == "1")//first name
			{
				cout<<"Please enter the new first name: ";
				getline(cin,newValue); //get a new value for the first name

				Contact* c =  new Contact("", "", "", "", "", "", ""); //instantiate a Contact object with empty strings passed as arguments
				c->setFname(newValue);//change the first name of the created Contact obj into a value provided by a user
				c->setLname(v->data[stoi(record)-1].getLname()); //copy details from the current vector's object to a new contact obj that we created
				c->setEmail(v->data[stoi(record)-1].getEmail());  //by calling the specific getter method for each of the remaining arguments of the Contact object
				c->setPrimaryPhone(v->data[stoi(record)-1].getPrimaryPhone());
				c->setCity(v->data[stoi(record)-1].getCity());
				c->setCountry(v->data[stoi(record)-1].getCountry());
			
				k = generateKey(newValue,c->getLname()); //generate a key based on the updated first name and old last name values
				this->insert_helper(k,c);//create a new node with this key and insert it into our BST
				cout<<"New contact with an updated first name has been generated!"<<endl; //inform the user
			}

			else if(field == "2")//last name
			{
				cout<<"Please enter the new last name: ";
				getline(cin,newValue);
				
				Contact* c =  new Contact("", "", "", "", "", "", "");//instantiate a Contact object with empty strings passed as arguments
				c->setFname(v->data[stoi(record)-1].getFname());
				c->setLname(newValue);//change the last name of the created Contact obj into a value provided by a user
				c->setEmail(v->data[stoi(record)-1].getEmail());//copy details from the current vector's object to a new contact obj that we created
				c->setPrimaryPhone(v->data[stoi(record)-1].getPrimaryPhone()); //by calling the specific getter method for each of the remaining arguments of the Contact object
				c->setCity(v->data[stoi(record)-1].getCity());
				c->setCountry(v->data[stoi(record)-1].getCountry());
			
				k = generateKey(c->getFname(),newValue);//generate a key based on the updated last name and old first name values
				this->insert_helper(k,c);//create a new node with this key and insert it into our BST
				cout<<"New contact with an updated last name has been generated."<<endl;
			}

			v->erase(stoi(record)-1); //remove the old record from the vector
		}

		else //if the user wants to edit the fields other than the first name or the last name
		{
			v->updateDetails(stoi(record), stoi(field)); //call this method which will just update the field requested by the user into a new value
		}

		cout<<"Do you want to edit another field (y/n)? ";
		getline(cin,editMore); //ask the user if he/she wants to edit another field
		cout<<endl;

		if(editMore == "n") //break out of the while loop if the user answers no
		{
			cout<<"The contact record has succesfully been updated!"<<endl;//inform the reader
			break;
		}
	}

	cin.clear();//clear cin cache
	cin.sync();

	return ptr;//return a pointer to the node
}

//update method which is tailored for when there is only 1 of the key
Node* ContactBST::updateNew(Node* ptr, string key)//if there is only 1 record with that key, when editing the first name or the last name, 
									//we delete this node and generate a new node with an updated key
{
	string record, field, k;
	string editMore = "y";
	string newValue;

	cout<<"Please select the record you want to edit: ";
	getline(cin,record);

	while(editMore == "y")
	{
		cout<<"Which field do you want to edit: 1)First Name, 2)Last Name, 3)Email, 4)Phone#, 5)City, or 6)Country: ";
		getline(cin,field);

		MyVector<Contact>* v;
		v = ptr->getData();

		if(field == "1" || field == "2")//if the user wants to edit the first name or the last name
		{

			if(field == "1")//first name
			{
				cout<<"Please enter the new first name: ";
				getline(cin,newValue);

				Contact* c =  new Contact("", "", "", "", "", "", "");//instantiate a Contact object with empty strings passed as arguments
				c->setFname(newValue);//change the first name of the created Contact obj into a value provided by a user
				c->setLname(v->data[stoi(record)-1].getLname());//for other arguments of Contact obj, copy details from the vector's current object to a new contact obj that we created
				c->setEmail(v->data[stoi(record)-1].getEmail());
				c->setPrimaryPhone(v->data[stoi(record)-1].getPrimaryPhone());
				c->setCity(v->data[stoi(record)-1].getCity());
				c->setCountry(v->data[stoi(record)-1].getCountry());
			
				k = generateKey(newValue,c->getLname());//generate a key based on the updated last name or first name values
				this->insert_helper(k,c);//create a new node with this key and insert it into our BST
				cout<<"New contact with and updated first name has been generated."<<endl;
			}

			else if(field == "2")//last name
			{
				cout<<"Please enter the new last name: ";
				getline(cin,newValue);
				
				Contact* c =  new Contact("", "", "", "", "", "", "");//instantiate a Contact object with empty strings passed as arguments
				c->setFname(v->data[stoi(record)-1].getFname());
				c->setLname(newValue);//change the last name of the created Contact obj into a value provided by a user
				c->setEmail(v->data[stoi(record)-1].getEmail());//for other arguments of Contact obj, copy details from the vector's current object to a new contact obj that we created
				c->setPrimaryPhone(v->data[stoi(record)-1].getPrimaryPhone());
				c->setCity(v->data[stoi(record)-1].getCity());
				c->setCountry(v->data[stoi(record)-1].getCountry());
			
				k = generateKey(c->getFname(),newValue);//generate a key based on the updated last name or first name values
				this->insert_helper(k,c);//create a new node with this key and insert it into our BST
				cout<<"New contact with and updated last name has been generated."<<endl;
			}

			this->remove_helper(ptr->getKey()); //remove the old node from the tree
			cout<<"Old contact has been removed."<<endl;

		}

		else //if the user wants to edit the fields other than the first name or the last name
		{
			v->updateDetails(stoi(record), stoi(field));//call this method which will just update the field requested by the user into a new value
		}

		cout<<"Do you want to edit another field (y/n)? ";
		getline(cin,editMore); //ask the user if he/she wants to edit another field

		if(editMore == "n") //break out of the while loop if the user answers no
		{
			cout<<"The contact record has succesfully been updated!"<<endl;
			break;
		}
	}

	cin.clear();//clear cin cache
	cin.sync();

	return ptr;//return a pointer to the node
}

//search for the specific key in the tree
Node* ContactBST::search(Node *ptr,string key)
{
	//base cases
	if(ptr==NULL)//if there is no such key in the tree..
		return ptr;//this method will return Null

	if(ptr->getKey()==key)
		return ptr;//if ptr->key == key we were searching for, return pointer to node with the specific key
	
	//general cases
	if(ptr->getKey()>key)//if key is smaller than the key of the root/subroot..
		return search(ptr->left,key);//recursively call search() with ptr->left now being the subroot

	else if(ptr->getKey()<key)//if key is larger than the key of the root/subroot..
		return search(ptr->right,key);//recursively call search() with ptr->right now being the subroot
	
}

//delete method which is invoked when if there is only 1 record with that key
Node* ContactBST::del(Node *ptr,string key)
{
	//base case #1: if the key was not found
	if(ptr == NULL)
		return ptr;

	//base case #2: if the key was found and the node containing that key doesn't have any children
	if(key == ptr->getKey() && ptr->left == NULL && ptr->right == NULL){
		delete ptr;//set ptr of that node equal to Null
		return nullptr;//return ptr

	}
	//base case #3: if the key was found and the node containing that key doesn't have any right subtree
	if(key == ptr->getKey() && ptr->left != NULL && ptr->right == NULL){
		Node* temp = ptr->left;//to keep track of the left node of the current ptr, set temporary pointer to ptr->left before deleting ptr
		delete ptr;//delete the pointer with the specified key
		return temp;//return temporary pointer
	}

	//base case #4: if the key was found and the node containing that key doesn't have any left subtree
	if(key == ptr->getKey() && ptr->left == NULL && ptr->right != NULL){
		Node* temp = ptr->right;//to keep track of the left node of the current ptr, set temporary pointer to ptr->left before deleting ptr
		delete ptr;//delete the pointer with the specified key
		return temp;//return temporary pointer
	}

	//base case #5: if the key was found and the node containing that key has both left and right subtrees
	if(key == ptr->getKey() && ptr->left != NULL && ptr->right != NULL){

		Node* min = findMin(ptr->right);//find the node with the min value from the right subtree
		ptr->key = min->key;//swap ptr and min by updating the key of the current ptr with the key of the min node...
		min->key = key;//...and changing the key of the min node to the old key of the ptr
		ptr->right = del(ptr->right,key);//now that ptr and min have been swapped, call remove() to recursively
											//remove the node with the specified key
		return ptr;//return pointer to the current node

	}

	//general case
	if(key<ptr->getKey())//if key is smaller than the key of the root/subroot..
			ptr->left = del(ptr->left,key);//recursively call remove() to pointer on the left side of root/subroot
	
	else if(key>ptr->getKey())//if key is larger than the key of the root/subroot..
			ptr->right = del(ptr->right,key);

	else if(key>ptr->getKey())//if key is equal to the key of the root/subroot..
			ptr->right = del(ptr->right,key);

	return ptr;//return pointer to the current node
}

//delete method which is invoked when we need to delete object from the vector, i.e when there are more than 1 records of that key
Node* ContactBST::deleteFromVector(Node *ptr)
{
	string record;

	cout<<"Please select the record you want to delete: ";
	getline(cin,record);//get the record that user wants to delete

	MyVector<Contact>* v;
	v = ptr->getData();//get access to the vector of the current node
	v->erase(stoi(record)-1);//remove the record from the vector 
							// we convert record to int and subtract 1 because if user enters 2, for ex, that record is located in the 1th position in our vector

	cin.clear();//clear the cin cache
	cin.sync();

	return ptr;//return pointer to the node where these changes have been made
}

//method which takes pointer to the node and the key as arguments and allows the user to mark the contact as favourite
bool ContactBST::markFav(Node* ptr, string key)
{
	string record;
	bool isSuccess = true;
	cout<<"Please select the record you want to mark as favourite: ";
	getline(cin,record);//get the record that the user wants to mark as fav

	MyVector<Contact>* v;
	v = ptr->getData();//get access to the vector of the current node

	v->changeIsFav(stoi(record),true);//call changeIsFav method which will change the isFav value of the Contact to true
	//get the key and email of the contact that has been modified, and print the corresponfing message to the user
	cout<<ptr->getKey()<<" ("<<v->getElem(stoi(record)-1).getEmail()<<") "<<"has successfully been marked as favourite."<<endl;

	cin.clear();
	cin.sync();

	return isSuccess;//returns a Boolean flag showing if the operation was successful
}

//method which takes pointer to the node and the key as arguments and allows the user to unmark the contact as favourite
bool ContactBST::unmarkFav(Node* ptr, string key)
{
	string record;
	bool isSuccess = true;
	cout<<"Please select the record you want to unmark as favourite: ";
	getline(cin,record);//get the record that the user wants to unmark as fav

	MyVector<Contact>* v;
	v = ptr->getData();

	v->changeIsFav(stoi(record),false);//call changeIsFav method which will change the isFav value of the Contact to false
	//get the key and email of the contact that has been modified, and print the corresponfing message to the user
	cout<<ptr->getKey()<<" ("<<v->getElem(stoi(record)-1).getEmail()<<") "<<"has successfully been unmarked as favourite."<<endl;

	cin.clear();//clear cin cache
	cin.sync();

	return isSuccess;//returns a Boolean flag showing if the operation was successful
}

//print contacts in ascending order
void ContactBST::printASC(Node* ptr)
{
	//base case
	if(ptr == NULL) //base case occurs when we reach the leaf i.e a node pointing to NULL
		return;

	//recursive case
	else
		//in order to print in ascending order, we need to print the keys of the left sub-tree, then print the keys of the right sub-tree
	{	
		printASC(ptr->left);

		MyVector<Contact>* v;
		v = ptr->getData();//get access to the vector of the current node
		v->displayForPrintASC();//call s specific display function tailored for the printASC, printDES functions

		printASC(ptr->right);
	}
}

//print contacts in descending order
void ContactBST::printDES(Node* ptr)
{
	//base case
	if(ptr == NULL) //base case occurs when we reach the leaf i.e a node pointing to NULL
		return;

	//recursive case
	else
	{	//in order to print in descending order, we need to print the keys of the right sub-tree, then print the keys of the left sub-tree
		printDES(ptr->right);

		MyVector<Contact>* v;
		v = ptr->getData();//get access to the vector of the current node
		v->displayForPrintASC();//call s specific display function tailored for the printASC, printDES functions

		printDES(ptr->left);
	}

}

//print contacts marked as favorite in ascending order
void ContactBST::printFav(Node* ptr)
{
	//base case
	if(ptr == NULL) //base case occurs when we reach the leaf i.e a node pointing to NULL
		return;

	//general case
	else
	{	//in order to print in ascending order, we need to print the keys of the left sub-tree, then print the keys of the right sub-tree
		printFav(ptr->left);

		MyVector<Contact>* v;
		v = ptr->getData();//get access to the vector of the current node
		v->displayForPrintFav();//call s specific display function tailored for the printing only the contacts that are marked as favourite

		printFav(ptr->right);
	}
}

//method which takes pointer to the node and path as arguments and loads all the contacts from the CSV file at path to the binary search tree
int ContactBST::importCSV(Node* ptr, string path)
{
	int n=0;
	ifstream fin; 
	fin.open(path, ios::in);//open the file in reading mode

	if (fin.is_open())//if the file has been opened
	{
		string line;
		string fname,lname,email,primaryPhone,city,country,tempIsFav;
		string k;
		bool isFav;
       
        while (getline(fin,line))//read the content of the file line by line
        {
            //remove all the spaces from our string that is stored in variable line
            line = removeSpaces(line);

            stringstream sstr(line);//used for breaking words
            getline(sstr,fname,',');//get fname, lname, email, etc. values from our string
            getline(sstr,lname,',');
            getline(sstr,email,',');
            getline(sstr,primaryPhone,',');
            getline(sstr,city,',');
            getline(sstr,country,',');
            getline(sstr,tempIsFav);

            //since the isfav value that we read from our string is of type string, convert it to a corresponding boolean value
            if(stoi(tempIsFav) == 1) isFav = true; 
            else isFav = false;

            //create a new contact based on the parameters that we got from reading the string 
            Contact* c =  new Contact(fname, lname, email, primaryPhone, city, country, isFav);
			k = generateKey(fname,lname);//generate the key for that particular contact
			this->insert_helper(k,c);//create a new node with this key and contact, and insert it into our BST
			n++;//every time we created a new contact, n will be incremented, that way we will get the total num of contact that we read from the file

            if(fin.eof()) break; //if the file reading has reached the end, eof() will return true and while loop will break
        }
		fin.close();//close the fle
	}
	else n=-1;

	return n;//the method either returns the number of contacts read from the file as integer or returns -1 if a bad path is provided
}


int ctr = 0; //global variable that is used as an index when putting strings inside an array in the below method
				//i declared it as a global var becuase the below method dumpASC is a recursive function

//helper method used when writing contacts from BST to file in ascending order
void ContactBST::dumpASC(Node* ptr, string array[]) 
{
	//this method will allow us to recursively naviagate our BST to get keys in the ascnding order, 
	string s;// for each Contact inside the node we get the Contact's details (such as email etc.) and store all of them in this string

	//base case
	if(ptr == NULL) //base case occurs when we reach the leaf i.e a node pointing to NULL
		return;

	//general case
	else
	{	
		dumpASC(ptr->left,array);

		MyVector<Contact>* v;
		v = ptr->getData();//get access to the vector of the current node which contains objects of type Contact

		for(int i=0; i<v->size();i++)
		{
			s = v->displayForDump(i);//call specific displayForDump() method which will concatenate all details of the contac in one string and return it
			array[ctr] = s;//store strings obtained from every contact inside the array which was passed as an argument
			ctr++;//every time we add a string to our array, ctr will be incremented, thus it will aloows us to calculate the number of contacts written to the file
		}
		
		dumpASC(ptr->right,array);//then print the keys of the right sub-tree
	}

}

//method which takes pointer to the root node and path as arguments and writes all the contacts from the binary search tree to a CSV file in an ascending order
int ContactBST::exportCSV(Node* ptr, string path)//works fine
{
	int n;
	string array[100];//create an array of string with size 100 -- here i chose 100 initially, but this value can be modified depending on max num of contact we're planning to have in our tree
	ofstream fout; //create an ofstream variable
	fout.open(path,ios::out | ios::trunc);//open the file in a writing mode
											//when the file is opened, the old contents are immediately removed

	if(fout.is_open())//if file has been opened
	{
	    dumpASC(ptr,array);//call our helper dumpASC function which will modify the array that we passed as an argument by filling it with the strings 
	    					//created by cocnatenating the details of every contact

		for(int j=0; j<ctr; j++)
			fout<<array[j]<<endl;//write each string in our array into our csv file

		n = ctr; //n will be equal to the global var value ctr which corresponds to the number of contact written to a file
		fout.close();//close the file
	
	}
	else n = -1;//n will equal -1 if file cannot be created

	ctr = 0;//update ctr value to 0 after succesfully dumping to the file in this current session
	
  	return n;//The method either returns the number of contacts written to the file as integer or returns -1 if file cannot be created
}
