#include "ReinerSprite.h"

ReinerSprite::ReinerSprite() {
    max_health = 20;
    health = 20;
    attack = 10;
    base_attack = 10;
    base_health = 20;
    exp = 0;
    level = 0;
    gold = 0;
    attack_per_level = 2;
    health_per_level = 2;
    exp_reward = 10;
    gold_reward = 5;

    animation_speed = 0.1;

    sprite_rect.left = 0;
    sprite_rect.top = 0;
    sprite_rect.height = 96;
    sprite_rect.width = 96;

    inventory_rect.left = 0;
    inventory_rect.top = 500;
    inventory_rect.height = 32;
    inventory_rect.width = 32;

    sf::Vector2f backdrop_size(128, 200);
    inventory_backdrop.setSize(backdrop_size);
    inventory_backdrop.setFillColor(sf::Color::Black);
    inventory_backdrop.setPosition(inventory_rect.left, inventory_rect.top);

    action_state = 0;
    dir_state = 0;
    old_dir_state = 0;

    level_up_icon = new ItemSprite("icon", 0, 2, 1);
    level_up_icon->setPosition(x + 32, y - 32);

    event_state = 0;

    action_offset = *offsets[WALKING];

    show_inventory = false;


    // load a mushyman by default
    if (!sprite_sheet.loadFromFile("spriteimages\\mushyman_walking_transparent.png")) {
        std::cout << "sprite sheet failed to load" << std::endl;
    }

    this->setTexture(sprite_sheet);
    this->setTextureRect(sprite_rect);
}

ReinerSprite::ReinerSprite(std::string file_name) {
    sprite_rect.left = 0;
    sprite_rect.top = 0;
    sprite_rect.height = 96;
    sprite_rect.width = 96;

    animation_speed = 0.8;

    action_state = 0;
    dir_state = 0;
    old_dir_state = 0;

    health = 20;
    attack = 10;
    exp = 0;

    event_state = 0;

    action_offset = *offsets[WALKING];

    show_inventory = false;

    if (!sprite_sheet.loadFromFile("spriteimages\\" + file_name)) {
        std::cout << "sprite sheet failed to load" << std::endl;
    }

    this->setTexture(sprite_sheet);
    this->setTextureRect(sprite_rect);
}

void ReinerSprite::UpdateSprite() {

    // movement stuff
    // get current x and y
    sf::Vector2f cur_pos = getPosition();

    // set the new x and y based on move angle and speed
    this->x = cur_pos.x + cos(move_angle) * speed;
    this->y = cur_pos.y - sin(move_angle) * speed;

    // for testing
    /*std::cout << "cur x" << x << std::endl;
    std::cout << "cur y" << y << std::endl;*/

    setPosition(this->x, this->y);
    //this->Animate();
}

void ReinerSprite::SetSpriteSheet(std::string file_name) {
    if (!sprite_sheet.loadFromFile("spriteimages\\" + file_name)) {
        std::cout << "sprite sheet failed to load" << std::endl;
    }
    this->setTexture(sprite_sheet);
}

// animates the sprite based on its state
bool ReinerSprite::Animate() {
    bool test = true;
    bool only_once = true;
    sprite_rect.left = action_offset * dir_state + (step * image_size);

    // in the case where the action has only a single frame for each direction(ie stopped action)
    if (action_offset == 96) {
        step = 0;
        test = false;
    }
    // in the case where we've reached the end of a directional sequence, reset the sequence
    else if (sprite_rect.left == action_offset * (dir_state + 1) - image_size) {
        sprite_rect.left = action_offset * dir_state;
        std::cout << sprite_rect.left << std::endl;
        std::cout << "Top rect" << sprite_rect.top << std::endl;
        step = 0;
        if (!(only_once)) {
            this->setTextureRect(sprite_rect);
        }
        return false;
    }
    // keeps time of the animation
    else if (animation_clock.getElapsedTime().asSeconds() > animation_speed) {
        sprite_rect.left += image_size;
        animation_clock.restart();
        step += 1;
        std::cout << sprite_rect.left << std::endl;
    }
    this->setTextureRect(sprite_rect);
    return test;
}

void ReinerSprite::SetNewDir(int new_dir) {
    // if they're already the same, dont do anything
    if (dir_state != new_dir) {
        step = 0;
        dir_state = new_dir;
        move_angle = move_angles[dir_state];
    }
}

void ReinerSprite::SetNewAction(int new_action) {
    if (action_state != new_action) {
        step = 0;
        sprite_rect.top = 0;
        action_state = new_action;
        sprite_rect.top += 96 * action_state;
        // for animation purposes, need to set the action offset
        action_offset = *offsets[action_state];
    }
}

int ReinerSprite::GetDirState() {
    return dir_state;
}
int ReinerSprite::GetActionState() {
    return action_state;
}

// get or set the action state
void ReinerSprite::SetEventState(int event_state) {
    this->event_state = event_state;
}
int ReinerSprite::GetEventState() {
    return event_state;
}

// getters and setters for stats
void ReinerSprite::SetAttack(int attack) {
    this->attack = attack;
}
int ReinerSprite::GetAttack() {
    return attack;
}

void ReinerSprite::SetHealth(int health) {
    this->health = health;
}
int ReinerSprite::GetHealth() {
    return health;
}

void ReinerSprite::SetMaxHealth(int max_health) {
    this->max_health = max_health;
}
int ReinerSprite::GetMaxHealth() {
    return max_health;
}

bool ReinerSprite::SetExp(int exp) {
    bool level_up = false;
    this->exp += exp;
    if (this->exp >= 20) {
        SetLevel(this->level + 1);
        this->exp = 0;
        level_up = true;
    }
    return level_up;
}
int ReinerSprite::GetExp() {
    return exp;
}

void ReinerSprite::SetLevel(int level) {
    this->level = level;
    SetAttack(this->base_attack + level * attack_per_level);
    SetHealth(this->base_health + level * health_per_level);
}
int ReinerSprite::GetLevel() {
    return level;
}

bool ReinerSprite::Attack(ReinerSprite* attacked_sprite) {
    bool killed = true;
    int this_attack = GetAttack();
    int enemy_health = attacked_sprite->GetHealth();
    // chance to crit
    srand(time(NULL));
    if ((rand() % 10) > 8) {
        this_attack *= 2;
    }
    int enemy_new_health = enemy_health - this_attack;
    attacked_sprite->SetHealth(enemy_new_health);
    if (attacked_sprite->GetHealth() > 0) {
        killed = false;
    }
    return killed;
}

void ReinerSprite::AddItemToInventory(ItemSprite* new_item) {
    new_item->setPosition(inventory_rect.left, inventory_rect.top);
    inventory.push_back(new_item);
}

std::vector<ItemSprite*> ReinerSprite::GetInventory() {
    return inventory;
}

void ReinerSprite::SetShowInventory(bool choice) {
    show_inventory = choice;
}
bool ReinerSprite::GetShowInventory() {
    return show_inventory;
}

void ReinerSprite::SetGold(int some_gold) {
    gold = some_gold;
}
int ReinerSprite::GetGold() {
    return gold;
}

int ReinerSprite::GetExpReward() {
    return exp_reward;
}
int ReinerSprite::GetGoldReward() {
    return gold_reward;
}