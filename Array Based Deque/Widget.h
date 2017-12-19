#if !defined (WIDGET_H)
#define WIDGET_H

class Widget{
  private:
    double pricePayed;
  public:
    //pre: price is a value between 0, 1000000
    //post: pricePayed is set to price
    Widget(double price);
    ~Widget();

    //pre: none
    //post: pricePayed is returned
    double getCostWidget();

    //pre: price is a value between 0, 1000000
    //post: pricePayed is set to price
    void setCostWidget(double price);
};
#endif
