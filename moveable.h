/**************************************************
 * MOVABLES header file
 ***************************************************************/
#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "point.h"
#include "vector.h"


/***************************************************************
 *
 *
 **************************************************************/
class Moveable
{
  public:
  Moveable(string type, int radius, int score)
     : point(0,0), vector(0,0), type(type), radius(radius), score(score) {};
  Moveable(string type, Point point, int radius, int score)
     : type(type), point(point), radius(radius), score(score)            {};
  Moveable(string type, Point point, Vector vector, int radius, int score)
     : type(type), point(point), vector(vector), radius(radius),
      score(score)  {};
   
   bool hit(Moveable* rhs)
   {
      if ((std::abs(point.getX() - rhs->point.getX()) <= getRadius()       &&
           std::abs(point.getY() - rhs->point.getY()) <= getRadius())      ||
          (std::abs(point.getX() - rhs->point.getX()) <= rhs->getRadius()  &&
           std::abs(point.getY() - rhs->point.getY()) <= rhs->getRadius()  ))
         return true;
      else
         return false;
       
   };
   virtual void  draw     () = 0;
   virtual void  move     () = 0;
   virtual int   getFrames()  {};
   virtual float getAngle ()  {};

   // Getters
   string getType  () const { return type;   };
   Vector getVect  () const { return vector; };
   Point  getPoint () const { return point;  };
   int    getRadius() const { return radius; };
   int    getScore () const { return score;  };


   // Setter
   virtual float setAngle(float change) {};
   
   void  setPoint(Point p)
   {
      point.setX(p.getX());
      point.setY(p.getY());
   };
           
   void  addPoint(int dx, int dy)
   {
      point.setX(point.getX() + dx);
      point.setY(point.getY() + dy);
   };
   
   void  setVect(Vector v)
   {
      vector.setDx(vector.getDx() + v.getDx());
      vector.setDy(vector.getDy() + v.getDy());
   };

  protected:
   string type;
   Point  point;
   Vector vector;
   bool   fDead;
   int    radius;
   int    score;
};

class Shootable : public Moveable
{
  public:
  Shootable(string type, int radius, int score)
     : Moveable(type, radius, score)                {};
  Shootable(string type, Point point, int radius, int score)
     : Moveable(type, point, radius, score)         {};
  Shootable(string type, Point point, Vector vector, int radius, int score)
     : Moveable(type, point, vector, radius, score) {};

   virtual void draw() {};
};

class Bullet : public Moveable
{
  public:
   // constructor
  Bullet(Point point, Vector vector, string type, int life)
     : Moveable(type, point, vector, 1, 0), framesToLive(life)
   {
      Vector v = (vector * 2);
      addPoint(v.getDx(), v.getDy());
   };
   
   void move()
   {
      addPoint(vector.getDx(), vector.getDy());
      framesToLive--;
   };

   void increment() {}; // ++        
   void draw     () { drawCircle(point,2,20,0); };
   int  getFrames() { return framesToLive;      }; 
   
  private:
   int framesToLive;
};

class DBullet : public Bullet
{
  public:
  DBullet(Point point, Vector vector)
     : Bullet(point, vector, "bullet", 22) {};
};

class UPBullet : public Bullet
{
  public:
  UPBullet(Point point, Vector vector2, float angle)
     : Bullet(point, vector2, "bullet", 22)
   {

      angle += 50;
      vector.setDx(-cos(3.1415 * angle / 180) * 10);
      vector.setDy(-sin(3.1415 * angle / 180) * 10);
   };
   void move()
   {
      Bullet::move();
//      chase();
   };
   void chase()
   {
      vector += Vector(1, 1);
   };

  private:
   float angle;
};

class DNBullet : public Bullet
{
  public:
  DNBullet(Point point, Vector vector2, float angle)
     : Bullet(point, vector2, "bullet", 22)//, angle(angle)
   {
      angle -= 50;
      vector.setDx(-cos(3.1415 * angle / 180) * 10);
      vector.setDy(-sin(3.1415 * angle / 180) * 10);
   };
   void move()
   {
      Bullet::move();
//      chase();
   };
   void chase()
   {
      vector += Vector(-1, -1);
   };
  private:
   float angle;
};

class Ship : public Shootable
{
  public:
  Ship() : Shootable("ship", Point(0,0), Vector(0,0), 4, 0), angle(135) {};
   
   void move()
   {
      addPoint(vector.getDx(), vector.getDy());
   };
   void draw()                    {drawShip(point, angle);};
   // don't make getAngle() const!!! it messes up the angle
   // for bullet fire, why i don't know, just that it does
   void loseLife()              { lives--;                };
   void addLife ()              { lives++;                };
   static int getLives()        { return lives;           };
   float getAngle()             { return angle;           };
   int getX()                   { return point.getX();    };
   int getY()                   { return point.getY();    };
   float setAngle(float change) { return angle += change; };
  private:
   float angle;
   static int lives;
};


