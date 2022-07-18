
#include "contact.h"
#include<iostream>


//constructor
Contact::Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav)
: fname(fname), lname(lname), email(email), primaryPhone(primaryPhone), city(city), country(country), isFav(isFav) {}

Contact::Contact(){}

//getter methods
string Contact::getFname() {return this->fname;}
string Contact::getLname() {return this->lname;}
string Contact::getEmail() {return this->email;}
string Contact::getPrimaryPhone() {return this->primaryPhone;}
string Contact::getCity() {return this->city;}
string Contact::getCountry() {return this->country;}
bool Contact::getIsFav() {return this->isFav;}

//setter methods
void Contact::setFname(string f) {this->fname = f;}
void Contact::setLname(string l) {this->lname = l;}
void Contact::setEmail(string e) {this->email = e;}
void Contact::setPrimaryPhone(string p) {this->primaryPhone = p;}
void Contact::setCity(string c) {this->city = c;}
void Contact::setCountry(string c) {this->country = c;}
void Contact::setIsFav(bool b) {
	this->isFav = b;
}

//display method associated with the keyword add
void Contact::displayDetails()
{
	cout<<this->fname<<" "<<this->lname<<endl;
	cout<<"Email: "<<this->email<<endl;
	cout<<"Phone#: "<<this->primaryPhone<<endl;
	cout<<"City: "<<this->city<<endl;
	cout<<"Country: "<<this->country<<endl;
}

//display method associated with other keywords where we need to print details of the requested/found contact to the user
void Contact::displayDetailsShort()
{
	cout<<this->fname<<" "<<this->lname<<", "
		<<this->email<<", "
		<<this->primaryPhone<<", "
		<<this->city<<", "
		<<this->country<<endl;
}

//display method associated with the keywords related to printing
void Contact::displayDetailsPrint()
{
	cout<<this->fname<<" "<<this->lname<<", "
		<<this->email<<", "
		<<this->primaryPhone<<", "
		<<this->city<<", "
		<<this->country<<", "
		<<this->isFav<<endl;
}