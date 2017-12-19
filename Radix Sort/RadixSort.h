#if !defined (RADIXSORT_H)
#define RADIXSORT_H

#include "QueueLinked.h"
#include <string>
#include <iostream>

using namespace std;
using CSC1310::QueueLinked;

template < class T >
class RadixSort
{
   private:
     //pre:: bin is a unsorted QueueLinked to be sorted using bins
     //post:: bin is sorted
      static void binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char (*getRadixChar) (T* item, int index));
      //pre:: sort is an array of unsorted T*'s to be sorted
      //post:: sort is sorted in ascending order
      static void radixSortAsc(T** sort, int n, int num_chars, char (*getRadixChar) (T* item, int index));  //algorithm 1
      //pre:: sort is an array of unsorted T*'s to be sorted
      //post:: sort is sorted in descending order
      static void radixSortDesc(T** sort, int n, int num_chars, char (*getRadixChar) (T* item, int index));  //algorithm 2

   public:
     //pre:: sort is an array of unsorted T*'s to be sorted; asc determines if the array is sorted ascending or descending
     //post:: sort is sorted either ascending or descending depending on the value of asc
      static T** radixSort(T** sort, int num_to_sort, int num_chars, bool asc, char (*getRadixChar) (T* item, int index));
};

template < class T >
T** RadixSort<T>::radixSort(T** unsorted, int num_to_sort, int num_chars, bool asc, char (*getRadixChar) (T* item, int index))
{
   if(asc){
     radixSortAsc(unsorted, num_to_sort, num_chars, getRadixChar);
     return unsorted;
   }else{
      radixSortDesc(unsorted, num_to_sort, num_chars, getRadixChar);
      return unsorted;
   }

}

template < class T >
void RadixSort<T>::radixSortAsc(T** sort, int n, int num_chars, char (*getRadixChar) (T* st, int index))
{
  QueueLinked<T>* sortBin = new QueueLinked<T>;

  for(int i = 0; i < n; i++){
    sortBin->enqueue(sort[i]);
  }

  binSort(sortBin, 1, num_chars, getRadixChar);

  for(int i = 0; i < n; i++){
    sort[i] = sortBin->dequeue();
  }
}

template < class T >
void RadixSort<T>::binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char (*getRadixChar) (T* st, int index))
{
  int num_queues = 37;  //covers letters and digits
  int ch = 0;
  QueueLinked<T>** bins = new QueueLinked<T>*[num_queues];

  //must instantiate each of the queues
  for (int i = 0; i < num_queues; i++)
  {
     bins[i] = new QueueLinked<T>();
  }

  while(!bin->isEmpty()){
    ch = toupper(getRadixChar(bin->peek(), curr_char));
    if(ch <= 90 && ch >= 65){
      bins[ch % 55] -> enqueue(bin->dequeue());
    }else if (ch >= 48 && ch <= 57){
      bins[ch % 48] -> enqueue(bin->dequeue());
    }else{
      bins[36] -> enqueue(bin->dequeue());
    }
  }


  for (int i = 0; i < num_queues; i++){
    if(bins[i]->size() > 1){
      binSort(bins[i], curr_char + 1, num_chars, getRadixChar);
    }
  }

  for(int i = 0; i < num_queues; i++)
  {
    while(!bins[i]->isEmpty()){
      bin->enqueue(bins[i]->dequeue());
    }
  }

  for (int i = 0; i < num_queues; i++)
  {
    delete bins[i];
  }

  delete[] bins;
}

template < class T >
void RadixSort<T>::radixSortDesc(T** sort, int n, int num_chars, char (*getRadixChar) (T* st, int index))
{
  int ch = 0;
  int ch2 = 0;
  int counter = 0;
  int counter2 = 0;
  int num_queues = 37;
  T** sorter = new T*[n];

  QueueLinked<T>** bins = new QueueLinked<T>*[num_queues];

  for(int i = 0; i < num_queues; i++){
    bins[i] = new QueueLinked<T>;
  }

  for(int i = 0; i < n; i++){
    ch = toupper(getRadixChar(sort[i], num_chars));

    if(ch <= 90 && ch >= 65){
      bins[ch % 55] -> enqueue(sort[i]);
    }else if (ch >= 48 && ch <= 57){
      bins[ch % 48] -> enqueue(sort[i]);
    }else{
      bins[36] -> enqueue(sort[i]);
    }
  }

  for(int i = num_queues-1; i > 0; i--){
    while(!bins[i]->isEmpty()){
      sorter[counter] = bins[i]->dequeue();
      counter++;
    }

    for(int j = 0; j < counter-1; j++){
      for(int x = 0; x < counter-1-j; x++){
        ch = toupper(getRadixChar(sorter[x], num_chars-1));
        ch2 = toupper(getRadixChar(sorter[x+1], num_chars-1));
        if(ch < ch2){
          T* temp = sorter[x];
          sorter[x] = sorter[x+1];
          sorter[x+1] = temp;
        }
      }
    }

    for(int k = 0; k < counter; k++){
      bins[i]->enqueue(sorter[k]);
    }

    while(!bins[i]->isEmpty()){
      sort[counter2] = bins[i]->dequeue();
      counter2++;
    }
    counter = 0;
  }

  for (int i = 0; i < num_queues; i++)
  {
    delete bins[i];
  }

  delete[] bins;


}

#endif
