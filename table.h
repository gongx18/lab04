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
	string toString(Entry e);
		
	void put(unsigned int key, std::string data);
	void put(Entry e); 
	std::string get(unsigned int key) const; 
	bool remove(unsigned int key);
        int hashFunction(int x) const; 
        void mergeSort(Entry a[], size_t size);
	void merge(Entry a[], size_t l, size_t  r);	
	
	
	friend std::ostream& operator<<(std::ostream& out, const Table& t); 

	list<Entry> *table; 
	int BUCKET; 
	
	
};

#endif /* table_h */
