#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<iterator>
#include "entry.h"
#include "table.h"

using namespace std; 

void mergeSort(Entry a[], int size){
	int leftArraySize;
	int rightArraySize;

	if(size>1){
		leftArraySize = size/2;
		rightArraySize = size - leftArraySize; 
		
		mergeSort(a, leftArraySize);

		mergeSort((a+leftArraySize), rightArraySize);
		
		merge(a, leftArraySize, rightArraySize); 
	}
}

void merge(Entry a[], int leftArraySize, int rightArraySize){
	Entry* tempArray;
	int copied = 0;
	int leftCopied = 0;
	int rightCopied = 0;

	tempArray = new Entry[leftArraySize + rightArraySize]; 
	
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

	for(int i=0; i<leftArraySize + rightArraySize; i++){
		a[i] = tempArray[i];
	}

	delete[] tempArray; 
}

int Table::hashFunction(int key, int entries) const{ //not sure why do I need to put const at the end; 
	return key % entries;
}




 	
Table::Table(unsigned int max_entries){ //do not redefine default parameter in cpp file. 
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
	int index = hashFunction(e.get_key(), BUCKET);
	table[index].push_back(e); 		
}

std::string Table::get(unsigned int key) const{
	int index = hashFunction(key, BUCKET); 
	list<Entry>:: iterator i;  
	for(i = table[index].begin(); i != table[index].end(); i++){
//		cout<<"entered"<<endl;
//		cout<<"i->key is: "<< i->get_key()<<endl;  
		if(i->get_key() == key){
			return i->get_data(); 			
		}
	}
	return ""; 
}

bool Table::remove(unsigned int key){
	int index = hashFunction(key, BUCKET);
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
	int size = t.BUCKET; 
	int count = 0; 
	//Entry a[] = new Entry[size];
	Entry* a = new Entry[size]; 
 	//repeat for loop
	for(int i = 0; i < size; i++){
		for(list<Entry>::iterator j = t.table[i].begin(); j != t.table[i].end(); j++){
			a[count] = *j; 
			count++; 
		}
	}
	mergeSort(a, count); //merge sort is not called on Table object;  
	for(int k = 0; k < count; k++){
		out << toString(a[k]); 
	}

	delete[] a; 

	return out; 
}






