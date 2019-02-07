#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<iterator>
#include "entry.h"
#include "table.h"

using namespace std; 

Table::Table(unsigned int max_entries = 100){
	this->BUCKET = 100;
	table = new list<Entry>[BUCKET];//used table as a pointer to the array of list;  
}

Table::Table(unsigned int entries, std::istream& input){
	this->BUCKET = entries; 
	table = new list<Entry>[entries];
	for(int i = 0; i < entries; i++){
		Entry e;
		input >> e;
		put(e); 
	}
}

void Table::put(unsigned int key, std::string data){
	Entry e;
	e.set_key(key);
	e.set_data(data);
	put(e);  
}

void Table::put(Entry e){
	int index = hashFunction(e.get_key());
	table[index].push_back(e); 		
}

std::string Table::get(unsigned int key) const{
	int index = hashFunction(key); 
	list<Entry>:: iterator i;  
	for(i = table[index].begin(); i != table[index].end(); i++){
		if(i->get_key() == key){
			return i->get_data(); 			
		}
	}
}

bool Table::remove(unsigned int key){
	int index = hashFunction(key);
	list<Entry>:: iterator i;
	for(i = table[index].begin(); i != table[index].end(); i++){
		if(i->get_key() == key) break;
	}
	if(i != table[index].end()){
		table[index].erase(i); 
		return true; 
	}else{
		return false; 
	}
}

std::ostream& operator<<(std::ostream& out, const Table& t){
	//place all Entry objects in the Hash table into a vector; 
	int count; 

	//second approach: array
	Entry[] a = new Entry[count];
 	//repeat for loop
	for(int i = 0; i < BUCKET; i++({
		for(list<Entry>::iterator j = t[i].begin(); j != t[i].end(); j++){
			a[count] = *j; 
			count++; 
		}
	}
	//MergeSort(e, count); 
	for(int k = 0; k < count; k++){
		out << a[k].toString(); 
	}
	return out; 
}

string Table::toString(Entry e){
	return std::str(e.get_key()) + " " + std::str(e.get_data()); 
}

void Table::MergeSort(Entry a[], size_t size){
	size_t leftArraySize();
	size_t rightArraySize();

	if(size>1){
		leftArraySize = size/2;
		rightArraySize = size - leftArraySize; 
		mergesort((a+leftArraySize), rightArraySize);
		
		merge(a, leftArraySize, rightArraySize); 
	}
}

void Table::merge(Entry a[], size_t leftArraySize, size_t rightArraySize){
	int* tempArray;
	size_t copied = 0;
	size_t leftCopied = 0;
	size_t rightCopied = 0;

	tempArray = new int[leftArraySize + rightArraySize]; 
	
	while((leftCopied<leftArraySize) && (rightCopied < rightArraySize)){
		if(a[leftCopied].get_key() < (a + rightArraySize)[rightCopied].get_key()){
			tempArray[copied++] = a[leftCopied++]; 
		}else{
			tempArray[copied++] = (a + leftArraySize)[rightCopied++]; 
		}
	}
	
	while(leftCopied <leftArraySize){
		tempArray[copied++] = a[leftCopied++]; 
	}

	while(rightCopied < rightArraySize){
		tempArray[copied++] = (a + leftArraySize)[rightCopied++];
	}

	for(size_t i=0; i<leftArraySize + rightArraySize; i++){
		a[i] = tempArray[i];
	}

	delete[] tempArray; 
}

int Table::hashFunction(int key){
	return key % 100; 	
}





