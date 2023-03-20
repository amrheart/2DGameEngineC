#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
// menus are just containers for data, so dont need to derive ... for now
class Menu
{
protected:
	bool visible;
	bool clickable;

	sf::RectangleShape* backdrop;
public:
	Menu();

	void SetVisible(bool visibility);
	bool GetVisible();

	void SetClickable(bool clickability);
	bool GetClickable();

	void SetBackdrop(sf::RectangleShape* backdrop);
	sf::RectangleShape* GetBackdrop();
};

#endif