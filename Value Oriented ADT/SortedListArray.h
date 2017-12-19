/*
  Holden Ayers
  9.27.2017
  Dr.Brown CSC 1310
  Program 1: Value Oriented ADT
*/

#if !defined(SORTEDLISTARRAY_H)
#define SORTEDLISTARRAY_H

#include "Text.h"
#include "ListArrayIterator.h"
#include <iostream>

using namespace std;
using CSC1310::String;
using CSC1310::ListArrayIterator;

template <class T>
class SortedListArray
{
   private:
      T** items;
      int max_size;
      int sz;

      int (*compare_items)(T* item_1, T* item_2);
      int (*compare_keys)(String* key, T* item);

      void arrayResize(int new_max_size);

      //pre:: method is passed an item whose proper sorted index is to be found
      //post:: using binary search algorithm, determines the index that the item should be placed in the array and returns the index
      int addBinarySearch(T* item);

      //pre:: method is passed a search_key to remove or get from the sorted list array
      //post:: if the desired item is in the array, will return the index of the item found using binary search algorithm; if not found returns -1
      int removeBinarySearch(String* search_key);

   public:
      //pre:: exsisting list array containing all the elements to be added, unsorted, along with function that compare items and string of that particular type of data
      //post:: a sorted list array containg all the items from the original list array
      SortedListArray(int (*comp_items)(T* item_1, T* item_2), int (*comp_keys)(String* key, T* item));

      //deletes the sorted list array
      ~SortedListArray();

      //pre:: none
      //post:: returns if the sorted list array contains data or no 1 = data 0 = no data
      bool isEmpty();

      //pre:: none
      //post:: returns the size of the sorted list array, contained in a private int
      int size();

      //pre:: method is passed a search_key to be found inside the sorted list array
      //post:: searches the sorted list array for the search key, returns the item if found, if not found returns NULL, uses binary search to find index
      T* get(String* search_key);

      //pre:: method is passed T* item (templated item pointer)
      //post:: adds the item to the sorted list array in the proper position, determined by a binary search
      void add(T* item);

      //pre:: method is passed a search_key to remove form the sorted list array
      //post:: if the item with the same name as the search key is found, removes the item, otherwise does nothing, uses binary search to find index for item to be removed
      void remove(String* search_key);

      //pre:: none
      //post:: creates a iterator that can iterate through the sorted list array
      ListArrayIterator<T>* iterator();
};

template < class T >
SortedListArray<T>::SortedListArray(int (*comp_items)(T* item_1, T* item_2), int (*comp_keys)(String* key, T* item))
{
   max_size = 2;
   items = new T*[max_size];
   for (int i = 0; i < max_size; i++)
   {
      items[i] = NULL;
   }
   sz = 0;

   compare_items = comp_items;
   compare_keys = comp_keys;
}

template < class T >
SortedListArray<T>::~SortedListArray()
{
   delete[] items;  //the individual items themselves are not deleted
}

template < class T >
int SortedListArray<T>::addBinarySearch(T* item)
{
  int F = 0;
  int index = size()-1;
  int mid = F + ((index-F) / 2);
  int compare = 0;

  if(size() == 0) return 1;

  while(F <= index){
    compare = (*compare_items)(item, items[mid]);
    if(compare == 0){
      return mid+1;
    }else if(compare < 0){
      index = mid - 1;
    }else{
      F = mid + 1;
    }
    mid = F + ((index-F) / 2);
  }
   return mid + 1;
}

template < class T>
int SortedListArray<T>::removeBinarySearch(String* search_key)
{
  int F = 0;
  int index = size()-1;
  int mid = F + ((index-F) / 2);
  int compare = 0;

  while(F <= index){
    compare = (*compare_keys)(search_key, items[mid]);
    if(compare == 0){
      return mid;
    }else if(compare < 0){
      index = mid - 1;
    }else{
      F = mid + 1;
    }
    mid = F + ((index-F) / 2);
  }
   return -1;
}

template < class T >
bool SortedListArray<T>::isEmpty()
{
   return (sz == 0);
}

template < class T >
int SortedListArray<T>::size()
{
   return sz;
}

template < class T >  //1-based
T* SortedListArray<T>::get(String* search_key)
{
  int index = removeBinarySearch(search_key);
  if(index < 0){
    return NULL;
  }

  return items[index];
}

template < class T >
void SortedListArray<T>::add(T* item)
{
   int index = addBinarySearch(item);
   //need more room in the array list
   if (sz == max_size)
   {
      arrayResize(2*max_size);
   }

   for (int i = sz; i >= index; i--)
   {
      items[i] = items[i - 1];
   }

   items[index - 1] = item;
   sz++;
}

template < class T >
void SortedListArray<T>::remove(String* search_key)
{
   int index = removeBinarySearch(search_key);


   if(index >= 0){
     for (int i = index; i < sz; i++)
     {
        items[i - 1] = items[i];
     }

     items[sz - 1] = NULL;
     sz--;
   }

/*
   if (sz < max_size/2 - 1) //halve the size of the array, smallest size of max_size should be 2
   {
      arrayResize(max_size/2);
   }
*/
}

template < class T >
ListArrayIterator<T>* SortedListArray<T>::iterator()
{
   ListArrayIterator<T>* iter = new ListArrayIterator<T>(items, sz);
   return iter;
}

template < class T >
void SortedListArray<T>::arrayResize(int new_max_size)
{
   max_size = new_max_size;
   T** temp = new T*[max_size];

   for (int i = 0; i < sz; i++)
   {
      temp[i] = items[i];
   }
/*+
   for (int i = sz; i < max_size; i++)
   {
      temp[i] = NULL;
   }
*/
   delete[] items;
   items = temp;
}

#endif
