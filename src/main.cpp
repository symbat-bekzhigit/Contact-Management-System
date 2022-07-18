
//=================================================================================
// Name         : DS Assignment#3 
// Author       : 
// Version      : 1.0
// Date Created : 03-20-2022
// Date Modified: 
// Description  : Starter Code for Contact Management System using BST Tree in C++
// Copyright © 2022 Khalid Mengal and Mai Oudah. All rights reserved.
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>

#include "contact.h"//include all of these header files
#include "contactbst.h"
#include "myfunctions.h"

using namespace std;

//==========================================================
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"import <path>      :Import contacts from a CSV file"<<endl
		<<"export <path>      :Export contacts to a CSV file"<<endl
		<<"add                :Add a new contact"<<endl
		<<"edit <key>         :Update a contact's details"<<endl
		<<"del <key>          :Delete a contact"<<endl
		<<"searchFor <key>    :Search for a contact"<<endl
		<<"markfv <key>       :Mark as favourite"<<endl
		<<"umarkfv <key>      :Unmark as favourite"<<endl
		<<"printASC           :Print contacts in ascending order"<<endl
		<<"printDES           :Print contacts in descending order"<<endl
		<<"printfv            :Print all favourite contacts"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;


}

//==========================================================
int main(void)
{
	ContactBST myContactBST;//create BST tree
	string user_input;
	string command;
	string key;

	string k,fname,lname;

	while(true)
	{
		listCommands();
		cout<<">";

		getline(cin,user_input);//get userinput

		stringstream sstr(user_input);//and parse userinput into command and parameter(s)
		getline(sstr,command,' ');
		getline(sstr,key);
		
		Node* root = myContactBST.getRoot();	//get the root of the tree
		cout<<"----------------------------------"<<endl;
		if( user_input =="display")	myContactBST.printTree();//if the command will be "display", the bst tree will be printed (it is not included in the list of commands())

		//if the command will be searchFor...
		else if( command =="searchFor")
		{
			//check whether the key that the user entered exists in our tree
			if(myContactBST.search(root,key)==nullptr)
				cout<<"Record not found"<<endl;//null pointer will be returned if there's no such key in our tree

			else//if the key exists...
			{
				//call a method which takes pointer to the root node and the key as arguments and returns a pointer to the found node
				Node* n = myContactBST.search(root,key);//assign returned pointer to a pointer n
				MyVector<Contact>* vector = n->getData();//get access to the vector of the node

				cout<<vector->size()<<" record(s) found: "<<endl;//vector's size will correspond to the number of Contact objects inside a vector
				vector->displayForSearch();//call a display method tailored for this specific command
			}

		}

		//if the command will be add...
		else if( command =="add" or command=="a")
		{ 
			Contact* c = generateNewContact();//call this function which generates a new contact amd returns it
			fname = c->getFname();//get first name
			lname = c->getLname();//get last name
		
			k = generateKey(fname,lname);//generate a key out of this fname and last name

			myContactBST.insert_helper(k,c);//call insert_helper() method which will create a new node based on the passed key and contact values 

		} 

		//if the command will be edit...
		else if( command =="edit" or command=="e")
		{ 
			//check whether the key that the user entered exists in our tree
			if(myContactBST.search(root,key)==nullptr)
				cout<<"Record not found"<<endl;///null pointer will be returned if there's no such key in our tree

			else //if the key exists...
			{
				Node* n = myContactBST.search(root,key);//get access to a node which contains our key
				MyVector<Contact>* vector = n->getData();//get access to the vector of this node

				cout<<vector->size()<<" record(s) found: "<<endl;
				vector->displayShort();//call a display method tailored for this specific command

				if(vector->size()==1)//if there is only 1 record with that key, when editing the first name or the last name, 
									//we delete this node and generate a new node with an updated key
				{
					n = myContactBST.updateNew(n,key);//call a different updateNew() method which has the same argument and returning value as the update() method below
					cout<<endl;						//but a different content inside

					//myContactBST.printTree();
				}

				else//if there are more than 1 records of that key, when editing the first name or the last name,
					//we remove a particular record from the vector and create a new node for that record with an updated key
				{
					n = myContactBST.update(n,key);//call update method which takes pointer to the root node and the key as arguments and returns a pointer to the node
					cout<<endl;
			
					// cout<<"Updated vector contains: "<<endl;
					// vector->displayShort();
					//myContactBST.printTree();

				}
			}
		} 

		//if the command will be del...
		else if( command =="del" or command=="d")
		{ 
			//check whether the key that the user entered exists in our tree
			if(myContactBST.search(root,key)==nullptr)
				cout<<"Record not found"<<endl;//null pointer will be returned if there's no such key in our tree

			else //if the key exists...
			{
				Node* n = myContactBST.search(root,key);
				MyVector<Contact>* vector = n->getData();

				cout<<vector->size()<<" record(s) found: "<<endl;
				vector->displayShort();//call a display method tailored for this specific command

				if(vector->size()==1)//if there is only 1 record with that key, delete a node
				{
					myContactBST.remove_helper(key); //this remove_helper method will invoke del() method of BST
					cout<<endl;
					cout<<"The contact record has successfully been deleted!"<<endl;//notify the user that contact has been deleted

				}

				else//if there are more than 1 records of that key, delete a record from the corresponding vector
				{
					n = myContactBST.deleteFromVector(n);//deleteFromVector method will delete that record from the vector and returns a pointer to the deleted node
					cout<<endl;
					cout<<"The contact record has successfully been deleted!"<<endl;

					// cout<<"Updated vector contains: "<<endl;
					// vector->displayShort();
				
				}
			}
		}

		//if the command will be markfv...
		else if( command =="markfv")
		{
			//check if such key exists in our tree
			if(myContactBST.search(root,key)==nullptr)
				cout<<"Record not found"<<endl;

			else
			{
				Node* n = myContactBST.search(root,key);//get access to the node containing that key
				MyVector<Contact>* vector = n->getData();//get access to that node's vector

				cout<<vector->size()<<" record(s) found: "<<endl;
				vector->displayShort();
				cout<<endl;

				myContactBST.markFav(n,key);//invoke a method which takes pointer to the root node and the key as arguments 
										//and returns a Boolean flag showing if the operation was successful
			}
		}

		//if the command will be unmarkfv...
		else if( command =="unmarkfv")
		{
			//similar logic as with markfv command
			if(myContactBST.search(root,key)==nullptr)
				cout<<"Record not found"<<endl;

			else
			{
				Node* n = myContactBST.search(root,key);
				MyVector<Contact>* vector = n->getData();

				cout<<vector->size()<<" record(s) found: "<<endl;
				vector->displayShort();
				cout<<endl;

				myContactBST.unmarkFav(n,key); //invoke a method which takes pointer to the root node and the key as arguments 
										//and returns a Boolean flag showing if the operation was successful
			}
		}

		//if the command will be import...
		else if( command =="import")	
		{
		
			cout<<myContactBST.importCSV(root,key)<<endl;//call a method importCSV of BST which either returns the number of contacts read 
														//from the file as integer or returns -1 if a bad path is provided
		
		} 

		//if the command will be export...
		else if( command =="export")
		{
			cout<<myContactBST.exportCSV(root,key)<<endl;//call a method exportCSV of BST which either returns the number of contacts read 
														//from the file as integer or returns -1 if a bad path is provided
			
		} 

		else if( command =="printASC")	{myContactBST.printASC(root); cout<<endl;} //command to print the BST in ascending order
		else if( command =="printDES")	{myContactBST.printDES(root); cout<<endl;} //command to print the BST in descending order
		else if( command =="printfv")	{myContactBST.printFav(root); cout<<endl;} //command to print contacts in BST marked as favourite in ascending order
		else if( command == "help") continue; //if command is help, print the list of commands again
		else if( command == "exit") break; //if the comamnd is exit, exit the program
		else cout<<"Invalid command !!!"<<endl; 


	}

	return 0;
}



