// BarcodeHashTableScanner.cpp

#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Item.h"
#include "LinkedList.h"
#include <list>

#define SIZE 10000

using namespace std;


class HashTable									// Declaration of the hash table class
{
public:
	void loadHashTable(string barcode, string description);
	string searchHashTable( string) ;

private:
	
	int hashFunction(const string barcode) const;	
	list<Item> table[SIZE];							// create a hash table of using linked list                                                                                        
};

void HashTable::loadHashTable(string barcode, string description)		// Function to load a key-value pair (barcode - description
{										// to a hash table
	int index = hashFunction(barcode);					// use hash function to identify an index from barcode
	
	Item item;
	item.barcode = barcode;
	item.description = description;
	table[index].push_front(item);						// load the item to the front of the table index
}

string HashTable::searchHashTable (string searchItem) {				// Function to search a given barcode in a hash table
	int index = hashFunction (searchItem);

	
	list<Item>::iterator itor;						// create an iterator
	for (itor = table[index].begin(); itor != table[index].end(); itor++) {	// to go through the list at the table index
		if (*itor == searchItem) 					// if the barcode matches the search item
			return itor -> description;				// return and print out the description
			cout << itor -> description << endl;
	}
	
	return "";								// the function returns an empty string if found nothing
	cout << "Barcode Not Found" << endl;					// print out the message
}


int HashTable::hashFunction(const string barcode) const				// hash function to find the index of the table
{
	int index = 0;

	for (int i = 0; i < barcode.length(); i++)				// loop through each character of the barcode (string)
	{
		index += 37 * barcode[i];					// to add up the index 

	index %= SIZE;								// use module to find the index 

	return index;								// return the index
	}
}


int main () {

	ifstream myFile ("upc_corpus.txt");					// read in a provided data file
	
	if (!myFile.is_open()) {						// check if the data file is opened 
		cout << "Text File failed to open" << endl;
	}

	int counter = 0; 							// create a counter of each line read
	string line;
	string barcode;
	string description;

	HashTable ht;

	while (getline (myFile, line) && counter < SIZE) { 		// read each line of the data file and stop if the counter reaches the size
		stringstream ss (line);					// create an object for each line
		getline (ss, barcode, ',');				// read an object and stop at the stopper (comman) to store it
		getline (ss, description);				// read the rest of the object and store it
		counter++;						// increment each line read

	myFile.close();							// close file


	ht.loadHashTable(barcode, description);				// after getting the barcode and description, load them into the table
	}

	string searchItem;
	cout << "--------------------------------------------" << endl;	
	cout << "Enter a Barcode to Search: " ;				// ask a barcode from a user to search

	cin >> searchItem;						// read it into a string search item

	clock_t t;							// start to time the search operation
	t = clock();

	ht.searchHashTable(searchItem);					// process the search
	
	t = clock() - t;						// calculate the time of the search oepration

	cout << "Hash Search time: " << t << " milisecond" << endl;	// print out the result of search operation
	cout << "---------------------------------------------" << endl;
	return 0;
}

