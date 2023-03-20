//class MySprite : public sf::Sprite {
//private:
//    int height;
//    int width;
//    float x_pos;
//    float y_pos;
//    int dx;
//    int dy;
//    float move_angle = 0;
//    float image_angle = 0;
//    float speed = 0;
//
//
//public:
//    using sf::Sprite::Sprite;
//
//    // for now will be simple transform
//    // takes the move angle and speed and converts to x y
//    void my_update() {
//        setRotation(move_angle * (180 / 3.14159));
//        sf::Vector2f cur_pos = getPosition();
//        x_pos = cur_pos.x + cos(move_angle) * speed;
//        y_pos = cur_pos.y - sin(move_angle) * speed;
//        setPosition(x_pos, y_pos);
//    }
//
//    void increaseSpeed(float increase) {
//        speed += increase;
//    }
//
//    void changeMoveAngle(float increase) {
//        move_angle += increase;
//    }
//
//    void changeImageAngle(float increase) {
//        image_angle += increase;
//    }
//};
//
//class Scene {
//private:
//    // height and width of screen with start position of scene
//    int height = 0;
//    int width = 0;
//    int x_pos = 0;
//    int y_pos = 0;
//    float FPS = 30;
//
//    // Pointer to a render window
//    // allows Scene object to manipulate screen
//    sf::RenderWindow* window;
//
//    // sprites in the scene
//    std::vector<MySprite*> list_of_sprites;
//
//    // background will be a sprite for now
//    // Ill keep the background sprite seperate
//    sf::Sprite background;
//
//public:
//    Scene(int n_height, int n_width, int n_x_pos, int n_y_pos) {
//        height = n_height;
//        width = n_width;
//        x_pos = n_x_pos;
//        y_pos = n_y_pos;
//    }
//    // sets the scenes window object
//    void setWindow(sf::RenderWindow* n_window) {
//        window = n_window;
//    }
//
//    // draw the sprites to the screen
//    void draw() {
//        MySprite* n_sprite = list_of_sprites.front();
//        window->draw(*n_sprite);
//    }
//
//    // updates the position of the sprites
//    void update() {
//        MySprite* n_sprite = list_of_sprites.front();
//        n_sprite->my_update();
//    }
//
//    // clear and display the new screen
//    // called once per frame, so frame rate is done here
//    void display() {
//        time_t start = time(0);
//        window->clear();
//        update();
//        draw();
//        float time_elapsed = difftime(time(0), start);
//        // sleep for the remaining time of the frame
//        float remaining_time = FPS - time_elapsed;
//        if (remaining_time < 0) {
//            std::cout << "losing frames" << std::endl;
//        }
//        else {
//            Sleep(remaining_time);
//        }
//        window->display();
//    }
//
//    // add a sprite to the back of the sprite list
//    void addSprite(MySprite* new_sprite) {
//        list_of_sprites.push_back(new_sprite);
//    }
//
//    // getters
//    int getHeight() {
//        return height;
//    }
//
//    int getWidth() {
//        return width;
//    }
//
//    ~Scene() {
//    }
//};