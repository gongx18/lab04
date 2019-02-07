//
//  table.h
//  W19 - Lab04
//
#ifndef table_h
#define table_h
#include <list> 
#include "entry.h"


class Table{
	public:
	Table(unsigned int max_entries = 100);
	
	Table(unsigned int entries, std::istream& input);
	
	void put(unsigned int key, std::string data);
	void put(Entry e); 
	std::string get(unsigned int key) const; 
	bool remove(unsigned int key);
        int hashFunction(int x); 
        void mergeSort(Entry a[], size_t size);
	void merge(Entry a[], int a, int b);	
	
	
	friend std::ostream& operator<<(std::ostream& out, const Table& t); 
	private:
	list<Entry> *table; 
	int BUCKET; 
	
	
};

#endif /* table_h */
