#ifndef CONTACT_H
#define CONTACT_H

#include<iostream>
#include<string>
using namespace std;


class Contact
{
	private:
		//each contact contains below details
		string fname;
		string lname;
		string email;
		string primaryPhone;
		string city;
		string country;
		bool isFav;

	public:
		Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav);	//constructor
		Contact();
		//getter methods
		string getFname(); 
		string getLname(); 
		string getEmail();
		string getPrimaryPhone();
		string getCity();
		string getCountry();
		bool getIsFav();

		//setter methods
		void setFname(string f);
		void setLname(string l);
		void setEmail(string e);
		void setPrimaryPhone(string p);
		void setCity(string c);
		void setCountry(string c);
		void setIsFav(bool b);

		//display methods tailored for different uses
		void displayDetails();
		void displayDetailsShort();
		void displayDetailsPrint();

		friend class ContactBST;
};

#endif