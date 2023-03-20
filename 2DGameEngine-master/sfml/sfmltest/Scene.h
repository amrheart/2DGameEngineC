#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
#include "MySprite.h"
#include "PlayerSprite.h"
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <time.h>
#include <chrono>


//scene class will organize sprites
// contains a pointer to the render window
class Scene{
private:
	int height;
	int width;
	int FPS;
	float frame_duration;
	std::vector<MySprite*> list_of_sprites;
	MySprite* background;

	sf::RenderWindow* window;
	
public:
	Scene(int width, int height, int FPS, sf::RenderWindow* window);

	// updates each sprite, will handle out of bounds behavior
	void UpdateSprites();

	// draw all the sprites in the sprite list to the 1st buffer
	void DrawSprites();

	// displays the frame and also
	// will wait until the entire frame has finished : this is based on FPS
	void DisplayFrame();

	// add sprite to the list of sprites
	void AddSprite(MySprite* new_sprite);

	// checks the x and y of a sprite and returns true if its in the screen and false if outside
	bool CheckBounds(MySprite* sprite_to_check);

	// goes through the sprite list and checks if any collisions occur
	// returns index of sprite that caused collision with player
	void CheckCollisions();

	// Bounces the sprite off the edge of the screen
	void Bounce(MySprite* sprite_to_bounce);

	// teleports the sprite to the opposite side of the scree
	void Teleport(MySprite* sprite_to_tp);
};

#endif