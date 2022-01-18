// --------------------------- rentalstore.cpp --------------------------------
// The RentalStore class reads from multiple files containing information on
// movies, customers and a commands file. The class stores information from 
// the movies and customers, and performs commands based off the command file
// such as borrow, return, showing inventory and history.
// ----------------------------------------------------------------------------
#include "rentalstore.h"
//g++ main.cpp rentalstore.cpp movie.cpp customer.cpp drama.cpp classic.cpp comedy.cpp
//------------------- constructors/destructor  -------------------------------
//default constructor
RentalStore::RentalStore(){
  //set all customer to nullptr
  for (int i=0; i<MAX_CUSTOMER; i++)
  {
    hashCustomers[i] = nullptr;
  }
  //sets all drama to nullptr
  for (int i=0; i<MAX_DRAMA; i++)
  {
    hashDramas[i] = nullptr;
  }
  //Sets all classics to nullptr
	for (int i = 0; i < MAX_CLASSIC; i++) {
		hashClassics[i] = nullptr;
	}
  //Sets all comedies to nullptr
	for (int i = 0; i < MAX_COMEDY; i++) {
		hashComedy[i] = nullptr;
	}
} 

// ------------------------------- destructor ---------------------------------
RentalStore::~RentalStore(){
  //Customer destructor
  for (int i=0; i<MAX_CUSTOMER; i++)
  {
    deleteCustomer(hashCustomers[i]);
    hashCustomers[i] = nullptr;
  }
  //Drama destructor
  for(int i = 0; i < MAX_DRAMA; i++){
    Drama *current = hashDramas[i];
    while(current != NULL){
      Drama *del = current;
      current = current->getNextDrama();
      delete del;
    }
  }
  //Comedy desctructor
  for(int i = 0; i < MAX_COMEDY; i++){
    Comedy *current = hashComedy[i];
    while(current != NULL){
      Comedy *del = current;
      current = current->getNextComedy();
      delete del;
    }
  }
  //Classic destructor
  for(int i = 0; i < MAX_CLASSIC; i++){
    Classic *current = hashClassics[i];
    while(current != NULL){
      Classic *del = current;
      current = current->getNextClassic();
      delete del;
    }
  }
} 

//----------------- reading movie, customer, and command files ----------------

// ----------------------------- buildCustomer --------------------------------
// Description: reads from data4customers.txt and build hashCustomers[]
// ----------------------------------------------------------------------------
void RentalStore::buildCustomer(ifstream& infile){
  //allocate new customer class
  Customer *newCustomer = new Customer;
  
  //insert into hashCustomers[]
  if(newCustomer->setCustomer(infile))
  { 
    insertCustomer(newCustomer);
  }
  else
    delete newCustomer;
}

// ------------------------------- buildMovie ---------------------------------
// Description: reads the data from the data4movies.txt and inserts the movies
//              into the hashtable that coressponds to their genre.
// ----------------------------------------------------------------------------
void RentalStore::buildMovie(ifstream& infile){
  string genreString; 
  char genre;
  string stockString;
  int stock;
  string title;
  string director;
  string actor;
  string monthString;
  int month;
  string yearString;
  int year;
  string data;

  //gets the line as a string
  getline(infile, data); 

  //if line is empty, return
  if(data == ""){ 
    return;
  }

  vector<string> v;
  stringstream ss(data);

  //parses the strings by commas
  while (ss.good()) { 
      string substr;
      getline(ss, substr, ',');
      v.push_back(substr);
  }

  //stores the parsed strings under correct variables
  genreString = v[0]; 
  stockString = v[1];
  director = v[2];
  title = v[3];

  genre = genreString[0];
  stringstream tmp(stockString);
  tmp >> stock;

  //gets rid of the spaces in front of the strings
  director.replace(0,1,"");
  title.replace(0,1,"");

  // stores it in the hashtable according to genre
  if(genre == 'C'){ // Classic movies
    string classicData = v[4];
    vector<string> w;
    stringstream ss(classicData);
    while (ss.good()) { // parses actor's first and last name and month and year
      string substr;
      getline(ss, substr, ' ');
      w.push_back(substr);
    }
    actor = w[1] + " " + w[2];
    monthString = w[3];
    yearString = w[4];

    stringstream tmp(monthString); // stores month and year as ints
    tmp >> month;
    stringstream tp(yearString);
    tp >> year;
    insertClassics(stock, director, title, actor, month, year);
  }
  else if(genre == 'F'){ // Comedy movies
    yearString = v[4];
    stringstream tmp(yearString);
    tmp >> year;
    insertComedy(stock, director, title, year);
  }
  else if(genre == 'D'){ // Drama movies
    yearString = v[4];
    stringstream tmp(yearString);
    tmp >> year;
    insertDrama(stock, director, title, year);
  }
  else{
    cout <<"'"<< genre <<"' is an invalid movie type, could not insert." << endl;
  }
}

