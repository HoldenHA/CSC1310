#ifndef CIRCLE_H
#define CIRCLE_H

#include "Color.h"
#include "Text.h"
#include "wx/wx.h"

class Circle 
{
   private:
      int radius;
      Color* color;
      CSC1310::String* text;
      static const float PI2 = 6.283854;

   public:
      Circle(Color* color, int radius, CSC1310::String* text);
      ~Circle();
      void draw(wxDC& dc, int x, int y);
};

#endif