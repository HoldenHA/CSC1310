#include <iostream>
#include "PQSort.h"
#include "ListArray.h"
#include "CD.h"

using namespace CSC1310;
using namespace std;

int main(){
	PQSort<CD>* sorter = new PQSort<CD>();
	ListArray<CD>* list = CD::readCDs("cds.txt");
	int size = list->size();

	CD** cds = new CD*[size];

	ListArrayIterator<CD>* iter = list->iterator();
	int count = 0;
	while(iter->hasNext())
	{
		CD* cd = iter->next();
		cds[count] = cd;
		count++;
	}
	delete iter;
	
	//min_or_max = FALSE 
	CD** sortedCDs = sorter->pqSort(cds, size, FALSE, &CD::compare_items, &CD::compare_keys);
	
	//min_or_max = TRUE 
	//CD** sortedCDs = sorter->pqSort(cds, size, TRUE, &CD::compare_items, &CD::compare_keys);
	
	for(int i = 0; i < size; i++){
		sortedCDs[i]->displayCD();
	}
	
	delete sortedCDs;
	delete cds;
}