// -------------------------- readCommands ------------------------------------
// Description: reads from the data4commands.txt and performs the commands
// ----------------------------------------------------------------------------
void RentalStore::readCommands(ifstream& infile){
  char command='\0';
  infile>>command;
  if (command == '\0') //if read empty char, terminate
    return;
  int custID=0;
  char mediaType='\0', movieType='\0';
  string movieData;
  string line;
  switch (command){
    case 'B': // borrow movie
    case 'R': // return movie
      infile>>custID;
      infile >> mediaType;
      if (mediaType != 'D'){
        cout<<endl<<"'"<<mediaType<<"' is invalid media type, line discarded."<<endl;
        getline(infile, line);     // get rid of the line
        break;
      }
      infile >> movieType;
      if (movieType != 'F' && movieType != 'C' && movieType != 'D'){
        cout<<endl<<"'"<< movieType <<"' is invalid movie type, line discarded."<<endl;
        getline(infile, line);     // get rid of the line
        break;
      }
      getline(infile, movieData);
      movieData.replace(0,1,""); //get rid of space in front
      if (command == 'B')
      {
        borrow(custID, mediaType, movieType, movieData);
      }
      else {
        returns(custID, mediaType, movieType, movieData);
      }
      break;
    case 'H': // print transaction history of a customer
      infile>>custID;
      history(custID);
      getline(infile, line);     // get rid of the line
      break;
    case 'I': // print inventory
      inventory();
      break;
    default:
      cout<<endl<<"'"<< command <<"' is an invalid action code, line discarded."<<endl;
      getline(infile, line);     // get rid of the line
      break;  
  }
} 

// ---------------------- basic commands: B, R, I, H --------------------------

// -------------------------------- borrow ------------------------------------
// Description: subtracts 1 to stock for each movie borrowed, add to customer 
//              rentedMovie
// ----------------------------------------------------------------------------
bool RentalStore::borrow(int customerID, char mediaType, char movieType, string movieData){
  Movie* foundMovie = findMovie(mediaType, movieType, movieData);
  if(foundMovie == nullptr) {
    cout << endl <<movieType<<", "<< movieData <<endl;
    cout<<" -- movie not found, line discarded."<<endl;
    return false;
  }

  Customer* foundCustomer = findCustomer(customerID);
  if(foundCustomer == nullptr) 
      return false;  

  if(foundMovie->subtractStock())
  {
    foundCustomer->addRentedMovie(foundMovie);  
    return true;
  }
  else 
  {
    cout<<endl;
    foundMovie->print();
    cout<<endl<<" -- movie stock not sufficient, line discarded."<<endl;
    return false; 
  }
}

// -------------------------------- returns -----------------------------------
// Description: adds 1 to stock for each movie returned, mark customer 
//              rentedMovie returned
// ----------------------------------------------------------------------------
bool RentalStore::returns(int customerID, char mediaType, char movieType, string movieData){
  Movie* foundMovie = findMovie(mediaType, movieType, movieData);
  if(foundMovie == nullptr) {
    cout << endl <<movieType<<", "<< movieData <<endl;
    cout<<" -- movie not found, line discarded."<<endl;
    return false;
  }
  
  Customer* foundCustomer = findCustomer(customerID);
  if(foundCustomer == nullptr) 
    return false;  
  
  if(foundMovie->addStock()){
    foundCustomer->returnMovie(foundMovie);  
    return true;
  }
  else 
    return false;
} 

