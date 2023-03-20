#include "SideViewSprite.h"
#include <iostream>

SideViewSprite::SideViewSprite() {
	dy = 0;
}

void SideViewSprite::UpdateSprite() {
	sf::Time t = motion_time.getElapsedTime();
	int cur_time = t.asMilliseconds();
	// game will update every 15 milliseconds; about 64 tick
	if (cur_time >= 200){
		dy += gravity;
		motion_time.restart();
	}

	y += dy;
	setPosition(x, y);
}