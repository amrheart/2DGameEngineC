#ifndef MYSPRITE_H
#define MYSPRITE_H
#include <SFML/Graphics.hpp>

class MySprite : public sf::Sprite{
protected:
	bool invisible;
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
	int dx;
	int dy;
	int ddx;
	int ddy;
	int gravity;
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