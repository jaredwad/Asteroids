/****************************************************************
 * asteroids.CPP
 * This is really the lifeblood of the game. This is where all of
 * the other parts of the program come together to produce a game
 * even better than Halo.
 ***************************************************************/

#include <iostream>
#include <cassert>
#include "rock.h"
#include "asteroids.h"
#include "uiInteract.h" //Take the user input.
#include "uiDraw.h"     //The drawing procedures.

using namespace std;

// the ship will always be first
#define SHIP       (*objects.begin())

// set the bounds of the game
float Point::xMin =  -200.0;
float Point::xMax =  200.0;
float Point::yMin =  -200.0;
float Point::yMax =  200.0;

int Ship::lives = 4;

/***********************************************
 * ASTEROIDS::INTERACT
 * This will take the user's input and send it
 * to the correct functions. The only input is
 * the arrows as well as the space bar.
 **********************************************/
void Asteroids::interact(int isUp, int isDown,int isLeft,
                         int isRight, bool isSpace, bool isW, bool isL)
{
   // you can only move the ship
   if( SHIP->getType() == "ship")
   {
      //If the user presses up or down...
      if (isUp)
      {
         Vector v;
         v.setDx(-cos(PI * SHIP->getAngle() / 180) * .2);
         v.setDy(-sin(PI * SHIP->getAngle() / 180) * .2);
         SHIP->setVect(v);
      }

      // this may not make sense coming from a ships point of view,
      // but i think its cool
      if (isDown)
      {
         Vector v;
         v.setDx( cos(PI * SHIP->getAngle() / 180) * .2);
         v.setDy( sin(PI * SHIP->getAngle() / 180) * .2);
         SHIP->setVect(v);
      }

      //Change the angle
      if (isLeft)
         SHIP->setAngle( 8);
   
      if (isRight)
         SHIP->setAngle(-8);
   
      //If the user spaces out...
      if (isSpace)
      {
         Point  point  = SHIP->getPoint();
         Vector vector = SHIP->getVect ();
         Vector tempVect;

         tempVect.setDx(-cos(PI * SHIP->getAngle() / 180) * 10);
         tempVect.setDy(-sin(PI * SHIP->getAngle() / 180) * 10);

         vector += tempVect;
      
         objects.push_back(new DBullet(point, vector));
      }

      // say hello to bettsy
      if (isW && score >= 3)
      {

         score -= 3;
         
         Point  point  = SHIP->getPoint();
         Vector vector = SHIP->getVect ();
         Vector tempVect;

         tempVect.setDx(-cos(PI * SHIP->getAngle() / 180) * 10);
         tempVect.setDy(-sin(PI * SHIP->getAngle() / 180) * 10);

         vector += tempVect;
         Point tempPoint = ((SHIP + 1)->getPoint());
         tempVect = Vector(0,0);
      
         objects.push_back(new UPBullet(point, vector, SHIP->getAngle()));
         objects.push_back(new DBullet(point, vector));
         objects.push_back(new DNBullet(point, vector, SHIP->getAngle()));
      }

      // this way you'll never die!!!
      if (isL && score >= 200)
      {
         score -= 200;
         ((Ship*)SHIP)->addLife();
      }


   }

   // if you die you lose points
   else if (((Ship*)SHIP)->getLives() > 0)
   {
      if (score >= 50)
         score -= 50;
      else
         score = 0;
      objects.insert(objects.begin(), new Ship);
   }
}

/***************************************************************
 * DRAW
 * This will draw everything one the screen that needs to be drawn.
 **************************************************************/
void Asteroids::draw()
  {
     for (std::list<Moveable*>::iterator iter = objects.begin();
          iter != objects.end(); iter++)
        (*iter)->draw();
     drawScore();
     drawLives();
     drawLevel();
  };

/***********************************************
 * ASTEROIDS::DRAWLEVEL
 * This will call the DRAWNUMBER function from uiDraw
 * send the current level to be displayed.
 **********************************************/
void Asteroids::drawLevel()
{
   //DRAW the text. Don't write it, Draw it!
   drawText(Point(point.getXMin() + 300, point.getYMax() - 12),
            "LEVEL - " );

   //DRAW the level value
   drawNumber(Point(point.getXMin() + 360, point.getYMax() - 2),
              getLevel());
}

/***********************************************
 * ASTEROIDS::DRAWSCORE
 * This will call the DRAWNUMBER function from uiDraw
 * send the current hit score for them
 * to be displayed.
 **********************************************/
void Asteroids::drawScore()
{
   //DRAW the text
   drawText(Point(point.getXMin() + 150, point.getYMax() - 12),
            "SCORE - " );

   //DRAW the score
   drawNumber(Point(point.getXMin() + 220, point.getYMax() - 2),
              score);
}

/**************************************************
 * ASTEROIDS::DRAWLIVES
 * This will draw the lives on the screen (up to 4).
 *************************************************/
void Asteroids::drawLives()
{
   //DRAW the text.
   drawText(Point(point.getXMin() + 20, point.getYMax() - 12),
            "LIVES - " );

   if (((Ship*)SHIP)->getLives() <= 4)
   {
   //DRAW a ship for each life we have.
   for (int i = 1; i <= ((Ship*)SHIP)->getLives(); i++)
      drawShip(Point((point.getXMin() + 30) + (20 * (i + 1)),
               point.getYMax() - 10), -95);
   }
   else
   {
      drawNumber(Point(point.getXMin() + 100, point.getYMax() - 2),
                 ((Ship*)SHIP)->getLives());
   }
}

