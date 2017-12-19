#if !defined (INVENTORYMANAGER_H)
#define INVENTORYMANAGER_H

#include "StackDeque.h"
#include "QueueDeque.h"
#include "Widget.h"
using namespace std;

class InventoryManager
{ 
  private:
    bool QorS;
    StackDeque<Widget>* myStack;
    QueueDeque<Widget>* myQueue;
    double totalProfit;

  public:
    //pre: inventory_choice is a boolean where true = LIFO (stack) and false = FIFO (queue)
    //post: QorS is set to the value of inventory_choice, and a InventoryManager object is made
    InventoryManager(bool inventory_choice); //LIFO or FIFO
    ~InventoryManager();

    //pre: cost is double between 0, 1000000; num_to_buy is an int between 1, 1000000
    //post: num_to_buy widgets of cost cost are placed on the queue(0) or stack(1)
    void buyWidgets(double cost, int num_to_buy);

    //pre: none
    //post: totalProfit is returned; totalProfit is total of all calls to sellWidgets
    double getTotalProfit();

    //pre: price is double between 0, 1000000; num_to_sell is an int between 1, 1000000
    //post: num_to_sell widgets are removed from queue(0) or stack(1), sellWidgets = price - costWidgets (ran num_to_sell times against queue or stack)
    double sellWidgets(double price, int num_to_sell);
};
#endif
