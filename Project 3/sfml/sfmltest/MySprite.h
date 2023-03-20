#ifndef MYSPRITE_H
#define MYSPRITE_H
#include <SFML/Graphics.hpp>

class MySprite : public sf::Sprite{
protected:
	bool invisible;
	bool collidable;
	int height;
	int width;
	float move_angle;
	float image_angle;
	float x;
	float y;
	float max_speed;
	float min_speed;

	// for use with top down games
	float speed;
	float acceleration;

	// for use with side view games (not implemented)
	float dx;
	float dy;
	int ddx;
	int ddy;
	float gravity;

	// keeps track of the actual physical time of the sprite; allows fps to be seperate
	sf::Clock motion_time;

public:
	MySprite();
	MySprite(int height, int width, float x, float y);

	// used to calculate transformations
	void ChangeSpeed(float change);
	void ChangeMoveAngle(float change);
	void ChangeImageAngle(float change);

	// simply updates the sprites position based on sprites current state
	// to be called every frame
	virtual void UpdateSprite();

	// Checks if the sprite collides with the one passed to it
	// sfml has built in methods to help with this, so not much code
	bool CollidesWith(MySprite* check_collide);

	// tells the scene to not draw the sprite
	void SetInvisible();
	void SetVisible();
	bool GetInvisible();

	// pass 0 for no collide and 1 for collide
	void SetCollidable(bool choice);
	bool GetCollidable();

	// get and set various attributes directly
	float GetMoveAngle();
	void SetMoveAngle(float new_angle);
	float GetImageAngle();
	void SetImageAngle(float new_angle);
	float GetAcceleration();
	void SetAcceleration(float new_acceleration);
	float GetSpeed();
	void SetSpeed(float new_speed);
	float GetMinSpeed();
	void SetMinSpeed(float minspeed);
	float GetMaxSpeed();
	void SetMaxSpeed(float maxspeed);
	void SetXY(int x, int y);
};

#endif