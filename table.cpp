#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<iterator>
#include "entry.h"
#include "table.h"

//using namespace std; 

//void mergeSort(Entry a[], int size){
//	int leftArraySize;
//	int rightArraySize;
//
//	if(size>1){
//		leftArraySize = size/2;
//		rightArraySize = size - leftArraySize; 
//		
//		mergeSort(a, leftArraySize);
//
//		mergeSort((a+leftArraySize), rightArraySize);
//		
//		merge(a, leftArraySize, rightArraySize); 
//	}
//}

//void merge(Entry a[], int leftArraySize, int rightArraySize){
//	Entry* tempArray;
//	//vector<Entry> tempV;
//	int copied = 0;
//	int leftCopied = 0;
//	int rightCopied = 0;
//
//	tempArray = new Entry[leftArraySize + rightArraySize]; 
//	
//	while((leftCopied<leftArraySize) && (rightCopied < rightArraySize)){
//		if(a[leftCopied].get_key() < (a + rightArraySize)[rightCopied].get_key()){
//			tempArray[copied++] = a[leftCopied++]; 
//		}else{
//			tempArray[copied++] = (a + leftArraySize)[rightCopied++]; 
//		}
//	}
//	
//	while(leftCopied <leftArraySize){
//		tempArray[copied++] = a[leftCopied++]; 
//	}
//
//	while(rightCopied < rightArraySize){
//		tempArray[copied++] = (a + leftArraySize)[rightCopied++];
//	}
//
//	for(int i=0; i<leftArraySize + rightArraySize; i++){
//		a[i] = tempArray[i];
//	}
//
//	delete[] tempArray; 
//}
void merge(Entry arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    Entry L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i].get_key() <= R[j].get_key()) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSort(Entry arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 

int Table::hashFunction(int key, int entries) const{ //not sure why do I need to put const at the end; 
	return key % entries;
}




 	
Table::Table(unsigned int max_entries){ //do not redefine default parameter in cpp file. 
	BUCKET = 100;
	table = new list<Entry>[BUCKET];//used table as a pointer to the array of list;  
}

Table::Table(unsigned int entries, std::istream& input){
	BUCKET = entries; 
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
	if(BUCKET == 0) return false;
	 
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
	int size = t.BUCKET; //???
	int count = 0; 
	//Entry a[] = new Entry[size];
	Entry* a = new Entry[size]; 
 	//repeat for loop
//	for(int i = 0; i < size; i++){
//		for(list<Entry>::iterator j = t.table[i].begin(); j != t.table[i].end(); j++){
//			a[count] = *j; 
//			count++; 
//		}
//	}
	 
	for(int i = 0; i < size; i++){
		for(list<Entry>::iterator j = t.table[i].begin(); j != t.table[i].end(); j++){
			a[count] = *j;
			count++;
		}
	}
	//cout<<"The total number of elements in this vector is" << count<<endl;

	mergeSort(a, 0, count-1); //merge sort is not called on Table object;  
	for(int k = 0; k < count; k++){
		out << toString(a[k]); 
	}

//	delete[] a; 

	return out; 
}






