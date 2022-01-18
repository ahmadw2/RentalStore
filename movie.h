// -------------------------------- movie.h -----------------------------------
// This class stores movie information from the data4movies.txt file. It stores
// the movie's title, director, stock and release date.
// ----------------------------------------------------------------------------
#ifndef MOVIE
#define MOVIE
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Movie{
  // friend ostream & operator<<(ostream &, const Movie &); // prints movie info

public:
  Movie(); // constructor
  virtual ~Movie(); // destructor
  Movie(Movie &); // copy constructor

  string getTitle(); // returns the name of the movie
  string getDirector(); // returns the director of the movie
  int getStock(); // returns the stock of the movie
  int getYear(); // returns the year the movie was released

  void setYear(int newYear); // sets the year of the movie
  void setDirector(string newDirector); // sets the director
  void setTitle(string newTitle); // sets the title
  void setStock(int newStock); // sets the stock of the movie

  bool subtractStock(); //Subtracts -1 from movie stock
  bool addStock(); //Adds +1 to movie stock

  virtual void print(); // prints movie info
  void printWithStock(); //prints movie info with stock

private:
  string title; // stores title of the movie
  string director; // stores director's name
  int stock; // stores the stock
  int year; // stores the year the movie was released
};
#endif
