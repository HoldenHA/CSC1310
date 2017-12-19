#include "RadixSort.h"
#include "CD.h"
using CSC1310::CD;
#include "ListArray.h"
using CSC1310::ListArray;
#include "ListArrayIterator.h"
using CSC1310::ListArrayIterator;
#include "Text.h"
using CSC1310::String;

#include <iostream>
using namespace std;

void deleteCDs(ListArray<CD>* list)
{
   ListArrayIterator<CD>* iter = list->iterator();

   while(iter->hasNext())
   {
      CD* cd = iter->next();
      delete cd;
   }
   delete iter;
}

int main()
{
   RadixSort<CD>* sorter = new RadixSort<CD>;
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

   CD** sortAsc = new CD*[size];
   CD** sortDes = new CD*[size];

   cout <<  "Sorted in ascending order:: " << endl << endl;
   sortAsc = sorter->radixSort(cds, size, 3, true, &CD::getRadixChar);
   for(int i = 0; i < size; i++){
     sortAsc[i]->displayCD();
   }

   cout <<  "Sorted in descending order:: " << endl << endl;
   sortDes = sorter->radixSort(cds, size, 3, false, &CD::getRadixChar);
   for(int i = 0; i < size; i++){
     sortDes[i]->displayCD();
   }




   delete[] cds;


   deleteCDs(list);
   delete list;

   return 0;
}
