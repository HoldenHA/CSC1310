#if !defined (PQAVL_H)
#define PQAVL_H

#include <iostream>
#include "AVLTree.h"
using namespace std;

template < class T >
class PQAVL {
	private:
		AVLTree<T>* PQ;
		
	public:
		//pre: min_or_max determines if PQAVL is min/max; compare_item/comp_key are function pointers 
		//post: a min/max PQAVL object is created based on the value of min_or_max 
		PQAVL(bool min_or_max, int (*compare_item) (T* item_1, T* item_2), int (*comp_key) (String* key, T* item));
		
		//pre: none
		//post: PQAVL object is deleted  
		~PQAVL(); 
		
		//pre: none
		//post: returns true if PQAVL is empty; else false 
		bool pqIsEmpty();
		
		//pre: item is a T* object to be inserted into PQAVL object 
		//post: item is inserted into PQAVL object at the proper location 
		void pqInsert(T* item);
		
		//pre: none
		//post: T* item at smallest or largest position in PQAVL object is returned, based on value of min_or_max
		T* pqRemove();
};

template < class T >
PQAVL<T>::PQAVL(bool min_or_max, int (*compare_item) (T* item_1, T* item_2), int (*comp_key) (String* key, T* item)){
	PQ = new AVLTree<T>(min_or_max, true, true, compare_item, comp_key);
}

template < class T >
PQAVL<T>::~PQAVL(){
	delete PQ;
}

template < class T >
bool PQAVL<T>::pqIsEmpty(){
	return PQ->isEmpty();
}

template < class T >
void PQAVL<T>::pqInsert(T* item){
	PQ->insert(item);
}

template < class T >
T* PQAVL<T>::pqRemove(){
	return PQ->remove();
}

#endif