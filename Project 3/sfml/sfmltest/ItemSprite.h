#ifndef ITEMSPRITE_H
#define ITEMSPRITE_H
#include "MySprite.h"
#include <iostream>
class ItemSprite :
    public MySprite
{
protected:
    std::string name;
    float value;

    sf::Texture sprite_sheet;
    sf::IntRect sprite_rect;

public:
    ItemSprite(std::string name, float value, int row, int column);
    int Use();
};

#endif