// ------------------------------ inventory -----------------------------------
// Description: outputs the inventory of all items(movies) in the store. It 
//              prints the comedy movies sorted by title and year, then the
//              dramas sorted by director and title, then the classics sorted
//              by release date and major actor. 
// ----------------------------------------------------------------------------
void RentalStore::inventory(){
  cout<<endl<<"Printing inventory of all items in store..."<<endl;
  cout<<"---Comedy Movies sorting by Title, then Year it released:"<<endl;
  cout<<setw(5)<<"Stock"<<setw(20)<<"Director"<<setw(35)<<"Title"<<setw(8)<<"Year"<<endl;
  for(int i = 0; i< MAX_COMEDY; i++){
    Comedy *curr = hashComedy[i];
    while (curr != nullptr){
      curr->printWithStock();
      cout<<endl;
      curr = curr->getNextComedy();
    }
  }
  cout<<"---Dramas sorting by Director, then Title:"<<endl;
  cout<<setw(5)<<"Stock"<<setw(20)<<"Director"<<setw(35)<<"Title"<<setw(8)<<"Year"<<endl;
  for(int i = 0; i< MAX_DRAMA; i++){
    Drama *curr = hashDramas[i];
    while (curr != nullptr){
      curr->printWithStock();
      cout<<endl;
      curr = curr->getNextDrama();
    }
  }
  cout<<"---Classics sorting by Release date, then Major actor:"<<endl;
  cout << setw(5) << "Stock" << setw(20) << "Director" << setw(35) << "Title" << setw(20) << "Major Actor" << setw(15) << "Release Date" << endl;
  for(int i = 0; i< MAX_CLASSIC; i++){
    Classic *curr = hashClassics[i];
    while (curr != nullptr){
      curr->printWithStock();
      cout<<endl;
      curr = curr->getNextClassic();
    }
  }
}

// -------------------------------- history -----------------------------------
// Description: outputs all the movie transactions of a customer  
// ----------------------------------------------------------------------------
void RentalStore::history(int customerID){
  Customer* currentCustomer = findCustomer(customerID);
  if(currentCustomer == nullptr) 
    return;
  currentCustomer->printRentals();
}   

// ------------------------ private helper methods ----------------------------

// ----------------------------- findCustomer ---------------------------------
// Description: return the customer ptr stored in the hashtable 
// ----------------------------------------------------------------------------
Customer* RentalStore::findCustomer(int customerID){
  int lastDigit = customerID % 10;;
  Customer *current;
  current = hashCustomers[lastDigit];
  while(current != nullptr){
    if(current->getID() == customerID){
      return current;
    }
    else if (current->getID() < customerID) {
      current = current->getNextCustomer();
    }
    else
      break;
  }
  cout<<endl<<"'"<< customerID <<"' is an invalid customer ID, line discarded."<<endl;
  return nullptr;
}

// ------------------------------ insertCustomer ------------------------------
// Description: hash and insert customer into hashCustomers[]  
// ---------------------------------------------------------------------------- 
bool RentalStore::insertCustomer(Customer *newCustomer)
{ //insert into hashCustomers[]
  int lastDigit = newCustomer->getID() % 10;
  if(hashCustomers[lastDigit] == nullptr)
  { //no collision, insert in place
    hashCustomers[lastDigit] = newCustomer;  
  }
  else
  {  //when collision occurs, insert location per sorted customerID
    Customer *current = hashCustomers[lastDigit];
    if (*newCustomer < current)
    { //insert at front of list
      newCustomer->setNextCostomer(current);
      hashCustomers[lastDigit] = newCustomer;
    }
    else
    { //traverse till location is found
      Customer *next = current->getNextCustomer();
      while(next != nullptr)
      {
        if(*newCustomer < next)
        { //insert before next
          newCustomer->setNextCostomer(next);  
          break;
        }
        current = current->getNextCustomer();
        next = current->getNextCustomer();
      }
      current->setNextCostomer(newCustomer);
    }
  }
  return true;
}

// ------------------------------ deleteCustomer ------------------------------
// Description: recursively deletes customer in a linked list and its 
//               rentedMovie struct
// ----------------------------------------------------------------------------
bool RentalStore::deleteCustomer(Customer *cust)
{
  if (cust != nullptr){
    deleteCustomer(cust->getNextCustomer());
    delete cust;
    cust = nullptr;
    //delete struct rentedMovie is done in customer.cpp
  }
  return true;
}

