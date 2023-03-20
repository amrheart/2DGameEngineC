#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
#include "MySprite.h"
#include "PlayerSprite.h"
#include "ReinerSprite.h"
#include "SideViewSprite.h"
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
	std::vector<ReinerSprite*> list_of_sprites;
	MySprite* background;
	sf::IntRect background_tile;
	MySprite* hud;

	sf::RenderWindow* window;

	// stats panel display
		// stats panel
	// will contain stats of character and be displayed at all times
	sf::RectangleShape stats_backdrop;
	sf::Text player_health;
	sf::Text player_damage;
	sf::Text player_defense;
	sf::Text player_gold;
	sf::IntRect stats_rect;

	// try adding some text
	sf::Font font;

	// define the scenes that border this one
	Scene* left_bound;
	Scene* right_bound;
	Scene* top_bound;
	Scene* bottom_bound;
	
public:
	Scene(int width, int height, int FPS, sf::RenderWindow* window);

	void AddBackground(MySprite* background);

	void AddHud(MySprite* HUD);

	// updates each sprite, will handle out of bounds behavior
	void UpdateSprites();

	// draw all the sprites in the sprite list to the 1st buffer
	void DrawSprites();

	// displays the frame and also
	// will wait until the entire frame has finished : this is based on FPS
	void DisplayFrame();

	// add sprite to the list of sprites
	void AddSprite(ReinerSprite* new_sprite);

	// checks the x and y of a sprite and returns true if its in the screen and false if outside
	bool CheckBounds(MySprite* sprite_to_check);

	// utility function so that i can check only the players bounds
	bool CheckPlayerBounds(ReinerSprite* player);

	// goes through the sprite list and checks if any collisions occur
	// returns the sprite that collides with the player
	ReinerSprite* CheckCollisions();

	// Bounces the sprite off the edge of the screen
	void Bounce(MySprite* sprite_to_bounce);

	// teleports the sprite to the opposite side of the scree
	void Teleport(MySprite* sprite_to_tp);

	// reverse the direction of the sprite to the opposite direction
	void ReverseDirection(ReinerSprite* sprite_to_reverse);

	int GetHeight();
	int GetWidth();
};

#endif