/***********************************************
 * ASTEROIDS::ADVANCE
 * This will increment all of the objects on
 * in the game to their next position.
 **********************************************/
void Asteroids::advance()
{
   for (std::list<Moveable*>::iterator iter = objects.begin();
        iter != objects.end(); iter++)
   {
      (*iter)->move();

      //Wrap around the screen pac-man style
      Point point = (*iter)->getPoint();
      
      if (abs(point.getX()) >= 200)
         point.setX(-point.getX());

      if (abs(point.getY()) >= 200)
         point.setY(-point.getY());
      
      (*iter)->setPoint(point);
      
      hit(iter);

      if ((*iter)->getType() == "enemy" && ((Enemy*)(*iter))->isTimeToShoot())
      {
         Point  point  = (*iter)->getPoint();
         Vector vector = (*iter)->getVect ();
         Vector tempVect;

         tempVect.setDx(-cos(PI * (*iter)->getAngle() / 180) * 10);
         tempVect.setDy(-sin(PI * (*iter)->getAngle() / 180) * 10);

         vector += tempVect;
      
         objects.push_back(new DBullet(point, tempVect));
      }
      
      if ((*iter)->getType() == "CenterEnemy" &&
          ((CenterEnemy*)(*iter))->isTimeToShoot())
      {
         Point  point  = (*iter)->getPoint();
         Vector vector = (*iter)->getVect ();
         Vector tempVect;

         tempVect.setDx(-cos(PI * (*iter)->getAngle() / 180) * 10);
         tempVect.setDy(-sin(PI * (*iter)->getAngle() / 180) * 10);

         vector = tempVect;
      
         objects.push_back(new DBullet(point, tempVect));
      }

      if (objects.size() == 1)
      {
         
         if(countDown == 0)
         {
            fCount = true;
            countDown = 20;
         }
         
         if(fCount)
            countDown--;
         
         if(countDown <= 0)
         {
            score += 50;
            level++;
            
            for(int i = 0; i <= level; i++)
            {
               objects.push_back(new LRock);
            }
         
            if (level >= 2)
            {
               objects.push_back(new Enemy);
               objects.push_back(new Enemy);
            }
            
            if (level >=3)
               objects.push_back(new CenterEnemy);
            
         }
      }
   }
}

/***********************************************
 * ASTEROIDS::HIT
 * 
 * 
 **********************************************/
void Asteroids::hit(std::list<Moveable*>::iterator & first)
{
   for (std::list<Moveable*>::iterator second = objects.begin();
        second != objects.end(); second++)
   {
      // these rocks have magical powers and can only be destroid
      // by shooting them with special bullets
      if (first != second && ((*first)->getType() != "LRock" &&
                              (*first)->getType() != "MRock" &&
                              (*first)->getType() != "SRock" &&
                              (*first)->getType() != "enemy")&&
          (*first)->getType() != (*second)->getType())
      {
         
         if ((*first)->getType() == "bullet")
         {
            
            // kills the bullet after 20 frames
            if ((*first)->getFrames() <= 0)
            {
               assert((*first)->getFrames() == 0);
               //pointer of first
               objects.erase(first);
               
               first--;
               return;
             }
         }

         // if two objects collide
         if ((*first)->hit(*second))
         {
            
            if ((*first )->getType() == "ship" ||
                (*second)->getType() == "ship"  )
            {
               ((Ship*)SHIP)->loseLife();
            }

            if ((*second)->getType() == "LRock")
            {

               Vector v;
               
               objects.push_back(new MRock((*second)->getPoint(), v));
               
               v = (Vector(random(-5,5), random(-5,5)));
               
               objects.push_back(new MRock((*second)->getPoint(), v));
               
               v = (Vector(random(-5,5), random(-5,5)));
               
               objects.push_back(new SRock((*second)->getPoint(), v));

            }
            
            if ((*second)->getType() == "MRock")
            {
               Vector v;
               
               objects.push_back(new SRock((*second)->getPoint(), v));
               
               v = (Vector(random(-5,5), random(-5,5)));

               objects.push_back(new SRock((*second)->getPoint(), v));
            }
                      

            // add the score up
            score += (*first )->getScore();
            score += (*second)->getScore();
            
            // remove from list
            objects.erase(first);
            objects.erase(second);

            // it restarts the loops, but ensures that we're
            // always at an actual peice of information
            first = objects.begin();
            second = objects.end();

            //paranoia, maybe but better safe than seg fault
            return;
         }
         
      }
   }
}

/*********************************************
 * CALLBACK
 * The main interaction loop of the engine.
 * This gets called from OpenGL.  It give us our
 * interface pointer (where we get our events from)
 * as well as a void pointer which we know is our
 * game class.
 *********************************************/
void callBack(const Interface *pUI, void *p)
{
   // we know the void pointer is our game class so
   // cast it into the game class.
   Asteroids *pAsteroids = (Asteroids *)p;

   // main interact function
   pAsteroids->interact(pUI->isUp(),    pUI->isDown(),
                        pUI->isLeft(),  pUI->isRight(),
                        pUI->isSpace(), pUI->isW(),
                        pUI->isL());

   // move all the objects
      pAsteroids->advance();

      // draw it
      pAsteroids->draw();
}

/*********************************
 * MAIN
 * initialize the drawing window, initialize
 * the game,and run it!
 *********************************/
int main(int argc, char **argv)
{
   // Start the drawing
   Interface ui(argc, argv, "STEROIDS!");

   // play the game.  Our function callback will get called periodically
   Asteroids asteroids;  
   ui.run(callBack, (void *) & asteroids);

   return 0;
}
