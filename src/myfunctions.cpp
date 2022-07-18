#include<iostream>
#include<cstdlib>
#include<sstream>

#include "contact.h"
#include "myfunctions.h"

using namespace std;

//function which will generate a new object of type Contact and return it
Contact* generateNewContact()
{
	string fname, lname, email, primaryPhone, city, country;
	bool isFav;
	string key;
	string tempIsfav;

	//get from the user the corresponding parameter required for generating the contact
	cout<<"Please enter the details of the contact:"<<endl;
	cout<<"First Name: ";
	getline(cin,fname);

	cout<<"Last Name: ";
	getline(cin,lname);

	cout<<"Email: ";
	getline(cin,email);

	cout<<"Phone#: ";
	getline(cin,primaryPhone);

	cout<<"City: ";
	getline(cin,city);

	cout<<"Country: ";
	getline(cin,country);

	cout<<"Do you want to add the contact in your favourites (y/n) : ";
	getline(cin,tempIsfav);

	//since the input that we get from the user is string, we assign the input to a temp string varible, and based on its value, adjust our boolean isFav variable
	if(tempIsfav == "y") isFav = true;
	else if (tempIsfav == "n") isFav = false;

	cin.clear();//clear the cin cache
	cin.sync();

	Contact* c =  new Contact(fname, lname, email, primaryPhone, city, country, isFav);//create a new contact

	cout<<"Contact "<<fname<<" "<<lname<<" has successfully been added!"<<endl;//print the corresponding message

	return c;//return the generated contact
}

//function which will generate key based on the fname and lname values passed as an argument
string generateKey(string fname, string lname)
{
	string key;
	key = fname + " " + lname; //key is the concatenation  of fname, space, and lname

	return key;
}

//function which will remove spaces from the string passed as an argument and return the uppdated string
string removeSpaces(string str)
{
    stringstream ss(str); // store the string into string stream
    string temp;
 
    str = ""; //make the string empty
 
    //run the while loop till end of stream and get every word without unnecessary spaces
    while (getline(ss, temp, ' ')) {
        //and put them back into a string by concatenating 
        str = str + temp;
    }
    return str;//return the string without spaces
}