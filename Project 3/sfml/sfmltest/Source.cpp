#include "Scene.h"
#include "OrcSprite.h"
#include "MushyManSprite.h"
#include "ItemSprite.h"
#include "StateConstants.h"
#include <chrono>
#include <thread>

// main game file
// will organize all game mechanics
// will determine what to do when player is in battle, control shcemes, etc.

bool Battle(ReinerSprite* player, ReinerSprite* enemy, Scene battle_scene, sf::RenderWindow *window) {
    // turn states
    const int PLAYER = 0;
    const int ENEMY = 1;
    int turn = PLAYER;
    std::string winner = "Empty";

    // add the sprites to the scene
    player->SetXY(100, 600);
    enemy->SetXY(600, 100);
    player->setPosition(400 - 48, battle_scene.GetHeight()/2 + battle_scene.GetHeight()/15 - 48);
    enemy->setPosition(500 - 48, battle_scene.GetHeight()/2 - battle_scene.GetHeight()/15 - 48);
    player->SetSpeed(0);
    enemy->SetSpeed(0);
    player->SetNewDir(2);
    enemy->SetNewDir(6);
    player->SetNewAction(5);
    enemy->SetNewAction(5);

    battle_scene.AddSprite(player); 
    battle_scene.AddSprite(enemy);

    bool battle_not_over = true;
    bool keep_going = true;
    bool outcome = true;
    bool key_held_down = false;
    // fight sequence will loop until a winner is determined
    while (keep_going) {
        if (battle_not_over) {
            // players turn
            if (turn == PLAYER) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    // attack and if attack kills, end battle
                    player->SetNewAction(1);
                    while (player->Animate()) {
                        battle_scene.DisplayFrame();
                    }
                    enemy->SetNewAction(4);
                    while (enemy->Animate()) {
                        battle_scene.DisplayFrame();
                    }
                    if (player->Attack(enemy)) {
                        battle_not_over = false;
                        winner = "PLAYER";
                    }
                    player->SetNewAction(5);
                    enemy->SetNewAction(5);
                    std::cout << "Player attacked" << std::endl;
                    turn = ENEMY;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                    if (key_held_down == false) {
                        if (player->GetShowInventory()) {
                            player->SetShowInventory(false);
                        }
                        else {
                            player->SetShowInventory(true);
                        }
                    }
                    key_held_down = true;
                }
                else {
                    key_held_down = false;
                }
            }
            // Enemies turn
            else if (turn == ENEMY) {
                enemy->SetNewAction(1);
                while (enemy->Animate()) {
                    battle_scene.DisplayFrame();
                }
                player->SetNewAction(4);
                while (player->Animate()) {
                    battle_scene.DisplayFrame();
                }
                if (enemy->Attack(player)) {
                    battle_not_over = false;
                    winner = "ENEMY";
                }
                player->SetNewAction(5);
                enemy->SetNewAction(5);
                std::cout << "Enemy attacked" << std::endl;
                turn = PLAYER;
            }
            player->Animate();
            enemy->Animate();
            battle_scene.DisplayFrame();
        }
        else if (battle_not_over == false) {
            // end of battle sequence
            // play death animation for whichever character lost and give items to player if they won
            // otherwise set lost to player
            if (winner == "PLAYER") {
                enemy->SetNewAction(3);
                // play death animation for enemy
                while (enemy->Animate()) {
                    battle_scene.DisplayFrame();
                }
                player->SetNewAction(2);
                while (player->Animate()) {
                    battle_scene.DisplayFrame();
                }
                player->SetNewAction(5);
                if (player->SetExp(enemy->GetExpReward())) {
                    // player level up animation
                }
                Sleep(1000);
                enemy->SetInvisible();
                enemy->SetCollidable(false);
                player->SetGold(player->GetGold() + enemy->GetGoldReward());
                keep_going = false;
                outcome = true;
            }
            else if (winner == "ENEMY") {
                outcome = false;
                keep_going = false;
            }
        }
    }
    return outcome;

}

