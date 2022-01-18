// ------------------------------ comedy.cpp -----------------------------------
// The class 'Comedy' is a subclass of the class 'Movie'. It inherits
// all the properties of 'Movie'.
// ----------------------------------------------------------------------------
#include "comedy.h"

// --------------------------- Default constructor ----------------------------
Comedy::Comedy() {
	setYear(0);
	setDirector("");
	setTitle("");
	setStock(0);
	nextComedy = nullptr;
}
// --------------------------- constructor w/params ---------------------------
Comedy::Comedy(int stock, string director, string title, int year) {
	setYear(year);
	setDirector(director);
	setTitle(title);
	setStock(stock);
  nextComedy = nullptr;
}
// ------------------------------- destructor --------------------------------
Comedy::~Comedy() {
	//No dynamic allocations
}
// --------------------------- getNextComedy ---------------------------------
// Description: returns the pointer to the nextComedy object
// ---------------------------------------------------------------------------
Comedy* Comedy:: getNextComedy() {
	Comedy* comedyPtr = nextComedy;
	return comedyPtr;
}
// --------------------------- setNextComedy ---------------------------------
// Description: sets nextComedy equal to com
// ---------------------------------------------------------------------------
void Comedy::setNextComedy(Comedy* com) {
	nextComedy = com;
}

// ------------------------------- Operator Overloads -------------------------

// ------------------------------ operator< -----------------------------------
// Description: Return true if current object title comes before com
//              title. False otherwise.
// ----------------------------------------------------------------------------
bool Comedy::operator<(Comedy& com) {
	if (this->getTitle() < com.getTitle()) {
		return true;
	}
	else if (this->getTitle() == com.getTitle() &&
		this->getYear() < com.getYear()) {
		return true;
	}
	else {
		return false;
	}	
}
// ------------------------------ operator> -----------------------------------
// Description: Return true if current object title comes after com
//              title. False otherwise.
// ----------------------------------------------------------------------------
bool Comedy::operator>(Comedy& com) {
	if (this->getTitle() > com.getTitle()) {
		return true;
	}
	else if (this->getTitle() == com.getTitle() &&
		this->getTitle() > com.getTitle()) {
		return true;
	}
	else {
		return false;
	}
}
// ----------------------------- operator<= -----------------------------------
// Description: Return true if current object title comes before or 
//              equal to com title. False otherwise.
// ----------------------------------------------------------------------------
bool Comedy::operator<=(Comedy& com) {
	if (*this < com || *this == com) {
		return true;
	}
	else {
		return false;
	}
}
// ----------------------------- operator>= -----------------------------------
// Description: Return true if current object title comes after or 
//              equal to com title. False otherwise.
// ----------------------------------------------------------------------------
bool Comedy::operator>=(Comedy& com) {
	if (*this > com || *this == com) {
		return true;
	}
	else {
		return false;
	}
}
// ----------------------------- operator== -----------------------------------
// Description: Return true if current object title and year equals com, 
//              False otherwise.
// ----------------------------------------------------------------------------
bool Comedy::operator==(Comedy& com) {
	if (this->getTitle() == com.getTitle() &&
		this->getYear() == com.getYear()) {
		return true;
	}
	else { 
		return false; 
	}
}
bool Comedy::operator!=(Comedy& com) {
	return !(*this== com);
}

// ------------------------------ operator<< ----------------------------------
// Description: Outputs to ostream title, director, and year
// ----------------------------------------------------------------------------
ostream& operator<<(ostream& output, Comedy& d) {
	output << d.getTitle() << " " << d.getDirector() << " " << d.getYear()
		<< endl;
	return output;
}

// ------------------------------ print ---------------------------------------
// Description: prints movie data with genre
// ----------------------------------------------------------------------------
void Comedy::print(){
  cout << "F, " << getTitle() << ", " << getDirector() << ", " << getYear();
}