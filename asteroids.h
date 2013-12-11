/****************************************************************
 * ASTEROIDS HEADER
 * This is the class contains the functions that
 * regulate the game, by passing info from all of the other classes
 * (rocks, ships, bullets, etc).
 ***************************************************************/
#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "moveable.h"
#include "rock.h"
#include "uiDraw.h"
#include "vector.h"
#include <list>
using namespace std;

#define PI 3.141592653589793238462643383279502884197169399375105820
//Extra precise

/****************************************************
 * CLASS ASTEROIDS
 * This contains all of the function headers and inline functions
 * that belong to ASTEROIDS
 ***************************************************/
class Asteroids
{
  public:
   // constructor
  Asteroids() : level(1), fCount(false), countDown(0), score(0)
   {
      objects.push_back(new Ship );
      objects.push_back(new LRock);
      objects.push_back(new LRock);
   };

   // draw functions
   void draw();
   void drawLives();
   void drawScore();
   void drawLevel();

   void interact(int isUp, int isDown, int isLeft,
                 int isRight, bool isSpace,
                 bool isW, bool isL);
   
   void advance (); 
   void hit     (std::list<Moveable*>::iterator & iter);
   int  getLevel() {return level;};
   int  getScore() {return score;};

   std::list<Moveable*>::iterator getStart() { return objects.begin(); };
   std::list<Moveable*>::iterator getEnd()   { return objects.end();   };
   
  private:
   list<Moveable*> objects; // a list of pointers to the objects
   Point point;
   bool fCount;
   int countDown;
   int level;
   unsigned int score; // yes our score gets that big
};
#endif // ASTEROIDS_H
