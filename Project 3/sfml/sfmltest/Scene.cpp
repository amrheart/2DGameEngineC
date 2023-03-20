#include "Scene.h"

Scene::Scene(int width, int height, int FPS, sf::RenderWindow* window) {
	this->height = height;
	this->width = width;
	this->FPS = FPS;
	this->window = window;
	this->frame_duration = 1 / FPS;

	int row = 5;
	int column = 6;

	if (!font.loadFromFile("fonts\\misc\\EightBitDragon-anqx.ttf")) {
		std::cout << "Couldnt load font" << std::endl;
	}

	// stats panel stuff
	stats_rect.width = 200;
	stats_rect.height = 100;
	stats_rect.left = 700;
	stats_rect.top = 600;

	sf::Vector2f stats_size(200, 100);
	stats_backdrop.setSize(stats_size);
	stats_backdrop.setFillColor(sf::Color::Black);
	stats_backdrop.setPosition(stats_rect.left, stats_rect.top);

	// set stats display text
	int char_size = 15;
	player_health.setFont(font);
	player_damage.setFont(font);
	player_defense.setFont(font);
	player_gold.setFont(font);
	player_health.setString("Health: " + std::to_string(10));
	player_damage.setString("Damage: " + std::to_string(10));
	player_defense.setString("EXP: " + std::to_string(0));
	player_gold.setString("Gold: " + std::to_string(0));
	player_health.setCharacterSize(char_size);
	player_damage.setCharacterSize(char_size);
	player_defense.setCharacterSize(char_size);
	player_gold.setCharacterSize(char_size);
	player_health.setPosition(stats_rect.left, stats_rect.top);
	player_damage.setPosition(stats_rect.left, stats_rect.top + char_size + 1);
	player_defense.setPosition(stats_rect.left, stats_rect.top + char_size * 2 + 2);
	player_gold.setPosition(stats_rect.left, stats_rect.top + char_size * 3 + 3);

	// set border scenes to null
	left_bound = NULL;
	right_bound = NULL;
	top_bound = NULL;
	bottom_bound = NULL;
}

void Scene::AddBackground(MySprite* background) {
	this->background = background;
}

void Scene::AddHud(MySprite* HUD) {
	this->hud = HUD;
}

void Scene::AddSprite(ReinerSprite* new_sprite) {
	this->list_of_sprites.push_back(new_sprite);
}

void Scene::UpdateSprites() {
	int num_of_sprites = list_of_sprites.size();
	ReinerSprite* player = list_of_sprites[0];
	for (int i = 0; i < num_of_sprites; i++) {
		ReinerSprite* temp = list_of_sprites[i];
		sf::Vector2f ph = temp->getPosition();
		temp->UpdateSprite();
		
		// Check Bounds
		// scene will handle the positioning of sprites when they leave screen
		if (CheckBounds(temp)) {
			// if a sprite that is not the player
			if (temp != player) {
				temp->setPosition(ph);
			}
		}
		//this->CheckCollisions();

	}
}

void Scene::DrawSprites() {
	int num_of_sprites = list_of_sprites.size();
	// always draw background first
	this->window->draw(*background);

	for (int i = 0; i < num_of_sprites; i++) {
		MySprite* temp = list_of_sprites[i];
		if (!(temp->GetInvisible())) {
			this->window->draw(*temp);
		}
	}
	// if inventory is to be shown, draw it
	ReinerSprite* player = list_of_sprites[0];
	if (player->GetShowInventory()) {
		window->draw(player->GetBackdrop());
		std::vector<ItemSprite*> the_inventory = player->GetInventory();
		int num_of_items = the_inventory.size();
		for (int i = 0; i < num_of_items; i++) {
			this->window->draw(*the_inventory[i]);
		}
	}
	// draw stats panel
	player_health.setString("Health: " + std::to_string(player->GetHealth()));
	player_damage.setString("Damage: " + std::to_string(player->GetAttack()));
	player_defense.setString("EXP: " + std::to_string(player->GetExp()));
	player_gold.setString("Gold: " + std::to_string(player->GetGold()));
	window->draw(stats_backdrop);
	window->draw(player_health);
	window->draw(player_damage);
	window->draw(player_defense);
	window->draw(player_gold);
}

void Scene::DisplayFrame() {
	//auto start = std::chrono::steady_clock::now();
	time_t start = time(0);
	window->clear();
	this->UpdateSprites();
	this->DrawSprites();
	float time_elapsed = difftime(time(0), start);
	//auto end = std::chrono::steady_clock::now();
	//std::chrono::duration<double> time_elapsed = end - start;

	// sleep for the remaining time of the frame
	float remaining_time = this->FPS - time_elapsed;
	if (remaining_time < 0) {
		std::cout << "losing frames" << std::endl;
	}
	else {
	    Sleep(remaining_time);
	}
	// always displaying at the end of the frame rather than randomly within it
	this->window->display();
}

