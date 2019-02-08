//
//  table.h
//  W19 - Lab04
//
#ifndef table_h
#define table_h
#include <iostream>
#include <list> 
#include "entry.h"
#include <string>


using namespace std; 

class Table{
	public:
	Table(unsigned int max_entries = 100);
	
	Table(unsigned int entries, std::istream& input);

		
	void put(unsigned int key, std::string data);
	void put(Entry e); 
	std::string get(unsigned int key) const; 
	bool remove(unsigned int key);
        int hashFunction(int x) const; 
  //      void mergeSort(Entry a[], int size);
//	void merge(Entry a[], int l, int  r);	
	
	
	friend std::ostream& operator<<(std::ostream& out, const Table& t); 

	list<Entry> *table; 
	int BUCKET; 
	
	
};

        void mergeSort(Entry a[], int size);
	void merge(Entry a[], int l, int  r);
	string toString(Entry e); 	
#endif /* table_h */
