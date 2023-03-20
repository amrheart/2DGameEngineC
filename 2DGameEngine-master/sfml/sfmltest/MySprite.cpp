#include "MySprite.h"
#include <iostream>

MySprite::MySprite() {
	this->height = 100;
	this->width = 100;
	this->x = 0.0;
	this->y = 0.0;
	this->speed = 0.0;
	this->move_angle = 0.0;
	this->image_angle = 0.0;
	this->gravity = 0.0;
	this->invisible = false;
}

MySprite::MySprite(int height, int width, float x, float y) {
	this->height = height;
	this->width = width;
	this->x = 0.0;
	this->y = 0.0;
	this->dx = 0;
	this->dy = 0;
	this->ddx = 0;
	this->ddy = 0;
	this->speed = 0;
	this->max_speed = 1;
	this->move_angle = 0;
	this->image_angle = 0;
	this->gravity = 0;
	this->acceleration = 0;
	this->min_speed = 0;
	this->invisible = false;
}

void MySprite::ChangeSpeed(float change) {
	this->speed += change;
}

void MySprite::ChangeMoveAngle(float change) {
	this->move_angle += change;
}

void MySprite::ChangeImageAngle(float change) {
	this->image_angle += change;
}

void MySprite::UpdateSprite() {
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

bool MySprite::CollidesWith(MySprite* check_collide) {
	bool collides = false;
	sf::FloatRect this_rect = this->getGlobalBounds();
	sf::FloatRect other_rect = check_collide->getGlobalBounds();
	if (this_rect.intersects(other_rect)) {
		collides = true;
		std::cout << "Collided" << std::endl;
	}
	return collides;
}

void MySprite::SetInvisible() {
	this->invisible = true;
}

void MySprite::SetVisible() {
	this->invisible = false;
}

bool MySprite::GetInvisible() {
	return this->invisible;
}

float MySprite::GetMoveAngle() {
	return move_angle;
}

void MySprite::SetMoveAngle(float new_angle) {
	this->move_angle = new_angle;
}

float MySprite::GetImageAngle() {
	return this->image_angle;
}
void MySprite::SetImageAngle(float new_angle) {
	this->image_angle = new_angle;
	this->setRotation(this->image_angle * 180/3.14159);
}

float MySprite::GetAcceleration() {
	return this->acceleration;
}

void MySprite::SetAcceleration(float new_acceleration) {
	this->acceleration = new_acceleration;
}

float MySprite::GetSpeed() {
	return this->speed;
}

void MySprite::SetSpeed(float new_speed) {
	this->speed = new_speed;
}

float MySprite::GetMinSpeed() {
	return min_speed;
}
void MySprite::SetMinSpeed(float minspeed) {
	this->min_speed = minspeed;
}

float MySprite::GetMaxSpeed() {
	return max_speed;
}
void MySprite::SetMaxSpeed(float maxspeed) {
	this->max_speed = maxspeed;
}

void MySprite::SetXY(int x, int y) {
	this->x = x;
	this->y = y;
}