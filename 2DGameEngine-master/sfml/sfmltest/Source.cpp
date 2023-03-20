#include "Scene.h"
#include <chrono>
#include <thread>

int main()
{
    int height_of_screen = 700;
    int width_of_screen = 1.33 * height_of_screen;
    sf::Texture new_texture;
    if (!new_texture.loadFromFile("spriteimages\\ship3_transparent.png")) {
        std::cout << "new texture failed to load" << std::endl;
    }
    sf::Texture background_text;
    if (!background_text.loadFromFile("spriteimages\\sky.png")) {
        std::cout << "background texture failed to load" << std::endl;
    }
    sf::Texture cloud_text;
    if (!cloud_text.loadFromFile("spriteimages\\cow.png")) {
        std::cout << "cloud texture failed to load" << std::endl;
    }
    sf::Texture sprite_sheet;
    if (!sprite_sheet.loadFromFile("spriteimages\\plane_sheet.png")) {
        std::cout << "Plane sprite sheet failed to load" << std::endl;
    }
    /*sf::IntRect sprite_rect(30, 20, 120, 120);
    PlayerSprite plane;
    plane.setTexture(sprite_sheet);
    plane.setTextureRect(sprite_rect);
    plane.setPosition(75, 75);
    sf::Clock clock;*/
    //sf::Texture orc_test;
    //if (!orc_test.loadFromFile("spriteimages\\mushyman bitmaps\\stopped0000.bmp")) {
    //    std::cout << "orc texture failed to load" << std::endl;
    //}
    // workshop for animations
    // some constants for state: constants define a direction and action
    const int S = 0;
    const int SW = 1;
    const int W = 2;
    const int NW = 3;
    const int N = 4;
    const int NE = 5;
    const int E = 6;
    const int SE = 7;
    const int WALKING = 0;

    //std::string dirs[] = { "s", "sw", "w", "nw", "n", "ne", "e", "se" };
    ////load some mushy man walk textures into a matrix
    //sf::Texture walk_cycles[8][8];
    //for (int i = 0; i < 8; i++) {
    //    for (int n = 0; n < 8; n++) {
    //        sf::Texture cur_image;
    //        std::string name_of_file = "spriteimages\\mushyman bitmaps\\walking ";
    //        name_of_file += dirs[i];
    //        name_of_file += "000";
    //        name_of_file += std::to_string(n);
    //        name_of_file += ".bmp";
    //        std::cout << name_of_file << std::endl;
    //        cur_image.loadFromFile(name_of_file);
    //        walk_cycles[i][n] = cur_image;
    //    }
    //}
    // load orc textures
    //sf::Texture orc_w;
    //orc_w.loadFromFile("spriteimages\\mushyman bitmaps\\stopped0002.bmp");
    //sf::Texture orc_n;
    //orc_n.loadFromFile("spriteimages\\mushyman bitmaps\\stopped0004.bmp");
    //sf::Texture orc_s;
    //orc_s.loadFromFile("spriteimages\\mushyman bitmaps\\stopped0000.bmp");
    //sf::Texture orc_e;
    //orc_e.loadFromFile("spriteimages\\mushyman bitmaps\\stopped0006.bmp");
    //sf::Texture orc_nw;
    //orc_nw.loadFromFile("spriteimages\\mushyman bitmaps\\stopped0003.bmp");
    //sf::Texture orc_ne;
    //orc_ne.loadFromFile("spriteimages\\mushyman bitmaps\\stopped0005.bmp");
    //sf::Texture orc_sw;
    //orc_sw.loadFromFile("spriteimages\\mushyman bitmaps\\stopped0001.bmp");
    //sf::Texture orc_se;
    //orc_se.loadFromFile("spriteimages\\mushyman bitmaps\\stopped0007.bmp");



    //// load textures into an array
    //std::string dir[4] = { "n", "e", "s", "w" };
    //int num[2] = { 0, 1 };
    //std::vector<sf::Texture> text_vect;
    //for (int i = 0; i < 4; i++) {
    //    sf::Texture temp;
    //    std::string file_name = "spriteimages\\walking ";
    //    file_name += dir[i];
    //    file_name += "0000.bmp";
    //    temp.loadFromFile(file_name);
    //    text_vect.push_back(temp);
    //}

    // player sprite
    PlayerSprite a_sprite;
    sf::Vector2u text_size = new_texture.getSize();
    a_sprite.setTexture(new_texture);
    a_sprite.setPosition(0, 0);
    a_sprite.setOrigin(text_size.x / 2, text_size.y / 2);
    a_sprite.ChangeImageAngle(3.14159 / 2);
    a_sprite.setScale(.3, .3);
    a_sprite.SetMinSpeed(2);
    a_sprite.SetMaxSpeed(20);

    //// orc sprite
    //MySprite orc_sprite;
    //sf::Vector2u orc_text_size = orc_sprite.getSize();
    //orc_sprite.setTexture(orc_test);
    //orc_sprite.setPosition(75, 75);
    //orc_sprite.SetXY(50, 50);
    //orc_sprite.setOrigin(orc_text_size.x / 2, orc_text_size.y / 2);
    //orc_sprite.SetMaxSpeed(0);

    // background sprite
    MySprite background;
    background.setTexture(background_text);
    background.setPosition(0, 0);
    background.SetMaxSpeed(0);

    // cloud sprite
    MySprite cloud;
    cloud.setTexture(cloud_text);
    cloud.setPosition(height_of_screen/2, width_of_screen/2);
    cloud.SetMaxSpeed(0);
    cloud.setScale(.2, .2);

    sf::RenderWindow window(sf::VideoMode(width_of_screen, height_of_screen), "Test Game");
    Scene scene(width_of_screen,height_of_screen,20,&window);

    // draw the sprite to start
    window.clear();
    window.draw(background);
    window.draw(a_sprite);
    window.draw(cloud);
    window.display();

    // pass the address of window and sprite to the scene
    scene.AddSprite(&background);
    scene.AddSprite(&a_sprite);
    scene.AddSprite(&cloud);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        //    orc_sprite.setTexture(orc_ne, true);
        //}
        //else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        //    orc_sprite.setTexture(orc_nw, true);
        //}
        //else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        //    orc_sprite.setTexture(orc_se, true);
        //}
        //else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        //    orc_sprite.setTexture(orc_sw, true);
        //}
        //// if no input, deccelerate
        //else {
            //if (orc_sprite.GetSpeed() > 0) {
            //    orc_sprite.ChangeSpeed(-.1);
            //}
            //else if (orc_sprite.GetSpeed() < 0) {
            //    orc_sprite.ChangeSpeed(.1);
            //}
            //// ensure that speed is 0
            //else {
            //    orc_sprite.SetSpeed(0);
            //}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                a_sprite.ChangeMoveAngle(.2);
                a_sprite.ChangeImageAngle(-.2);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                a_sprite.ChangeMoveAngle(-.2);
                a_sprite.ChangeImageAngle(.2);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                a_sprite.ChangeSpeed(.1);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                a_sprite.ChangeSpeed(-.2);
            }
            else {
                if (a_sprite.GetSpeed() > 0) {
                    a_sprite.ChangeSpeed(-.1);
                }
                else if (a_sprite.GetSpeed() < 0) {
                    a_sprite.ChangeSpeed(.1);
                }
                // ensure that speed is 0
                else {
                    a_sprite.SetSpeed(0);
                }
            }
        scene.DisplayFrame();

    }

    return 0;
}
