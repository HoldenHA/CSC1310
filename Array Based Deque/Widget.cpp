#include "Widget.h"
using namespace std;

Widget::Widget(double price){
  pricePayed = price;
}

Widget::~Widget(){
}

double Widget::getCostWidget(){
  return pricePayed;
}

void Widget::setCostWidget(double price){
  pricePayed = price;
}
