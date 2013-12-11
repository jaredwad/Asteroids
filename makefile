###############################################################
# Program:
#     Project 04, Asteroids!
#     Brother Helfrich, CS165
# Author:
#     Adam Harris
#     Jared Wadsworth
# Summary:
#     Asteroids is a beloved classic video game. In following the
#     game developers tradition, we have created our own version of the game
#     in an attempt to win awards at E3 2013. The game uses different class
#     objects (ships, rocks, bullets, and enemies) that interact with each
#     other. The player controlling the ship is to shoot and destroy all other
#     objects on the screen.
#     EXTRA CREDIT:
#         -Colors
#         -Custom asteroids shapes (rotating becomes very difficult though)
#         -Enemies
#            -Dumb Enemies  (green)
#            -Smart Enemies (red, ship-like)
#         -Lives
#         -Shotgun (by pressing W)
#         -Buying Lives (by pressing L)
#         -Leveling system
#         -Scoring system
#              -Large Asteroids  = 20   pts    
#              -Medium Asteroids = 15   pts
#              -Small Asteroids  = 10   pts
#              -Enemy Ships      = 20   pts
#              -New Level        = 50   pts
#              -Firing Shotgun   = -3   pts
#              -Losing a Life    = -50  pts
#              -Buying a Life    = -200 pts
#
#     Estimated:  12.0 hrs
#     Actual:     20.0 hrs
#       The most difficult parts was angles and hit detection. Even
#       till the end, we never figued out vector addition. The game works
#       just fine without it though. 
###############################################################

###############################################################
# Programs:
#    skeet:         The playable game
#    uiTest:       Simple driver program for the drawing interface
###############################################################
asteroids : asteroids.o uiInteract.o uiDraw.o point.o
	g++ -g -o asteroids $^ -lglut -lGLU
	tar -cf asteroids.tar *.cpp *.h makefile

uiTest : uiTest.o uiDraw.o uiInteract.o point.o
	g++ -o uiTest $^ -lglut -lGLU

###############################################################
# Individual files
#    uiDraw.o      Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o  Handles input events
#    point.o       The position on the screen
#    uiTest.o      Driver program for uiDraw and uiTest
#    asteroids.o   Game of the year 2012
###############################################################
uiInteract.o : uiInteract.cpp uiInteract.h point.h
	g++ -c uiInteract.cpp

uiDraw.o : uiDraw.cpp uiDraw.h point.h
	g++ -c uiDraw.cpp

point.o : point.cpp point.h
	g++ -c point.cpp

uiTest.o : uiTest.cpp point.h uiDraw.h uiInteract.h
	g++ -c uiTest.cpp

asteroids.o : asteroids.cpp *.h
	g++ -c asteroids.cpp


###############################################################
# General rules
###############################################################
clean :
	rm uiTest asteroids *.o *.tar *~ *# *.gch

all :  uiTest asteroids