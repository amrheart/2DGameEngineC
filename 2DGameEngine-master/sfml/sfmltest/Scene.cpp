#include "Scene.h"

Scene::Scene(int width, int height, int FPS, sf::RenderWindow* window) {
	this->height = height;
	this->width = width;
	this->FPS = FPS;
	this->window = window;
	this->frame_duration = 1 / FPS;
}

void Scene::AddSprite(MySprite* new_sprite) {
	this->list_of_sprites.push_back(new_sprite);
}

void Scene::UpdateSprites() {
	int num_of_sprites = list_of_sprites.size();
	for (int i = 0; i < num_of_sprites; i++) {
		MySprite* temp = list_of_sprites[i];
		temp->UpdateSprite();
		
		// Check Bounds
		// scene will handle the positioning of sprites when they leave screen
		if (CheckBounds(temp)) {
			// handle the case of sprite leaving screen
			//temp->setPosition(50, 50);
			this->Bounce(temp);
		}
		this->CheckCollisions();

	}
}

void Scene::DrawSprites() {
	int num_of_sprites = list_of_sprites.size();
	for (int i = 0; i < num_of_sprites; i++) {
		MySprite* temp = list_of_sprites[i];
		if (!(temp->GetInvisible())) {
			this->window->draw(*temp);
		}
	}
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

void Scene::CheckCollisions() {
	// index starts at 2 because only enemies will be checked against player
	/*int num_of_sprites = list_of_sprites.size();
	for (int index = 2; index < num_of_sprites; index++) {
		MySprite* temp = list_of_sprites[index];
		if (temp->CollidesWith(list_of_sprites[1])) {
			temp->SetInvisible();
		}
	}*/
	MySprite* player = list_of_sprites[1];
	MySprite* enemy = list_of_sprites[2];
	if (player->CollidesWith(enemy)) {
		std::cout << "Its working" << std::endl;
		enemy->SetInvisible();
	}
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