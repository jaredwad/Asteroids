/**************************************************
 * ROCK HEADER
 ***************************************************************/
#ifndef ROCK_H
#define ROCK_H

#include <iostream>
#include "moveable.h"
#include "uiDraw.h"

/****************************************************************
 * CLASS ROCK
 * This is the parents class for all of the rocks.
 ***************************************************************/
class Rock : public Shootable
{
  public:
   //Constructor
  Rock(string type, int radius, int rotation, int score)
     : Shootable(type, Point(-199,random(-200,200)), radius, score),
      orientation(random(0,100)), rotation(rotation)               {};

  Rock(string type, Point point,
       int radius, int rotation, int score)
     : Shootable(type, point, radius, score),
      orientation(random(0,100)), rotation(rotation)               {};
   
  Rock(string type, Point point, Vector vector,
       int radius, int rotation, int score)
     : Shootable(type, point, vector, radius, score),
      orientation(random(0,100)), rotation(rotation) {};
   
   void move()             { addPoint(vector.getDx(), vector.getDy());};
   void advance();
   int setScore(int score) { score += 10;   };
   int getScore()          { return score;  };
   void kill()             { fDead = true;  };
   bool isKilled()         { return killed; };
   virtual void draw()
   {
      drawFullCircle(point, radius, sides, orientation);
      orientation -= rotation;
   };

  protected:
   bool killed;
   int size;
   int sides;
   int score;
   int orientation;
   int rotation;
};

/******************************************
 * SMALL ROCK
 * The smaller asteroid. It's worth 10 pts.
 *****************************************/
class SRock : public Rock
{
  public:
  SRock()                           : Rock("SRock", 11, 3, 10)        {};
  SRock(Point point)                : Rock("SRock", point, 11, 3, 10) {};
  SRock(Point point, Vector vector)
     : Rock("SRock", point, vector, 11, 3, 10)                        {};

   void draw() {drawSRock(point, radius);};
};

/***********************************************
 * MEDIUM ROCK
 * The mdeium sixed asteroid. It's worth 15 pts.
 *********************************************/
class MRock : public Rock
{
  public:
  MRock()                           : Rock("MRock", 14, 2, 15)        {};
  MRock(Point point)                : Rock("MRock", point, 14, 2, 15) {};
  MRock(Point point, Vector vector)
     : Rock("MRock", point, vector, 14, 2, 15)                        {};

   void draw() {drawMRock(point, radius);};
};

/************************************************
 * LARGE ROCK
 * The biggest of the asteroids. It's worth 20 pts.
 ***********************************************/
class LRock : public Rock
{
  public:
  LRock()                           : Rock("LRock", 20, 1, 20)        {};
  LRock(Point point)                : Rock("LRock", point, 20, 1, 20) {};
  LRock(Point point, Vector vector)
     : Rock("LRock", point, vector, 20, 1, 20)                        {};

   void draw() {drawLRock(point, radius);};
};

#endif //ROCK_H
