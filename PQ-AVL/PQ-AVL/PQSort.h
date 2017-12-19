#if !defined (PQSort_H)
#define PQSort_H

#include <iostream>
#include "PQAVL.h"
using namespace std;

template < class T >
class PQSort{
	private:
		/*
		pre: items is array to be sorted; num_items is number of items in items; min_or_max determines if items is sorted ascending or descending;
			compare_item/comp_key are function pointers 
		post: items is sorted using PQAVL
		*/
		static void _pqSort(T** items, int num_items, bool min_or_max, int (*compare_item) (T* one, T* two), int (*comp_key) (String* key, T* item));
		
	public:
		//pre: none 
		//post: PQSort object is created 
		PQSort();
		
		//pre: none 
		//post: PQSort object is deleted 
		~PQSort();
		
		/*
		pre: items is array to be sorted; num_items is number of items in items; min_or_max determines if items is sorted ascending or descending;
			compare_item/comp_key are function pointers 
		post: sorted T* array is returned
		*/
		static T** pqSort(T** items, int num_items, bool min_or_max, int (*compare_item) (T* one, T* two), int (*comp_key) (String* key, T* item));
};

template < class T >
PQSort<T>::PQSort(){
}

template < class T >
PQSort<T>::~PQSort(){
}

template < class T >
void PQSort<T>::_pqSort(T** items, int num_items, bool min_or_max, int (*compare_item) (T* one, T* two), int (*comp_key) (String* key, T* item)){
	PQAVL<T>* sorter = new PQAVL<T>(min_or_max, compare_item, comp_key);
	
	for(int i = 0; i < num_items; i++){
		sorter->pqInsert(items[i]);
	}
	
	for(int i = 0; i < num_items; i++){
		items[i] = sorter->pqRemove();
	}
	
	delete sorter;
}

template < class T >
T** PQSort<T>::pqSort(T** items, int num_items, bool min_or_max, int (*compare_item) (T* one, T* two), int (*comp_key) (String* key, T* item)){
	T** sortedArr = new T*[num_items];
	for(int i = 0; i < num_items; i++){
		sortedArr[i] = items[i];
	}
	
	_pqSort(sortedArr, num_items, min_or_max, compare_item, comp_key);
	
	return sortedArr;
}

#endif