bool Scene::CheckBounds(MySprite* sprite_to_check) {
	bool out_of_bounds = false;
	sf::Vector2f pos = sprite_to_check->getPosition();
	if (pos.x > this->width || pos.x < 0) {
		out_of_bounds = true;
	}
	else if (pos.y > this->height || pos.y < 0) {
		out_of_bounds = true;
	}
	return out_of_bounds;
}

bool Scene::CheckPlayerBounds(ReinerSprite* player) {
	bool out_of_bounds = false;
	sf::Vector2f pos = player->getPosition();
	if (pos.x > this->width || pos.x < 0) {
		out_of_bounds = true;
	}
	else if (pos.y > this->height || pos.y < 0) {
		out_of_bounds = true;
	}
	return out_of_bounds;
}

ReinerSprite* Scene::CheckCollisions() {
	// index starts at 2 because only enemies will be checked against player
	/*int num_of_sprites = list_of_sprites.size();
	for (int index = 2; index < num_of_sprites; index++) {
		MySprite* temp = list_of_sprites[index];
		if (temp->CollidesWith(list_of_sprites[1])) {
			temp->SetInvisible();
		}
	}*/
	ReinerSprite* player = list_of_sprites[0];
	int num_of_sprite = list_of_sprites.size();
	for (int i = 0; i < num_of_sprite; i++) {
		if (i != 0) {
			if (player->CollidesWith(list_of_sprites[i])) {
				std::cout << "You collided with an enemy" << std::endl;
				return list_of_sprites[i];
			}
		}
	}
	return NULL;
}

void Scene::Bounce(MySprite* sprite_to_bounce) {

	// calculate the opposite angle
	float opposite_angle = sprite_to_bounce->GetMoveAngle() - 3.14159;
	float opposite_image_angle = sprite_to_bounce->GetImageAngle() - 3.14159;

	// need to move the sprite back in bounds so it doesnt trigger repeatadly
	sf::Vector2f cur_pos = sprite_to_bounce->getPosition();
	int new_x = cur_pos.x;
	int new_y = cur_pos.y;
	if (cur_pos.x < 0) {
		new_x = 1;
	}
	else if (cur_pos.x > this->width) {
		new_x = this->width-1;
	}
	if (cur_pos.y < 0) {
		new_y = 1;
	}
	else if (cur_pos.y > this->height) {
		new_y = this->height - 1;
	}
	sprite_to_bounce->setPosition(new_x, new_y);

	// set the rotation
	sprite_to_bounce->SetImageAngle(opposite_image_angle);
	sprite_to_bounce->SetMoveAngle(opposite_angle);
}

void Scene::Teleport(MySprite* sprite_to_tp) {
	sf::Vector2f cur_pos = sprite_to_tp->getPosition();
	float new_y = cur_pos.y;
	float new_x = cur_pos.x;
	if (cur_pos.x > this->width) {
		new_y = this->height - cur_pos.y;
		new_x = 0;
	}
	else if (cur_pos.x < 0) {
		new_y = this->height - cur_pos.y;
		new_x = this->width - 1;
	}
	if (cur_pos.y > this->height) {
		new_x = this->width - cur_pos.x;
		new_y = 0;
	}
	else if (cur_pos.y < 0) {
		new_x = this->width - cur_pos.x;
		new_y = this->height - 1;
	}
	sprite_to_tp->setPosition(new_x, new_y);
}

void Scene::ReverseDirection(ReinerSprite* sprite_to_reverse) {
	int cur_direction = sprite_to_reverse->GetDirState();
	if (cur_direction == 0) {
		sprite_to_reverse->SetNewDir(7);
	}
	else if (cur_direction == 1) {
		sprite_to_reverse->SetNewDir(4);
	}
	else if (cur_direction == 2) {
		sprite_to_reverse->SetNewDir(6);
	}
	else if (cur_direction == 3) {
		sprite_to_reverse->SetNewDir(5);
	}
	else if (cur_direction == 4) {
		sprite_to_reverse->SetNewDir(1);
	}
	else if (cur_direction == 5) {
		sprite_to_reverse->SetNewDir(3);
	}
	else if (cur_direction == 6) {
		sprite_to_reverse->SetNewDir(2);
	}
	else if (cur_direction == 7) {
		sprite_to_reverse->SetNewDir(0);
	}
}

int Scene::GetHeight() {
	return height;
}
int Scene::GetWidth() {
	return width;
}