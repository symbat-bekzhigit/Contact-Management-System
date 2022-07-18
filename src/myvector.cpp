
#include "contact.h"
#include "myvector.h" 

#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<stdexcept>
#include<sstream>
#include<fstream>

using namespace std;


//referenced the logic of defining some of the vector functions from the lecture slides and my previous lab submissions


//no argument constructor; sets v_capacity as 0 , v_size as 0, and pointer data to NULL
template <class T>
MyVector<T>::MyVector() : v_capacity(0), v_size(0), data(NULL) {}

template <class T>
MyVector<T>::MyVector(int cap) : v_capacity(cap), v_size(0), data(new T [cap]) {}

//destrcutor of the vector class
template <class T>
MyVector<T>::~MyVector()
{ if(data != NULL) delete [] data; }

//returns the current size of the vector
template <class T>
int MyVector<T>::size() const  
{ 
	return v_size; }

//returns the capacity of the vector
template <class T>
int MyVector<T>::capacity() const
{ return v_capacity; }

//returns true if the vector is empty, false otherwise
template <class T>
bool MyVector<T>::empty() const
{ return size()==0;}


//method to resize the vector if the number of elements inserted into the vector increases beyond its capacity
template <class T>
void MyVector<T>::reserve(int new_cap)
{
	//if old capacity > new_cap, no need to increase the vector
	if (v_capacity > new_cap) return;

	//otherwise, create a  bigger array arr with capacity new_cap
	Contact* arr=  new Contact[new_cap];

	//...copy contents of the old array to new array
	for (int i=0; i<v_size; i++)
	{
		arr[i] = data[i];
	}

	if(data != NULL) delete [] data; //delete old array
	data = arr; //make arr a new array
	v_capacity = new_cap; //set new capacity

}

//Removes an element from index
template <class T>
void MyVector<T>::erase(int index) throw(outOfRange)
{
	//throws an out_of_range exception if index is out of the range
	if(index<0 || index>=v_size) throw outOfRange();

	//move elements, starting from the position [index+1] till the end of the vector, one units left
	for( int k=index+1; k<v_size;k++)
	{
		data[k-1] = data[k];
	}
	//decrease vector size
	v_size--;
}


//a method that adds an element at the end of the vector
template <class T>
void MyVector<T>::push_back(T c)
{
	//if the vector is already full call reserve() function double its capacity if size is equal to or more than capacity
	if(v_size >= v_capacity)
	{
		reserve(max(1, 2*v_capacity));//double the capacity, or if the size is 0 - make capacity 1
	}

	data[v_size] = c; //add element at the end of the vector
	v_size++; //increase vector size accorsingly

}

template <class T>
void MyVector<T>::displayForSearch() //display method used with the key searchFor
{
	for(int i=0; i<v_size; i++)
	{
		cout<<i+1<<": "; //i+1 corresponds to the position of those person in the vector
		(data+i)->displayDetails(); //call specific dispayDetails method from our contact class which is tailored to this specific key
		cout<<endl;
	}
}

template <class T> //method whhich will return the object at a particular index in our vector
T& MyVector<T>::getElem(int i)
{
	return data[i];
}

template <class T>
void MyVector<T>::displayShort() //display method used with the keys markfv, unmarkfv, edit, del
{
	for(int i=0; i<v_size; i++)//for every object inside our vector
	{
		cout<<i+1<<". "; //i+1 corresponds to the position of that person in the vector
		(data+i)->displayDetailsShort(); //call specific displayDetailsShort method from our contact class which is tailored to this specific key
	}
}

template <class T>
void MyVector<T>::displayForPrintASC() //display method used with the keys printASC, printDES
{
	for(int i=0; i<v_size; i++)
	{
		(data+i)->displayDetailsPrint();// specific displayDetailsPrint method from our contact class which is tailored to these specific keys
	}
}


template <class T>
void MyVector<T>::displayForPrintFav() //display method used with the keys printFav
{
	for(int i=0; i<v_size; i++)
	{
		if((data+i)->getIsFav() == true)
		{
			(data+i)->displayDetailsPrint();// specific displayDetailsPrint method from our contact class which is tailored to these specific keys
		}
	}
}

template <class T>
string MyVector<T>::displayForDump(int i) //display method used with the key exportCSV, which finds the contact in our vector by the index given as an argument
{
	string s = "";//create an empty string

	string isFav;

	if((data+i)->getIsFav() == true) isFav = "1";// we need to get string value of boolean isfav that we get from our contact class
	else isFav = "0";

	//get the contact located at a specific position i in our vector and concatenate contact's details into one string by calling getter methods from contact class
	s += (data+i)->getFname()+" "+(data+i)->getLname()+", "+(data+i)->getEmail()+", "+(data+i)->getPrimaryPhone()+", "+(data+i)->getCity()+", "+(data+i)->getCountry()+", "+isFav;
	
	return s;//return the string
}

template <class T>
void MyVector<T>::dumpForExport() //display method used with the keys printASC, printDES
{

	for(int i=0; i<v_size; i++)
	{
		cout<<(data+i)->getFname()<<" "<<(data+i)->getLname()<<", "
			<<(data+i)->getEmail()<<", "<<(data+i)->getPrimaryPhone()<<", "
			<<(data+i)->getCity()<<", "<<(data+i)->getCountry()<<", "
			<<(data+i)->getIsFav()<<endl;

	}
	
}

template <class T>
void MyVector<T>::updateDetails(int record, int field)//updateDetails method used when user wants to edit the particular details of the contact obj through the key edit
{
	string newValue;

	if(field == 3)//edit email
	{
		cout<<"Please enter the new email: ";
		getline(cin,newValue); //get the new value from the user
		(data+record-1)->setEmail(newValue); //update the current contact's email to a  a new value
	}

	else if(field == 4)//edit phone#
	{
		cout<<"Please enter the new phone#: ";
		getline(cin,newValue);
		(data+record-1)->setPrimaryPhone(newValue);//update the current contact's phone to a  a new value
	}

	else if(field == 5)//edit city
	{
		cout<<"Please enter the new city: ";
		getline(cin,newValue);
		(data+record-1)->setCity(newValue);//update the current contact's city to a  a new value
	}

	else if(field == 6)//edit country
	{
		cout<<"Please enter the new country: ";
		getline(cin,newValue);
		(data+record-1)->setCountry(newValue); //update the current contact's country to a  a new value
	}

	// cout<<"Updated records: "<<endl;
	// (data+record-1)->displayDetailsShort();

	cin.clear();//clear cin cache
	cin.sync();
	
}

template <class T>
void MyVector<T>::changeIsFav(int record, bool b) //method used when user wants to change the isFav value of the contact obj through the keys markfv and unmarkfv
{
	if(b == true) //if the boolean value which was provided as an argument is true isFav will be set to true
		(data+record-1)->setIsFav(true);
	else //otherwise, isFav will be set to false
		(data+record-1)->setIsFav(false);

}

template class MyVector<Contact>;
