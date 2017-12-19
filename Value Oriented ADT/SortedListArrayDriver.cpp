/*
  Holden Ayers
  9.27.2017
  Dr.Brown CSC 1310
  Program 1: Value Oriented ADT
*/

#include "SortedListArray.h"
#include "CD.h"
using CSC1310::CD;
using CSC1310::ListArray;
#include "ListArrayIterator.h"
using CSC1310::ListArrayIterator;

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
   ListArray<CD>* cds = CD::readCDs("cds.txt");
   SortedListArray<CD>* cdss = new SortedListArray<CD>(&CD::compare_items, &CD::compare_keys);
   ListArrayIterator<CD>* iter1 = cds->iterator();

   while(iter1->hasNext()){ //adds the cds from the list array to the sorted list array
     cdss->add(iter1->next());
   }

  ListArrayIterator<CD>* iter2 = cdss->iterator();
  //all these tests are done using the CD class that compares artists instead of titles, to change just replace each getArtist() with getKey() and uncomment the lines in CD.cpp
  /*
  //test that displays each cd, in sorted order, from the sorted list array of cds
  while(iter2->hasNext()){
      iter2->next()->displayCD();
  }
  */

   /*
   //test to remove a cd that does not exsist
   String* compare = new String("Bob");
   cdss->remove(compare);
   while(iter2->hasNext()){
       iter2->next()->displayCD();
   }
   */

   /*
   //test that deletes all the cds in the sorted list array then tries to display them
   ListArrayIterator<CD>* iter3 = cdss->iterator();
   while(iter2->hasNext()){
     String* myString = iter2->next()->getArtist();
     cdss->remove(myString);
   }
   while(iter2->hasNext()){
     iter2->next()->displayCD();
   }
   */

   /*
   //test that, after removing all the cds from the sorted list array checks if the array is empty of not
   ListArrayIterator<CD>* iter3 = cdss->iterator();
   while(iter2->hasNext()){
     String* myString = iter2->next()->getArtist();
     cdss->remove(myString);
   }
   cout << cdss->isEmpty() << endl;
   */

   /*
   //test that displays each cd in the list by using the sorted list array's get function
   while(iter2->hasNext()){
     cdss->get(iter2->next()->getArtist())->displayCD();
   }
   */

   deleteCDs(cds);
   delete cds;

   return 0;
}
