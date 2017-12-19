#include "InventoryManager.h"
#include "Widget.h"
#include "StackDeque.h"
#include "QueueDeque.h"

#include <iostream>
using namespace std;

InventoryManager::InventoryManager(bool inventory_choice){
  QorS = inventory_choice;
  if(QorS){
    myStack = new StackDeque<Widget>;
  }else{
    myQueue = new QueueDeque<Widget>;
  }

  totalProfit = 0;
}

InventoryManager::~InventoryManager(){
  if(QorS) delete myStack; else delete myQueue;
}

void InventoryManager::buyWidgets(double cost, int num_to_buy){
  Widget* myWidget = new Widget(cost);

  if(QorS){
    for(int i = 0; i < num_to_buy; i++){
      myStack->pushStack(myWidget);
    }
  }else{
    for(int i = 0; i < num_to_buy; i++){
      myQueue->enqueueQueue(myWidget);
    }
  }
}

double InventoryManager::getTotalProfit(){
  return totalProfit;
}

double InventoryManager::sellWidgets(double price, int num_to_sell){
  int counter = 0; 
  double sellPrice = 0;
  double widgetCost = 0;

  if(QorS){
    while(counter < num_to_sell && !myStack->isEmpty()){
      widgetCost = myStack->popStack()->getCostWidget();
      sellPrice += price - widgetCost;
      counter ++;
    }
  }else{
    while(counter < num_to_sell && !myQueue->isEmpty()){
      widgetCost = myQueue->dequeueQueue()->getCostWidget();
      sellPrice += price - widgetCost;
      counter++;
    }
  }
  totalProfit += sellPrice;

  return sellPrice;
}
