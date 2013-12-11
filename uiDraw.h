#ifndef UI_DRAW_H
#define UI_DRAW_H

#include <string>     // To display text on the screen
#include <cmath>      // for M_PI, sin() and cos()
#include "point.h"    // Where things are drawn
using std::string;

/************************************************************************
 * DRAW DIGIT
 * Draw a single digit in the old school line drawing style.  The
 * size of the glyph is 8x11 or x+(0..7), y+(0..10)
 *************************************************************************/
void drawDigit(const Point & topLeft, char digit);

/*************************************************************************
 * DRAW NUMBER
 * Display an positive integer on the screen using the 7-segment method
 *************************************************************************/
void drawNumber(const Point & topLeft, unsigned int number);

/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 ************************************************************************/
void drawText(const Point & topLeft, const char * text);

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *************************************************************************/
void rotate(Point & point, const Point & origin, int rotation);

/************************************************************************
 * DRAW RECTANGLE
 * Draw a rectangle on the screen centered on a given point (center) of
 * a given size (width, height), and at a given orientation (rotation)
 * measured in degrees (0 - 360)
 *************************************************************************/
void drawRect(const Point & center, char width, char height, int rotation);

/************************************************************************
 * DRAW CIRCLE
 * Draw a circle from a given location (center) of a given size (radius).
 *************************************************************************/
void drawCircle(const Point & center, char radius, int points, int rotation);

/*****************************************************************************
 *DRAW FULL CIRCLE
 * Draw a filled, solid circle. Similar to DRAW CIRCLE, only filled.
 **************************************************************************/
void drawFullCircle(const Point & center, char radius,
                    int points, int rotation);

/************************************************************************
 * DRAW BLUE CIRCLE
 * Draw a blue circle from a given location (center) of a given size (radius).
 *  INPUT   center   Center of the circle
 *          radius   Size of the circle
 *          points   How many points will we draw it.  Larger the number,
 *                   the more line segments we will use
 *          rotation True circles are rotation independent.  However, if you
 *                   are drawing a 3-sided circle (triangle), this matters!
 *************************************************************************/
void drawBlueCircle(const Point & center, int radius,
                    int points, int rotation);

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void drawLine(const Point & begin, const Point & end, int x, int y, int z);

/************************************************************************
 * DRAW DOT
 * Draw a single point on the screen, 2 pixels by 2 pixels
 *************************************************************************/
void drawDot(const Point & point);

/*************************************************************
 * DRAW LARGE ROCK
 * This will draw a large red custom asteroid.
 *************************************************************/
void drawLRock(Point & center, char radius);

/*************************************************************
 * DRAW MEDIUM ROCK
 * This will draw a medium orange custom asteroid.
 *************************************************************/
void drawMRock(Point & center, char radius);

/*************************************************************
 * DRAW SMALL ROCK
 * This will draw a small white custom asteroid.
 *************************************************************/
void drawSRock(Point & center, char radius);

/*************************************************************
 * DRAW ENEMY
 * This will draw a small green enemy spaceship.
 *************************************************************/
void drawEnemy(Point & center, char radius);

/************************************************************************
 * DRAW RED SHIP
 * Draw a spaceship on the screen
 *  INPUT point   The position of the ship
 *        angle   Which direction it is ponted
 *************************************************************************/
void drawRedShip(const Point & center, int rotation);

/************************************************************************
 * DRAW Ship
 * Draw the spaceship on the screen
 *************************************************************************/
void drawShip(const Point & point, int rotation);

/******************************************************************
 * RANDOM
 * This function generates a random number.  The user specifies
 * The parameters 
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int    random(int    min, int    max);
double random(double min, double max);


#endif // UI_DRAW_H
