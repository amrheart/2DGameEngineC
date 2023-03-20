//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <Windows.h>
//#include <cstdlib>
//#include <time.h>
#include "Scene.h"
//#include "MySprite.h"

//class Sprite {
//public:
//    int height;
//    int width;
//    Sprite(int n_height, int n_width) {
//        height = n_height;
//        width = n_width;
//    }
//};

// MySprite inherits from Sprite


int main()
{
    int height_of_screen = 700;
    int width_of_screen = 1.33 * height_of_screen;
    sf::Texture new_texture;
    if (!new_texture.loadFromFile("plane1.png")) {
        std::cout << "new texture failed to load" << std::endl;
    }
    sf::Texture background_text;
    if (!background_text.loadFromFile("sky.png")) {
        std::cout << "background texture failed to load" << std::endl;
    }
    sf::Texture cloud_text;
    if (!cloud_text.loadFromFile("C:\\Users\\Alex\\Desktop\\2D graphics\\Project 3\\cow.png")) {
        std::cout << "cloud texture failed to load" << std::endl;
    }

    // player sprite
    MySprite a_sprite;
    sf::Vector2u text_size = new_texture.getSize();
    a_sprite.setTexture(new_texture);
    a_sprite.setPosition(0, 0);
    a_sprite.setOrigin(text_size.x/2,text_size.y/2);
    a_sprite.ChangeImageAngle(3.14159/2);
    a_sprite.setScale(.3, .3);
    a_sprite.SetMinSpeed(2);
    a_sprite.SetMaxSpeed(20);

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
    //window.draw(cloud);
    window.display();

    // pass the address of window and sprite to the scene
    scene.AddSprite(&background);
    scene.AddSprite(&a_sprite);
    //scene.AddSprite(&cloud);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            a_sprite.ChangeMoveAngle(.2);
            a_sprite.ChangeImageAngle(-.2);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            a_sprite.ChangeMoveAngle(-.2);
            a_sprite.ChangeImageAngle(.2);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            a_sprite.ChangeSpeed(.1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            a_sprite.ChangeSpeed(-.2);
        }
        // if no input, deccelerate
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
