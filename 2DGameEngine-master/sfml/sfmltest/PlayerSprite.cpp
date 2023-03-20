#include "PlayerSprite.h"
#include <iostream>

void PlayerSprite::UpdateSprite() {
	// check to make sure min speed is not reached
	if (this->speed < GetMinSpeed()) {
		this->speed = GetMinSpeed();
	}
	// check to make sure max speed is not reached
	if (this->speed > GetMaxSpeed()) {
		this->speed = GetMaxSpeed();
	}

	// set the rotation of the image
	setRotation(this->image_angle * (180 / 3.14159));

	// get current x and y
	sf::Vector2f cur_pos = getPosition();

	// set the new x and y based on move angle and speed
	this->x = cur_pos.x + cos(move_angle) * speed;
	this->y = cur_pos.y - sin(move_angle) * speed;

	setPosition(this->x, this->y);
}