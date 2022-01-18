// -------------------------------- drama.h -----------------------------------
// The class 'Drama' is a subclass of the class 'Movie'. It inherits
// all the properties of 'Movie'.
// ----------------------------------------------------------------------------
#ifndef DRAMA
#define DRAMA
#include "movie.h"

class Drama: public Movie{

  friend ostream & operator<<(ostream &, Drama &); // prints movie info
  
public:
  Drama(); // constructor
  Drama(int stock, string director, string title, int year); // param constructor
  ~Drama(); // destructor
  
  // operator overloads, compares director then title
  bool operator<(Drama &d);
  bool operator>(Drama &d);
  bool operator<=(Drama &d);
  bool operator>=(Drama &d);
  bool operator==(Drama &d);
  bool operator!=(Drama &d);

  void print(); // prints movie information

  Drama* getNextDrama(); //gets drama
  void setNextDrama(Drama* d); //sets drama

private:
  Drama* nextDrama; //pointer to next drama for linked list in hashtable
};
#endif