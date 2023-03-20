#include "ItemSprite.h"

ItemSprite::ItemSprite(std::string name, float value, int row, int column) {
	this->name = name;
	this->value = value;
	
	if (!sprite_sheet.loadFromFile("spriteimages\\item_icons.png")) {
		std::cout << "sprite sheet failed to load" << std::endl;
	}
	sprite_rect.top = 0;
	sprite_rect.left = 0;
	sprite_rect.height = 32;
	sprite_rect.width = 32;
	sprite_rect.top += row * 32;
	sprite_rect.left += column * 32;

	this->setTexture(sprite_sheet);
	this->setTextureRect(sprite_rect);
}

int ItemSprite::Use() {
	return 10;
}