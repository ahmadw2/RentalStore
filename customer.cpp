// ----------------------------- customer.cpp -----------------------------------
// The Customer Class stores customer information and performs basic functions 
// such as setting the Customer data fields and equality/inequality comparison.
// ----------------------------------------------------------------------------
#include "customer.h"

//------------------- constructors/destructor  -------------------------------
//default constructor
Customer::Customer() { 
  customerID = -1;
  firstname = "";
  lastname = "";
  custRentedMovie = nullptr;
  nextCustomer = nullptr;
}  

//default destructor
Customer::~Customer() 
{ //clear rentHistory
  clearRentHistory(custRentedMovie);
  //clear nextCustomer ptr
  nextCustomer = nullptr;
} 

//constructor to set customer fields equal to parameter 
Customer::Customer(int id, const string &first, const string &last)
{
  customerID = id;
  firstname = first;
  lastname = last;
  custRentedMovie = nullptr;
  nextCustomer = nullptr;
}  

//copy constructor
Customer::Customer(const Customer &cust){
  if (this != &cust) {
    customerID = cust.customerID;
    firstname = cust.firstname;
    lastname = cust.lastname;
  }
  copyRentHistory(cust.custRentedMovie);
  nextCustomer = nullptr;
}  

//private helper function recursively clears the rentHistory
void Customer::clearRentHistory(struct rentedMovie* currentMovie){
  if (currentMovie != nullptr)
  {
    currentMovie->thisMovie = nullptr;
    currentMovie->isReturned = false;
    //recursively calls itself to clear
    clearRentHistory(currentMovie->previousRentedMovie);
    delete currentMovie;
    currentMovie = nullptr;
  }
}	  

//private helper function recursively copies the rentedMovie linked list
void Customer::copyRentHistory(struct rentedMovie* currentMovie)
{
  if (currentMovie != nullptr)
  {
    custRentedMovie->thisMovie = currentMovie->thisMovie;
    custRentedMovie->isReturned = currentMovie->isReturned;
    //recursively calls itself to copy
    copyRentHistory(currentMovie->previousRentedMovie);
  }
}	

//------------------- copy operator  -------------------------------
Customer& Customer::operator=(const Customer &cust){
  //copy operator
  if (this != &cust) {
    customerID = cust.customerID;
    firstname = cust.firstname;
    lastname = cust.lastname;
  }
  copyRentHistory(cust.custRentedMovie);
  nextCustomer = nullptr;
  return *this; 
}


//------------------- getter and setter  -------------------------------
bool Customer::setCustomer(istream& line){
  //set Customer fields from input file
	//returns true if the data is set, false when bad data
  int id;
  string idString, first, last;
  line >> idString;
  if (idString == "")
    return false;

  stringstream tmp(idString);
  tmp>>id;
  line >> first;
  line >> last;
  customerID = id;
  firstname = first;
  lastname = last;
  return true;
}

//setter for nextCustomer ptr
bool Customer::setNextCostomer(Customer *cust){
  nextCustomer = cust;
  return true;
} 

//getter for nextCustomer ptr
Customer* Customer::getNextCustomer(){
  return nextCustomer;
} 

//getter for customer ID
int Customer::getID() const{
  return customerID;
} 

//getter for customer firstname
string Customer::getFirstname() const{
  return firstname;
} 

//getter for custoemr lastname
string Customer::getLastname() const{
  return lastname;
} 
  	

//------------------- comparison operator  -------------------------------/
//equality operator by comparing customer ID, firstname and lastname
bool Customer::operator==(const Customer &cust) const{
  // if memory address is same, return true
  if (this != &cust){
    if (customerID != cust.customerID || firstname != cust.firstname || lastname != lastname) {
      return false;
    }
  }
  return true;
}  
    
//inequality operater
bool Customer::operator!=(const Customer &cust) const{
  return !(this == &cust);
}  
    
//operator > by comparing customer ID
bool Customer::operator>(const Customer *cust) const{
  return customerID > cust->customerID;
} 

//operator < by comparing customer ID
bool Customer::operator<(const Customer *cust) const{
  return customerID < cust->customerID;
} 

//------------------- rent or return methods  -------------------------------
//add movie to customer transaction history
void Customer::addRentedMovie(Movie* movieRent)
{ //allocate new rentedMovie
  rentedMovie *newMovie = new rentedMovie;
  newMovie->thisMovie = movieRent;
  newMovie->isReturned = false;
  //insert new rentedMovie at front of list
  newMovie->previousRentedMovie = custRentedMovie;
  custRentedMovie = newMovie;
}

//mark movie as returned in customer transaction history
void Customer::returnMovie(Movie* movieRent)
{
  rentedMovie *curr = custRentedMovie;
  while (curr != nullptr)
  { //comparing pointers
    if (curr->thisMovie == movieRent){ 
      if (curr->isReturned == false){
        curr->isReturned = true;
      }
      else
      {
        cout<<endl;
        movieRent->print();
        cout<<endl<<" -- has already been returned"<<endl;
      }
      return;
    }
    curr = curr->previousRentedMovie;
  }
  cout<<endl;
  movieRent->print();
  cout<<endl<<" -- was not found in customer history, please check again.";
}

//prints all rental records of the customer
void Customer::printRentals()
{  //prints all rental records
  cout<<endl<<"Printing all transactions of customer (latest to earliest): ";
  cout << *this;

  struct rentedMovie* curr = custRentedMovie;
  while (curr != NULL)
  {
      curr->thisMovie->print();
      if (curr->isReturned)
          cout << " -- returned" << endl;
      else
        cout << " -- borrowed" << endl;
      curr = curr->previousRentedMovie;
  }
}

//outputing the customer information
ostream& operator<<(ostream& out, const Customer& cust) {
    cout << cust.customerID << " " << cust.firstname << " " << cust.lastname << endl;
    return out;
}