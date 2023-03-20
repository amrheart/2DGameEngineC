# 2DGameEngine
First Take on a 2D Game Engine

------ Background ------
This is my version of a 2D top down game engine using SFML in C++. I have never used SFML but am well versed in C++, so I thought it would be a fun challenge to make my engine using SFML. I have implemented many aspects of a top down game engine. When boundry checking, there are two types of behaviors I have programmed in. 1. bounce off the edge of the screen, 2. Translate to the other side of the screen and continue in the same direction. The test game I made is very simple and shows off the mechanics of my engine. There isnt much of an objective, but you fly around as a plane.

------ Dependencies ------
The code for this game was written in C++ using visual studio code 2019 and the SFML library. An SFML and C++ environment is required to use this engines files and run the test game I made. The file that is to be run is the Source.cpp. This is the test game I made. Scene.h and Sprite.h are the Scene and Sprite classes respectively. The Scene contains a window object that it manipulates and the Sprite extends the SFML sprite class. Ignore tempstorage.cpp as its an earlier implementation. The files that you will need are locate in sfml//sfmltest.
Note: I'm not entirely sure how SFML works with running files. As in, I don't know if i need to statically link libraries for it to work independently. For this reason, I've provided a video demo of my game as well as all the files.

------- My Files -------
List of files that I made (non SFML)
-Scene.h, Scene.cpp
-Sprite.h, Sprite.cpp
-Source.cpp

------- Image sources -------
plane -> Justin from cartoonsmart.com
sky -> cutewallpaper.org
