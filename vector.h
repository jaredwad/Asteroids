/****************************************************************
 * VECTOR HEADER FILE
 * This pertains to the directions of the different objects. such as
 * SHIP, and ROCK. It's primary puporse is to be referenced by them.
 ***************************************************************/
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cassert>
#include "point.h"
#include "uiDraw.h"

class Vector
{
  public:
  Vector() { randVect(); };
  Vector(int dx, int dy) : dx(dx), dy(dy) {};
  
   // getters
   Point const getPoint();
   float getDx() const {return dx;};
   float getDy() const {return dy;};

   // setters
   void setDx(float x) {dx = x;};
   void setDy(float y) {dy = y;};

   void randVect()
   {
      setDx(random(-3,3));
      setDy(random(-3,3));
      if (getDx() == 0 || getDy() == 0)
         randVect();
      assert(getDx() != 0 && getDy() != 0);
   };

   Vector & operator +=(Vector v)
   {
      dx += v.getDx();
      dy += v.getDy();
   }

   Vector & operator -()
   {
      dx = -dx;
      dy = -dy;
   }

   Vector & operator *(int change)
   {
      dx *= change;
      dy *= change;
   }

   Vector & operator *=(int change)
   {
      dx *= change;
      dy *= change;
   }

   
   Vector & operator /=(int change)
   {
      dx /= change;
      dy /= change;
   };
   // stream I/O useful for debugging
   friend std::ostream & operator << (std::ostream & out, const Vector & vect)
   {
      out << "(" << vect.getDx() << ", " << vect.getDy() << ")";
      return out;
   };

  private:
   float dx;
   float dy;
};


#endif // VECTOR_H