// ------------------------------ insertDrama ---------------------------------
// Description: inserts the Drama movie into the hashDramas hastable. It uses
//              a key of the first letter of the Director's name. The rest of
//              the data is sorted alphabetically inside the linked list.
// ----------------------------------------------------------------------------
bool RentalStore::insertDrama(int stock, string director, string title,  int year){
    Drama *y = new Drama(stock, director, title, year); // new insertion
    
    char c = director[0]; // parses the first letter of director's first name
    int index = int(c); // gets index for letter 

    //(CASE 1)IF LIST IS EMPTY
    if(hashDramas[index] == NULL){
      hashDramas[index] = y; 
      return true;
    }
    //(CASE 2)IF LIST HAS ONE NODE
    else if(hashDramas[index]->getNextDrama() == NULL){
      Drama* current = hashDramas[index];
      //if y is less than head, replace y as head
      if(*y < *current){
        hashDramas[index] = y;
        y->setNextDrama(current);
        return true;
      }
      else{
        //if equal then add stock and deallocate
        if(*y == *current){
          current->setStock(current->getStock() + stock);
          delete y;
          return true;
        }
        // places y at the end of linked list
        current->setNextDrama(y);
        return true;
      }
    }
    //IF (CASE 3)LIST HAS MORE THAN ONE NODE
    else{
      Drama* current = hashDramas[index];
      //if y is less than head, replace y as head
      if(*y < *current){
        hashDramas[index] = y;
        y->setNextDrama(current);
        return true;
      }
      else{
        while(current != NULL){
          if(current->getNextDrama() != NULL){
            if(*y < *current->getNextDrama()){
                //if equal then add stock and deallocate
                if(*y == *current){
                  current->setStock(current->getStock() + stock);
                  delete y;
                  return true;
                }
                //if y is less than current next drama, set y as current's nextDrama
                y->setNextDrama(current->getNextDrama());
                current->setNextDrama(y);
                return true;
            }
          }
          else{
            // places y at the end of linked list
            current->setNextDrama(y);
            return true;
          }
          current = current->getNextDrama();
        }
      }
    }
  cout << "Error: problem with insertDrama function";
  return false;
}

// ------------------------------ insertComedy ---------------------------------
// Description: inserts the comedy movie into the hashComedy hashtable. It uses
//              a key of the first letter of the Title's name. The rest of
//              the data is sorted alphabetically inside the linked list.
// ----------------------------------------------------------------------------
bool RentalStore::insertComedy(int stock, string director, string title, int year) {
	//Dynamic allocate comedy movie input
	Comedy*comedyPtr = new Comedy(stock, director, title, year);
	int hashIndex = title[0];
	//(CASE 1)IF LIST IS EMPTY
	if (hashComedy[hashIndex] == nullptr) {
		hashComedy[hashIndex] = comedyPtr;
		return true;
	} 

	//(CASE 2)IF LIST HAS ONE NODE
	else if (hashComedy[hashIndex] != nullptr &&
		hashComedy[hashIndex]->getNextComedy() == nullptr) {
		//if equal then add and deallocate
		if (*hashComedy[hashIndex] == *comedyPtr) {
			hashComedy[hashIndex]->setStock(hashComedy[hashIndex]->getStock()+stock);
			delete comedyPtr;
			return true;
		}
		//if greater than, put behind
		else if (*comedyPtr > *hashComedy[hashIndex]) {
			hashComedy[hashIndex]->setNextComedy(comedyPtr);
			return true;
		}
		//if less than, put before
		else if (*comedyPtr < *hashComedy[hashIndex]) {
			comedyPtr->setNextComedy(hashComedy[hashIndex]);
			hashComedy[hashIndex]->setNextComedy(nullptr);
			hashComedy[hashIndex] = comedyPtr;
			return true;
		}
	}
	//IF (CASE 3)LIST HAS MORE THAN ONE NODE
	else {
		//If first node equal then addStock, deallocate
		if (*hashComedy[hashIndex] == *comedyPtr) {
			hashComedy[hashIndex]->setStock(hashComedy[hashIndex]->getStock() + stock);
			delete comedyPtr;
			return true;
		}
		//if first node not equal,loop through
		else {
			//Create temp pointer for traversal
			Comedy* tmpPtr = hashComedy[hashIndex];
			//While not end of list
			while (tmpPtr->getNextComedy() != nullptr) {
				//If found, then addStock, deallocate
				if (*tmpPtr == *comedyPtr) {
					tmpPtr->setStock(tmpPtr->getStock()+stock);
					delete comedyPtr;
					return true;
				}
        //if greater than, put behind
				else if (*comedyPtr > *tmpPtr && 
					*comedyPtr < *tmpPtr->getNextComedy()) {
					comedyPtr->setNextComedy(tmpPtr->getNextComedy());
					tmpPtr->setNextComedy(comedyPtr);
					return true;
				}
        //if less than, put behind
				else {
					tmpPtr = tmpPtr->getNextComedy();
					continue;
				}
			}
			//Check if equal at the end of list
			if (*tmpPtr == *comedyPtr) {
				tmpPtr->setStock(tmpPtr->getStock() + stock);
				delete comedyPtr;
				return true;
			}
			//else add to end of list and return
			tmpPtr->setNextComedy(comedyPtr);
			return true;
		}
	}
	cout << "Error: problem with insertComedy function";
	return false;
}

