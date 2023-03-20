#include "Menu.h"

Menu::Menu() {
}

void Menu::SetVisible(bool visibility) {
	visible = visibility;
}
bool Menu::GetVisible() {
	return visible;
}

void Menu::SetClickable(bool clickability) {
	clickable = clickability;
}
bool Menu::GetClickable() {
	return clickable;
}

void Menu::SetBackdrop(sf::RectangleShape* backdrop) {
	this->backdrop = backdrop;
}
sf::RectangleShape* Menu::GetBackdrop() {
	return backdrop;
}