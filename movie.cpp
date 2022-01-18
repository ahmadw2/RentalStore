// ------------------------------ movie.cpp -----------------------------------
// This class stores movie information from the data4movies.txt file. It stores
// the movie's title, director, stock and release date.
// ----------------------------------------------------------------------------
#include "movie.h"
// ---------------------------- constructor -----------------------------------
  Movie::Movie(){
   title = ""; // stores title of the movie
   director = ""; // stores director's name
   stock = 0; // stores the stock
   year = 0; // stores the year the movie was released
  }

// ------------------------------ destructor ----------------------------------
  Movie::~Movie(){

  } 

// ---------------------------- copy constructor ------------------------------
  Movie::Movie(Movie& m){
  title = m.getTitle();
  director = m.getDirector();
  stock = m.getStock();
  year = m.getYear();
  }

// -------------------------------- getTitle ----------------------------------
// Description: returns the name of the movie
// ----------------------------------------------------------------------------
  string Movie::getTitle(){
    return title;
  }

// ------------------------------- getDirector --------------------------------
// Description: returns the director of the movie
// ----------------------------------------------------------------------------
  string Movie::getDirector(){
    return director;
  }

// ------------------------------- getStock -----------------------------------
// Description: returns the stock of the movie
// ----------------------------------------------------------------------------
  int Movie::getStock(){
    return stock;
  }

// ------------------------------- getYear ------------------------------------
// Description: returns the year the movie was released
// ----------------------------------------------------------------------------
  int Movie::getYear(){
    return year;
  }

// ------------------------------ setTitle ------------------------------------
// Description: sets the title of the movie
// ----------------------------------------------------------------------------
  void Movie::setTitle(string newTitle){
    title = newTitle;
  }

// ------------------------------ setDirector ---------------------------------
// Description: sets the director of the movie
// ----------------------------------------------------------------------------
  void Movie::setDirector(string newDirector){
    director = newDirector;
  } 

// ------------------------------ setYear -------------------------------------
// Description: sets the year of the movie
// ----------------------------------------------------------------------------
  void Movie::setYear(int newYear){
    year = newYear;
  }
  
// ------------------------------ setStock ------------------------------------
// Description: sets the stock of the movie
// ----------------------------------------------------------------------------
  void Movie::setStock(int newStock){
    if(newStock >= 0){
      stock = newStock;
    }
  }

// ---------------------------- subtractStock ---------------------------------
// Description: subtracts 1 from movie stock
// ----------------------------------------------------------------------------
  bool Movie::subtractStock(){
    if(stock > 0){
      stock = stock - 1;
      return true;
    }
    else{
      return false;
    }
  }

// ------------------------------- addStock -----------------------------------
// Description: adds 1 to movie stock
// ----------------------------------------------------------------------------
  bool Movie::addStock(){
    stock = stock + 1;
    return true;
  }

// ------------------------------- print -------------------------------------
// Description: prints the movie info
// ---------------------------------------------------------------------------
  void Movie::print(){
    cout << getTitle() << ", " << getDirector() << ", " << getYear();
  }

// -------------------------- printWithStock ---------------------------------
// Description: prints the movie info with stock
// ---------------------------------------------------------------------------
  void Movie::printWithStock(){
    cout <<setw(5)<< getStock() <<setw(20) << getDirector() <<setw(35) 
    << getTitle()  << setw(8) << getYear();
  }
