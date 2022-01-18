// --------------------------- rentalstore.h ----------------------------------
// The RentalStore class reads from multiple files containing information on
// movies, customers and a commands file. The class stores information from 
// the movies and customers, and performs commands based off the command file
// such as borrow, return, showing inventory and history.
// ----------------------------------------------------------------------------
#ifndef RENTALSTORE
#define RENTALSTORE
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include "movie.h"
#include "comedy.h"
#include "classic.h"
#include "drama.h"
#include "customer.h"
using namespace std;

const int MAX_CLASSIC = 201; //Max number hashing for Classics (year-1900)
const int MAX_DRAMA = 127;   //Max number hashing for Drama (127 ASCII char)
const int MAX_COMEDY = 127;  //Max number hashing for Comedy (127 ASCII char)
const int MAX_CUSTOMER = 10; //Max number hashing for Customer (buckets of 10)

class RentalStore{
public:
  RentalStore(); // constructor
  ~RentalStore(); // destructor
  
  void readCommands(ifstream& infile); // reads from the data4commands.txt and perform commands
  void buildMovie(ifstream& infile); // reads from data4movies.txt
  void buildCustomer(ifstream& infile); // reads from data4customers.txt and build hashCustomers[]
  bool borrow(int customerID, char mediaType, char movieType, string movieData); //subtracts 1 to stock for each movie borrowed, add to customer rentedMovie
  bool returns(int customerID, char mediaType, char movieType, string movieData); //adds 1 to stock for each movie returned, mark customer rentedMovie returned
  void inventory(); // outputs the inventory of all items in the store
  void history(int customerID); // outputs all the transactions of a customer
 
private:
  int count; // keeps track of how many movies are stored
  Classic *hashClassics[MAX_CLASSIC]; // hastable storing classic movies
  Comedy *hashComedy[MAX_COMEDY]; // hastable storing comedy movies
  Drama *hashDramas[MAX_DRAMA]; // hastable storing dramas movies
  Customer *hashCustomers[MAX_CUSTOMER]; // array stores the customers information
  Movie* findMovie(char mediaType, char movieType, string movieData); // returns pointer to Movie matching movieData

  Drama* findDrama(string movieData); // rets pointer to Drama matching movieData
  Comedy* findComedy(string movieData);// rets pointer to Comedy matching movieData
  Classic* findClassic(string movieData);// rets pointer to Classic matching movieData 

  Customer* findCustomer(int customerID); //return the customer ptr
  bool insertDrama(int stock, string director, string title,  int year); // hash and inse
  bool insertCustomer(Customer *cust); //hash and insert customer into hashCustomers[]
  bool insertComedy(int stock, string director, string title, int year);//hash and insert comedy into hashComedy[]
  bool insertClassics(int stock, string director, string title, string actor, int month, int year);//hash and insert Classic into hashClassics[]
  bool deleteCustomer(Customer *cust); //recursively deletes customer in a linked list and its rentedMovie struct
};

#endif
