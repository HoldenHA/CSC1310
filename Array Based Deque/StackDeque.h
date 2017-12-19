#if !defined (STACKDEQUE_H)
#define STACKDEQUE_H

#include "DequeArray.h"
#include <iostream>
using namespace std;

template < class T >
class StackDeque{
  private:
    DequeArray<T>* stackDQ;
  public:
    StackDeque();
    ~StackDeque();
    bool isEmpty();
    int sizeStack();

    //pre: none
    //post: an object of type T is returned from back of stack; object pointer is removed from stack
    T* popStack();

    //pre: T* item is an object pointer of type T
    //post: item is placed on stack
    void pushStack(T* item);

    //pre: none
    //post: an object of type T is returned from back of stack
    T* peekStack();

};

template < class T >
StackDeque<T>::StackDeque(){
  stackDQ = new DequeArray<T>;
}

template < class T >
StackDeque<T>::~StackDeque(){
  delete stackDQ;
}

template < class T >
bool StackDeque<T>::isEmpty(){
  return stackDQ->isEmpty();
}

template < class T >
int StackDeque<T>::sizeStack(){
  return stackDQ->size();
}

template < class T >
T* StackDeque<T>::popStack(){
  T* item = stackDQ->dequeueDeque();
  return item;
}

template < class T >
void StackDeque<T>::pushStack(T* item){
  stackDQ->enqueue(item);
}

template < class T >
T* StackDeque<T>::peekStack(){
  T* item = stackDQ->peekDeque();
  return item;
}
#endif
