
#ifndef MYVECTOR_H
#define MYVECTOR_H
#include<iostream>
#include "contact.h"
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<stdexcept>
#include<sstream>

using namespace std;


class outOfRange: public exception
{
	public:

		virtual const char* what() const throw()
		{
			//explanatory string that will be returned when what() is called
			return "Index is out of range"; 
		}
};


class isEmpty: public exception
{
	public:
		virtual const char* what() const throw()
		{
			//explanatory string that will be returned when what() is called
			return "Vector is empty."; 
		}
};


template <class T>//added
class MyVector
{
	private:
		T *data;	
		int v_size;						//current size of vector (number of elements in vector)
		int v_capacity;					//capacity of vector
	public:
		MyVector();						//No argument constructor	
		MyVector(int cap);				
		~MyVector();					//Destructor
		void push_back(T c);		//Add an element at the end of vector
		void erase(int index) throw(outOfRange);			//Removes an element from the index

		int size() const;				//Return current size of vector
		int capacity() const;			//Return capacity of vector
		bool empty() const; 			//Return true if the vector is empty, False otherwise
		void reserve(int new_cap);   //method to double the size if it has reached the max capacity

		void displayForSearch();	//different variation of display methods used to display the content of the vector
		void displayShort();
		void displayForPrintASC();
		void displayForPrintFav();
		void dumpForExport();
		string displayForDump(int i); 	//display method used with the key exportCSV

		void updateDetails(int record, int field);	//other methods used when performing the main methods of the BST
		void changeIsFav(int record, bool b);
		T& getElem(int i);

		friend class ContactBST;

};


#endif
