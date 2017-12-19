#if !defined (QUEUEDEQUE_H)
#define QUEUEDEQUE_H

#include "DequeArray.h"
#include <iostream>
using namespace std;

template < class T >
class QueueDeque{
  private:
    DequeArray<T>* QueueDQ;
  public:
    QueueDeque();
    ~QueueDeque();
    bool isEmpty();
    int sizeQueue();

    //pre: none
    //post: an object of type T is returned from front of queue, object pointer is removed from queue
    T* dequeueQueue();

    //pre: item is an object pointer of type T
    //post: itme is placed at the back of the queue
    void enqueueQueue(T* item);

    //pre: none
    //post:  an object of type T is returned from front of queue
    T* peekQueue();

};

template < class T >
QueueDeque<T>::QueueDeque(){
  QueueDQ = new DequeArray<T>;
}

template < class T >
QueueDeque<T>::~QueueDeque(){
  delete QueueDQ;
}

template < class T >
bool QueueDeque<T>::isEmpty(){
  return QueueDQ->isEmpty();
}

template < class T >
int QueueDeque<T>::sizeQueue(){
  return QueueDQ->size();
}

template < class T >
T* QueueDeque<T>::dequeueQueue(){
  T* item = QueueDQ->dequeue();
  return item;
}

template < class T >
void QueueDeque<T>::enqueueQueue(T* item){
  QueueDQ->enqueue(item);
}

template < class T >
T* QueueDeque<T>::peekQueue(){
  T* item = QueueDQ->peek();
  return item;
}
#endif
