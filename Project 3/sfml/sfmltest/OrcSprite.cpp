#include "OrcSprite.h"

OrcSprite::OrcSprite() {
	// first redefine the action offsets
    walk_offset = 8 * 96;
    attack_offset = 13 * 96;
    talk_offset = 9 * 96;
    die_offset = 13 * 128;
    hit_offset = 9 * 96;
    stopped_offset = 96;

    // load the orc spritesheet
    if (!sprite_sheet.loadFromFile("spriteimages\\full_orc.png")) {
        std::cout << "sprite sheet failed to load" << std::endl;
    }
}

void OrcSprite::SetNewAction(int new_action) {
    if (action_state != new_action) {
        step = 0;
        sprite_rect.top = 0;
        action_state = new_action;
        // explicitly define behavior for orc sprite sheet
        // if atttacking, image size will be 128
        if (action_state == DYING) {
            image_size = 128;
        }
        else {
            image_size = 96;
        }
        if (action_state >= DYING) {
            sprite_rect.top += 96 * action_state;
            sprite_rect.top += 32;
        }
        else {
            sprite_rect.top += 96 * action_state;
        }
        // for animation purposes, need to set the action offset
        action_offset = *offsets[action_state];
    }
}