class Enemy : public Shootable
{
  public:
  Enemy() : Shootable("enemy", Point(random(-200,200), -150),
                      Vector(2,0), 7, 20), angle(-91),
      timeToShoot(random(10,20)) {};
   
   void move()
   {
      addPoint(vector.getDx(), vector.getDy());
      timeToShoot--;
   };
   
   void draw() {drawEnemy(point, radius);};
   bool isTimeToShoot()
   {
      if (timeToShoot <= 0)
      {
         timeToShoot = random(20,30);
         return true;
      }
      else
         return false;
      
   };
   float getAngle()             { return angle;           };

   
  private:
   float angle;
   int timeToShoot;
};

class CenterEnemy : public Shootable
{
  public:
  CenterEnemy()
     : Shootable("CenterEnemy", Point(random(-200,-100), 0),
                 Vector(random(-3,3),random(-3,3)), 4, 20),
      angle(0), timeToShoot(random(10,20))
   {
      angle = calcAngle(vector);
   };
   
   void move()
   {
      addPoint(vector.getDx(), vector.getDy());
      timeToShoot--;
      reorient();
   };
   
   void draw() {drawRedShip(point, angle);};
   bool isTimeToShoot()
   {
      if (timeToShoot <= 0)
      {
         timeToShoot = random(20,30);
         return true;
      }
      else
         return false;
      
   };

   void reorient()
   {
      Vector v;
      v.setDx((point.getX()));
      v.setDy((point.getY()));
      angle = calcAngle(v);
   };

   float calcAngle(Vector & v)
   {
      float theta;
      if ((point.getY() >= 0  &&
           point.getX() >= 0) || // 1st quadrent
          (point.getY() <  0  &&
           point.getX() >= 0)  ) // 4th
      {
         theta = (v.getDy() / v.getDx());
         theta = atan(theta);
         theta *= 180;
         theta /= 3.1415;
         return theta;
      }
      else if (point.getY() >= 0 &&
               point.getX() <  0  ) // 2nd
      {
         theta = (v.getDy() / -v.getDx());
         theta = atan(theta);
         theta *= 180;
         theta /= 3.1415;
         theta = 180 - theta;
         return theta;
      }

      else if(point.getY() <  0 &&
              point.getX() <  0  ) // 3rd
      {
         theta = (v.getDy() / -v.getDx());
         theta = atan(theta);
         theta *= 180;
         theta /= 3.1415;
         theta = (540 - theta);
         return theta;
      }
   };
      
   float getAngle()             { return angle;           };

   
  private:
   Point destination;
   Moveable* ship;
   float angle;
   int timeToShoot;
};


class SmartEnemy : public Shootable
{
  public:
  SmartEnemy()
     : Shootable("enemy", Point(random(-200,-100), 0),
                 Vector(random(-3,3),random(-3,3)), 4, 20),
      angle(0), timeToShoot(random(10,20))
   {
      angle = calcAngle(vector);
   };
   
  SmartEnemy(Moveable*  ship)
     : Shootable("enemy", Point(random(-200,-100), 0),
                 Vector(random(-3,3),random(-3,3)), 4, 20),
      angle(0), timeToShoot(random(10,20)), ship(ship)
   {
      destination = ship->getPoint();
      angle = calcAngle(vector);
   };
   
   void move()
   {
      addPoint(vector.getDx(), vector.getDy());
      timeToShoot--;
      reorient();
   };
   
   void draw() {drawShip(point, angle);};
   bool isTimeToShoot()
   {
      if (timeToShoot <= 0)
      {
         timeToShoot = random(20,30);
         return true;
      }
      else
         return false;
      
   };

   void reorient()
   {
      destination = ship->getPoint();
      Vector v;
      v.setDx(std::abs(point.getX() - ((Ship*)ship)->getX()));
      v.setDy(std::abs(point.getY() - ((Ship*)ship)->getY()));
      angle = calcAngle(v);
   };

   float calcAngle(Vector & v)
   {
      float theta;

      
      
      
      if ((point.getY() >= 0  &&
           point.getX() >= 0) || // 1st quadrent
          (point.getY() <  0  &&
           point.getX() >= 0)  ) // 4th
      {
         theta = (v.getDy() / v.getDx());
         theta = atan(theta);
         theta *= 180;
         theta /= 3.1415;
         return theta;
      }
      else if (point.getY() >= 0 &&
               point.getX() <  0  ) // 2nd
      {
         theta = (v.getDy() / -v.getDx());
         theta = atan(theta);
         theta *= 180;
         theta /= 3.1415;
         theta = 180 - theta;
         return theta;
      }

      else if(point.getY() <  0 &&
              point.getX() <  0  ) // 3rd
      {
         theta = (v.getDy() / -v.getDx());
         theta = atan(theta);
         theta *= 180;
         theta /= 3.1415;
         theta = (540 - theta);
         return theta;
      }

   };
      
   float getAngle()             { return angle;           };

   
  private:
   Point destination;
   Moveable* ship;
   float angle;
   int timeToShoot;
};
#endif //MOVEABLES_H