// ------------------------------ insertClassics ---------------------------------
// Description: inserts the classic movie into the hashClassics hashtable. It uses
//              a key of the release year for the hashtable. The rest of
//              the data is sorted by months inside the linked list.
//              Classics are sorted in the following manner:
//              (1) release year
//              (2) release month
//              (3) Major Actor ->concatenation of (firstName+lastName)
//	            A direct string compare is done. If a movie has a longer actor string
//	            then it will be GREATER than a shorter actor string (e.g. "a" < "ab")
//              (4) Major Actor(s) -> concatenation of all actor's first/last names
//              (5) Title will be used as a tie break
// ----------------------------------------------------------------------------
bool RentalStore::insertClassics(int stock, string director, 
								string title, string actor, int month, int year) {
	
	//Dynamic allocate comedy movie input
	Classic* classicPtr = new Classic(stock, director, title,actor, month, year);
	int hashIndex = year - 1900;
	//(CASE 1)IF LIST IS EMPTY
	if (hashClassics[hashIndex] == nullptr) {
		hashClassics[hashIndex] = classicPtr;
		return true;
	}

	//(CASE 2)IF LIST HAS ONE NODE
	else if (hashClassics[hashIndex] != nullptr &&
		hashClassics[hashIndex]->getNextClassic() == nullptr) {
		//if equal then add and deallocate
		if (*hashClassics[hashIndex] == *classicPtr) {
			hashClassics[hashIndex]->setStock(hashClassics[hashIndex]->getStock()+stock);
			hashClassics[hashIndex]->insertMajorActor(actor);
			delete classicPtr;
			return true;
		}
		//if greater than, put behind
		else if (*classicPtr > * hashClassics[hashIndex]) {
			hashClassics[hashIndex]->setNextClassic(classicPtr);
			return true;
		}
		//if less than, put before
		else if (*classicPtr < *hashClassics[hashIndex]) {
			classicPtr->setNextClassic(hashClassics[hashIndex]);
			hashClassics[hashIndex]->setNextClassic(nullptr);
			hashClassics[hashIndex] = classicPtr;
			return true;
		}
	}
	//IF (CASE 3)LIST HAS MORE THAN ONE NODE
	else {
		//If first node equal then addStock, deallocate
		if (*hashClassics[hashIndex] == *classicPtr) {
			hashClassics[hashIndex]->setStock(hashClassics[hashIndex]->getStock() + stock);
			hashClassics[hashIndex]->insertMajorActor(actor);
			delete classicPtr;
			return true;
		}
		//if first node not equal,loop through
		else {
			//Create temp pointer for traversal
			Classic* tmpPtr = hashClassics[hashIndex];
			//While not end of list
			while (tmpPtr->getNextClassic() != nullptr) {
				//If found, then addStock, deallocate
				if (*tmpPtr == *classicPtr) {
					tmpPtr->setStock(tmpPtr->getStock()+stock);
					hashClassics[hashIndex]->insertMajorActor(actor);
					delete classicPtr;
					return true;
				}
				//If greater than tmpPtr but less than nextClassic
				//Insert inbetween
				else if (*classicPtr > * tmpPtr &&
					*classicPtr < *tmpPtr->getNextClassic()) {
					classicPtr->setNextClassic(tmpPtr->getNextClassic());
					tmpPtr->setNextClassic(classicPtr);
					return true;
				}
				else {
					tmpPtr = tmpPtr->getNextClassic();
					continue;
				}
			}
			if (*tmpPtr == *classicPtr) {
				tmpPtr->setStock(tmpPtr->getStock() + stock);
				hashClassics[hashIndex]->insertMajorActor(actor);
				delete classicPtr;
				return true;
			}
			tmpPtr->setNextClassic(classicPtr);
			return true;
		}
	}
	cout << "Error: problem with insertClassic function";
	return false;
}

