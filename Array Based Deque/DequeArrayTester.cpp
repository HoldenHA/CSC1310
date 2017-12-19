#include "DequeArray.h"
#include <iostream>
using namespace std;

int main(){
  DequeArray<int>* myDeque = new DequeArray<int>;

  int one2 = 1;
  int two2 = 2;
  int three2 = 3;

  myDeque->enqueue(&one2);
  myDeque->enqueue(&two2);
  myDeque->enqueue(&three2);
  cout << "Enqueue test::" << endl;
  while(!myDeque->isEmpty()){
    cout << *myDeque->dequeue() << endl;
  }
  cout << endl;


  myDeque->enqueue(&one2);
  myDeque->enqueue(&two2);
  myDeque->enqueue(&three2);

  cout << *myDeque->peek() << endl;
  cout << *myDeque->peekDeque() << endl;
  cout << "Past peek in 1 dequeue test" << endl;

  myDeque->dequeue();
  while(!myDeque->isEmpty()){
    cout << *myDeque->dequeue() << endl;
  }
  cout << endl;


  myDeque->enqueue(&one2);
  myDeque->enqueue(&two2);
  myDeque->enqueue(&three2);

  cout << *myDeque->peek() << endl;
  cout << *myDeque->peekDeque() << endl;
  cout << "Past peek in dequeue deque test" << endl;

  myDeque->dequeueDeque();
  while(!myDeque->isEmpty()){
    cout << *myDeque->dequeue() << endl;
  }
  cout << endl;


  myDeque->enqueue(&one2);
  myDeque->enqueue(&two2);
  myDeque->enqueue(&three2);

  cout << *myDeque->peek() << endl;
  cout << *myDeque->peekDeque() << endl;
  cout << "Past peek in normal enqueue then dequeueDeque test" << endl;

  while(!myDeque->isEmpty()){
    cout << *myDeque->dequeueDeque() << endl;
  }
  cout << endl;


  cout << "Deque test::" << endl;

  myDeque->enqueueDeque(&one2);
  myDeque->enqueueDeque(&two2);
  myDeque->enqueueDeque(&three2);

  while(!myDeque->isEmpty()){
    cout << *myDeque->dequeue() << endl;
  }
  cout << endl;
  myDeque->dequeueAll();

  cout << "Dequeue deque test::" << endl;

  myDeque->enqueueDeque(&one2);
  myDeque->enqueueDeque(&two2);
  myDeque->enqueueDeque(&three2);

  while(!myDeque->isEmpty()){
    cout << *myDeque->dequeueDeque() << endl;
  }

  
  delete myDeque;
}
