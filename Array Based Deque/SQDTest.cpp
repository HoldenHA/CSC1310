#include "StackDeque.h"
#include "QueueDeque.h"
#include "DequeArray.h"
#include "Widget.h"
#include <iostream>
using namespace std;

int main(){
  StackDeque<int>* myStack = new StackDeque<int>;
  QueueDeque<int>* myQueue = new QueueDeque<int>;

  int myArr [5] = {1,2,3,5,4};

  for(int i = 0; i < 5; i++){
    myStack->pushStack(&myArr[i]);
    myQueue->enqueueQueue(&myArr[i]); 
  }

  cout << "Stack first::" << endl;
  while(!myStack->isEmpty()){
    cout << *myStack->popStack() << endl;
  }
  cout << endl;

  cout << "Queue second::" << endl;
  while(!myQueue->isEmpty()){
    cout << *myQueue->dequeueQueue() << endl;
  }

  cout << "Widget test::" << endl;
  StackDeque<Widget>* myWidgets = new StackDeque<Widget>;
  Widget* newWidget = new Widget(3);

  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);
  myWidgets->pushStack(newWidget);

  while(!myWidgets->isEmpty()){
    cout << myWidgets->popStack()->getCostWidget() << endl;
  }

}