// ------------------------------- findDrama ----------------------------------
// Description: Finds the Drama pointer using the movie data provided. It takes
//              the string that contains the director's name and movie title 
//              and parses it into two strings. Then it returns the pointer to
//              the movie if it is found in the hashDramas hashtable. 
// ----------------------------------------------------------------------------
Drama* RentalStore::findDrama(string movieData){
  vector<string> v;
  stringstream ss(movieData);
 
  while (ss.good()) { // parses movie data by commas into strings
      string substr;
      getline(ss, substr, ',');
      v.push_back(substr);
  }
  
  string directorName = v[0]; // stores strings in correct variable
  string titleName = v[1];
  titleName.replace(0,1,""); // gets rid of space in the beginning 

  char c = directorName[0]; 
  int index = int(c); 
  Drama *current = hashDramas[index];
  Drama *found = NULL;
  while(current != NULL){
    if(current->getDirector() == directorName && current->getTitle() == titleName){
      found = current;
      break;
    }
    current = current->getNextDrama();
  }
  return found; // returns pointer if found, returns null if not. 
}

// ------------------------------- findMovie ----------------------------------
// Description: Finds the movie pointer using the movie data provided. It calls
//              the individual find method of findComedy, findClassic or 
//              findDrama depending on the movieType. Then it returns the
//              pointer to the movie if it is found in the hashtables. 
// ----------------------------------------------------------------------------
Movie* RentalStore::findMovie(char mediaType, char movieType, string movieData){
  Movie *m;
  if(movieType == 'D'){ // if movieType is Drama
    m = findDrama(movieData);
  }
  else if(movieType == 'C'){ // if movieType is Classic
    m = findClassic(movieData);
  }
  else if(movieType == 'F'){ // if movieType is Comedy
    m = findComedy(movieData);
  }
  else{ // if movieType is neither Drama, Classic or Comedy.
    m = nullptr;
  }
  return m;
}

// ------------------------------ findComedy ---------------------------------
// Description: Finds the Comedy pointer using the movie data provided. It 
//              takes the string that contains the title and the year
//              and parses it into two strings. Then it returns the 
//              pointer to the movie if it is found in the hashComedy hashtable. 
// ----------------------------------------------------------------------------
Comedy* RentalStore::findComedy(string movieData) {
	//Get title and year
	istringstream str(movieData);
	string title, year;
	getline(str, title, ',');
	getline(str, year);
	year = year.substr(1, year.length());

	//Get hash index
	int hashIndex = (int)title[0];
	Comedy* currCom = hashComedy[hashIndex];

	//If empty, return nullptr
	if (currCom == nullptr) {
		return nullptr;
	}
  //Else, search for matching comedy
	else {
		while (currCom != nullptr) {
			if (currCom->getTitle() == title &&
				currCom->getYear() == stoi(year)) {
				return currCom;
			}
			currCom = currCom->getNextComedy();
		}
    //If not found, return null
		return nullptr;
	}
}

// ------------------------------ findClassic ---------------------------------
// Description: Finds the Classic pointer using the movie data provided. It 
//              takes the string that contains the release date and major actor
//              and parses it into one string and two ints. Then it returns the 
//              pointer to the movie if it is found in the hashClassics hashtable.
// **ASSUMPTION** -> Classics are defined as a match if year, month, and major
//                   all match. A classic can have more than one major actor
// ----------------------------------------------------------------------------
Classic* RentalStore::findClassic(string movieData) {
	//Get release month/year and actor
	istringstream str(movieData);
	string actor, tempStr;
	int relMon, relYear;
	//Tokenize year, month, and major actor
  vector<string> v;
	while (str >> tempStr) {
		v.push_back(tempStr);
	}
	relMon = stoi(v[0]);
	relYear = stoi(v[1]);
	actor = v[2] + ' ' + v[3];

	//get hashIndex
	int hashIndex = relYear - 1900;
	Classic* currCla = hashClassics[hashIndex];

	//If empty, return nullptr
	if (currCla == nullptr) {
		return nullptr;
	}
  //Else search for matching classic
	else {
		while (currCla != nullptr) {
			if (currCla->getYear() == relYear &&
				currCla->getReleaseMonth() == relMon) {
				if (currCla->getMajorActor(actor)) {
					return currCla;
				}
			}
			currCla = currCla->getNextClassic();
		}
    //If not found, return null
		return nullptr;
	}
}