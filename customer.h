// ----------------------------- customer.h -----------------------------------
// The Customer Class stores customer information and performs basic functions 
// such as setting the Customer data fields and equality/inequality comparison.
// ----------------------------------------------------------------------------
#ifndef CUSTOMER
#define CUSTOMER
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "movie.h"
using namespace std;

class Customer{

  friend ostream & operator<<(ostream &, const Customer &);

  public:
    Customer();   //default constructor
    ~Customer();  //destructor
    Customer(int id, const string &first, const string &last);  //Customer fields are set equal to parameter 
	  Customer(const Customer &); //copy constructor

    Customer& operator=(const Customer &cust);//copy operator
    bool setCustomer(istream& line); //set Customer fields from data file, returns true if the data is set, false when bad data entered
    bool setNextCostomer(Customer *cust); //setter for nextCustomer ptr
    Customer* getNextCustomer(); //getter for nextCustomer ptr
    int getID() const; //getter for customer ID
    string getFirstname() const; //getter for customer firstname
    string getLastname() const;  //getter for custoemr lastname

    bool operator==(const Customer &cust) const;  //equality operator
	  bool operator!=(const Customer &cust) const;  //inequality operater
    bool operator>(const Customer *cust) const;  //operator >
    bool operator<(const Customer *cust) const;  //operator <
    
    void addRentedMovie(Movie* movieRent); //add movie to customer transaction history
    void returnMovie(Movie* movieRent); //mark movie as returned in customer transaction history
    void printRentals();  //prints all rental records of the customer

  private:
    //struct rentedMovie represents one rented movie. 
    //it links to a chain of rented Movies
    struct rentedMovie{
      Movie *thisMovie;  //This will point to the movie of this node
      rentedMovie *previousRentedMovie; //This will point to the previous rentedMovie in the chain
      bool isReturned;  //yes for returned, no for currently borrowed
    };

    int customerID;
    string firstname;
    string lastname;
    rentedMovie *custRentedMovie;
    Customer *nextCustomer;
    
    //private helper methods recursively clears the rentHistory
    void clearRentHistory(struct rentedMovie* currentMovie);
    //private helper methods recursively copys the rentHistory
    void copyRentHistory(struct rentedMovie* currentMovie);
};

#endif