int main()
{
    int height_of_screen = 700;
    int width_of_screen = 1.33 * height_of_screen;
    sf::Texture new_texture;
    if (!new_texture.loadFromFile("spriteimages\\ship3_transparent.png")) {
        std::cout << "new texture failed to load" << std::endl;
    }
    sf::Texture background_grass;
    if (!background_grass.loadFromFile("spriteimages\\complete_grass.png")) {
        std::cout << "background texture failed to load" << std::endl;
    }
    sf::Texture background_text;
    if (!background_text.loadFromFile("spriteimages\\complete_ground.png")) {
        std::cout << "background texture failed to load" << std::endl;
    }
    sf::Texture diamond_fight;
    if (!diamond_fight.loadFromFile("spriteimages\\battle_tile.png")) {
        std::cout << "background texture failed to load" << std::endl;
    }

    // background sprite
    MySprite background;
    background.setTexture(background_text);
    background.setPosition(0, 0);
    background.SetMaxSpeed(0);

    MySprite background_home;
    background_home.setTexture(background_grass);
    background_home.setPosition(0, 0);
    background_home.SetMaxSpeed(0);

    MySprite background_battle;
    background_battle.setTexture(diamond_fight);
    background_battle.setPosition(0, 0);
    background_battle.SetMaxSpeed(0);

    sf::RenderWindow window(sf::VideoMode(width_of_screen, height_of_screen), "Test Game");
    Scene scene(width_of_screen,height_of_screen,20,&window);

    OrcSprite test;
    MushyManSprite enemy;
    enemy.setPosition(300, 100);
    enemy.SetNewDir(S);
    enemy.SetNewAction(STOPPED);
    enemy.SetSpeed(0);
    enemy.SetAttack(4);
    enemy.Animate();
    test.setPosition(width_of_screen / 2 - 48, width_of_screen / 2 - 48);
    test.SetSpeed(0);
    test.SetNewAction(STOPPED);
    test.Animate();

    ItemSprite some_item("potion", 5, 9, 0);
    test.AddItemToInventory(&some_item);

    // try adding some text
    sf::Font font;

    if (!font.loadFromFile("fonts\\misc\\EightBitDragon-anqx.ttf")) {
        std::cout << "Couldnt load font" << std::endl;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("LOADING");
    text.setOrigin(168 / 2, 24);
    text.setCharacterSize(24);
    text.setPosition(width_of_screen/2, height_of_screen/2);
    // end try adding text


    // draw the sprite to start
    window.clear();
    window.draw(text);
    window.display();

    // pass the address of window and sprite to the scene
    scene.AddBackground(&background);
    scene.AddSprite(&test);
    scene.AddSprite(&enemy);

    // build the desert scene
    MushyManSprite enemy1;
    enemy1.setPosition(500, 500);
    enemy1.SetNewDir(S);
    enemy1.SetNewAction(STOPPED);
    enemy1.Animate();
    scene.AddSprite(&enemy1);

    // build main scene
    Scene main_scene(width_of_screen, height_of_screen, 20, &window);

    MySprite main_background;
    main_background.setTexture(background_grass);
    main_background.setPosition(0, 0);
    main_scene.AddBackground(&main_background);
    main_scene.AddSprite(&test);

    // build croc lande
    Scene croc_land(width_of_screen, height_of_screen, 20, &window);

    MySprite croc_background;
    croc_background.setTexture(background_text);
    croc_background.setPosition(0, 0);
    croc_land.AddBackground(&croc_background);
    croc_land.AddSprite(&test);

    // make some enemies for croc land
    OrcSprite crocen1;
    MushyManSprite crocen2;
    MushyManSprite crocen3;

    ReinerSprite* croc_sprites[3] = {&crocen1, &crocen2, &crocen3};

    crocen1.setPosition(500, 500);
    crocen2.setPosition(100, 600);
    crocen3.setPosition(300, 400);
    for (int i = 0; i < 3; i++) {
        croc_sprites[i]->SetNewDir(S);
        croc_sprites[i]->SetNewAction(STOPPED);
        croc_sprites[i]->Animate();
        croc_land.AddSprite(croc_sprites[i]);
    }

    // build final boss
    Scene final_land(width_of_screen, height_of_screen, 20, &window);

    MySprite final_background;
    final_background.setTexture(background_text);
    final_background.setPosition(0, 0);
    final_land.AddBackground(&final_background);
    final_land.AddSprite(&test);

    OrcSprite final_boss;
    final_boss.setPosition(width_of_screen/2, height_of_screen/2);
    final_boss.setOrigin(96 / 2, 96 / 2);
    final_boss.setScale(1.5, 1.5);
    final_boss.SetAttack(12);
    final_boss.SetNewDir(S);
    final_boss.SetNewAction(STOPPED);
    final_boss.Animate();
    final_land.AddSprite(&final_boss);

    // input clock will be used to time various inputs
    // NOT a game time clock
    sf::Clock input_clock;

    // clock for health regeneration
    sf::Clock health_regen;

    // main game loop
    // dictates many of the games aspects

    ReinerSprite* collided_enemy = NULL;
    Scene* current_scene = &main_scene;
    bool key_held_down = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // If the player is not in battle
        if (test.GetEventState() == PEACE) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                test.SetNewDir(NW);
                test.SetNewAction(WALKING);
                test.SetSpeed(3);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                test.SetNewDir(SW);
                test.SetNewAction(WALKING);
                test.SetSpeed(3);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                test.SetNewDir(NE);
                test.SetNewAction(WALKING);
                test.SetSpeed(3);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                test.SetNewDir(SE);
                test.SetNewAction(WALKING);
                test.SetSpeed(3);
            }
            else {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    test.SetNewDir(W);
                    test.SetNewAction(WALKING);
                    test.SetSpeed(3);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    test.SetNewDir(E);
                    test.SetNewAction(WALKING);
                    test.SetSpeed(3);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    test.SetNewDir(N);
                    test.SetNewAction(WALKING);
                    test.SetSpeed(3);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    test.SetNewDir(S);
                    test.SetNewAction(WALKING);
                    test.SetSpeed(3);
                }
                else {
                    test.SetNewAction(STOPPED);
                    test.SetSpeed(0);
                }
            }
            test.Animate();
        }
        // if player has entered battle
        else if (test.GetEventState() == BATTLE) {

            // store current position and other things of player so their state can be maintained
            sf::Vector2f cur_pos = test.getPosition();
            int store_action = test.GetActionState();
            int store_direction = test.GetDirState();
            float store_speed = test.GetSpeed();

            // set up battle and commence battle
            Scene BattleScene(width_of_screen, height_of_screen, 20, &window);
            BattleScene.AddBackground(&background_battle);
            std::cout << "It just works" << std::endl;
            if (Battle(&test, collided_enemy, BattleScene, &window) == false) {
                window.close();
            }
            test.SetEventState(PEACE);

            // reset the sprites state to before battle
            test.setPosition(cur_pos.x, cur_pos.y);
            test.SetNewAction(store_action);
            test.SetNewDir(store_direction);
            test.SetSpeed(store_speed);

            health_regen.restart();

        }
        ReinerSprite* place_holder = current_scene->CheckCollisions();
        if (place_holder != NULL) {
            test.SetEventState(BATTLE);
            collided_enemy = place_holder;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            if (key_held_down == false) {
                if (test.GetShowInventory()) {
                    test.SetShowInventory(false);
                }
                else {
                    test.SetShowInventory(true);
                }
            }
            key_held_down = true;
        }
        else {
            key_held_down = false;
        }
        // health regeneration
        if ((test.GetHealth() < test.GetMaxHealth()) && health_regen.getElapsedTime().asSeconds() > 2) {
            test.SetHealth(test.GetHealth() + 1);
            health_regen.restart();
        }
        // check if player is at the edge
        if (current_scene->CheckPlayerBounds(&test)) {
            sf::Vector2f player_pos = test.getPosition();
            // if player is in main scene. from here they can access 3 rooms
            if (current_scene == &main_scene) {
                if (player_pos.x > width_of_screen) {
                    current_scene = &scene;
                    test.setPosition(1, player_pos.y);
                }
                else if (player_pos.x < width_of_screen) {
                    current_scene = &croc_land;
                    test.setPosition(width_of_screen - 1, player_pos.y);
                }
                if (player_pos.y <= 0) {
                    current_scene = &final_land;
                    test.setPosition(player_pos.x, height_of_screen - 2);
                }
            }
            if (current_scene == &scene && player_pos.x < 0) {
                current_scene = &main_scene;
                test.setPosition(width_of_screen-1, player_pos.y);
            }
            if (current_scene == &croc_land && player_pos.x > width_of_screen) {
                current_scene = &main_scene;
                test.setPosition(1, player_pos.y);
            }
        }
        // use health potion if H is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && test.GetInventory().size() > 0) {
            std::vector<ItemSprite*> player_inventory = test.GetInventory();
            test.SetHealth(test.GetHealth() + player_inventory[0]->Use());
        }
        current_scene->DisplayFrame();
        if (final_boss.GetHealth() < 0) {
            window.close();
        }

    }

    return 0;
}
