#include "InventoryManager.h"
#include "1310/CSC1310/Text.h"
using CSC1310::String;
#include "1310/CSC1310/Keyboard.h"
using CSC1310::Keyboard;

#include <iostream>
#include <iomanip>
using namespace std;

int inventoryChoice()
{
   Keyboard* kb = Keyboard::getKeyboard();
   int inv_choice = kb->getValidatedInt("Are you using (1) LIFO or (2) FIFO inventory management? ", 1, 2);
   return inv_choice;
}

//DO THIS
//buy Widgets (check invalid input and reprompt if necessary)
void buyWidgets(InventoryManager* im)
{
  Keyboard* kb = Keyboard::getKeyboard();
  int numBuy = kb->getValidatedInt("How many widgets would you like to buy? ", 1, 1000000);
  double costBuy = kb->getValidatedDouble("What is the cost for each widget? ", 0, 1000000);
  im->buyWidgets(costBuy, numBuy);
}

//DO THIS
//sell Widgets and return the profit (check invalid input and reprompt if necessary)
void sellWidgets(InventoryManager* im)
{
  cout << setprecision(2) << fixed;
  Keyboard* kb = Keyboard::getKeyboard();
  int numSell = kb->getValidatedInt("How many widgets would you like to sell? ",1, 1000000);
  double sellPrice = kb->getValidatedDouble("What is the selling price for each widget? ",0, 1000000);

  cout << endl;
  cout << "Your profit on this transaction is $" <<  im->sellWidgets(sellPrice, numSell) << endl;
}

bool mainMenu(InventoryManager* im)
{
   Keyboard* kb = Keyboard::getKeyboard();
   cout << endl;
   int menu_choice = kb->getValidatedInt("1. Buy Widgets \r\n2. Sell Widgets\r\n3. Quit\r\nWhat would you like to do? ", 1, 3);
   cout << endl;
   if (menu_choice == 1)
   {
      buyWidgets(im);
      return 1;
   }
   else if(menu_choice == 2)
   {
      sellWidgets(im);
      return 1;
   }
   else
   {
      return 0;
   }
}

int main()
{
   cout << setprecision(2) << fixed;

   int invCh = inventoryChoice();
   bool inv_choice = 0;

   if(invCh == 1) inv_choice = 1; else inv_choice = 0;
   InventoryManager* im = new InventoryManager(inv_choice);

   bool ask = 1;
   while (ask)
   {
      ask = mainMenu(im);
   }

   double running_total = im->getTotalProfit();
   cout << "Your total profit for all transactions is $" << running_total << endl;

   delete im;
}
