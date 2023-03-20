#include "MushyManSprite.h"

MushyManSprite::MushyManSprite() {
    attack = 4;

    // since Reiner Sprite was designed with mushyman as the default, no need to set everything
    // only need to load mushy man sprite sheet
    if (!sprite_sheet.loadFromFile("spriteimages\\full_mushy_man.png")) {
        std::cout << "sprite sheet failed to load" << std::endl;
    }
}