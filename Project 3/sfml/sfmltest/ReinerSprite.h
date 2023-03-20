#ifndef REINERSPRITE_H
#define REINERSPRITE_H
#include "MySprite.h"
#include "ItemSprite.h"
#include "StateConstants.h"
#include <iostream>
#include <stdlib.h>
// I want reiner sprites to work a bit differently than normal sprites
// mostly rpg elements will be added
class ReinerSprite :
    public MySprite
{
protected:
    sf::Texture sprite_sheet;
    sf::IntRect sprite_rect;

    bool changed_direction = false;

    float animation_speed;

    // pi
    const float pi = 3.14159;

    // move angles in radians of each of the directions
    const float move_angles[8] = {0, pi/2, pi/4, 3*pi/4, 3*pi/2, 7*pi/4, 5*pi/4, pi};

    // offset of each (walk) cycle
    int walk_offset = 8 * 96;
    int attack_offset = 11 * 96;
    int talk_offset = 9 * 96;
    int die_offset = 7 * 96;
    int hit_offset = 9 * 96;
    int stopped_offset = 96;
    int* offsets[6] = { &walk_offset, &attack_offset, &talk_offset, &die_offset, &hit_offset, &stopped_offset};
    int action_offset;

    // image size is important to keep track of
    // frames are either 96x96 or 128x128 and must be defeined explcitely
    int image_size = 96;

    // defines what frame in the cylce we are on
    int step = 0;


    int old_dir_state;
    int dir_state;
    int action_state;
    int event_state;

    // clock keeps time on animations
    sf::Clock animation_clock;

    // Sprites will contain stats about characters
    int max_health;
    int health;
    int attack;
    int base_attack;
    int base_health;
    int exp;
    int level;
    int gold;
    int attack_per_level;
    int health_per_level;
    int exp_reward;
    int gold_reward;
    
    // inventory stuffs
    // will contain all the items a sprite possess
    sf::RectangleShape inventory_backdrop;
    std::vector<ItemSprite*> inventory;
    bool show_inventory;
    sf::IntRect inventory_rect;

    // level up icon
    ItemSprite* level_up_icon;

public:
    ReinerSprite();
    ReinerSprite(std::string file_name);

    void UpdateSprite();

    void SetSpriteSheet(std::string file_name);
    bool Animate();

    // set a direction or action state
    void SetNewDir(int new_dir);
    virtual void SetNewAction(int new_action);

    int GetDirState();
    int GetActionState();

    // get or set the event state : Two events are peace and battle
    void SetEventState(int action_state);
    int GetEventState();

    // getters and setters for stats
    void SetAttack(int attack);
    int GetAttack();

    void SetHealth(int health);
    int GetHealth();

    void SetMaxHealth(int max_health);
    int GetMaxHealth();

    // will return true if player levels up, false otherwise
    bool SetExp(int exp);
    int GetExp();

    // defines behavior when a sprite levels up
    void LevelUp();

    void SetLevel(int level);
    int GetLevel();

    // attack function will take a sprite to attack
    // returns true if it kills the sprite, otherwise false
    bool Attack(ReinerSprite* attacked_sprite);

    void AddItemToInventory(ItemSprite* new_item);
    std::vector<ItemSprite*> GetInventory();

    sf::RectangleShape GetBackdrop() {
        return inventory_backdrop;
    }

    void SetShowInventory(bool choice);
    bool GetShowInventory();

    void SetGold(int some_gold);
    int GetGold();

    int GetExpReward();
    int GetGoldReward();
};

#endif