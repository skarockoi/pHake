#ifndef _PMOUSE_HPP_
#define _PMOUSE_HPP_

#include <SFML/Graphics.hpp>

class pMouse // rectanuglar mouse you see when toggling the menu
{
public:
	pMouse() : window_(0), mouse_rect_({0,0}), active_(false) { }
	void Create(sf::RenderWindow* const& window);
	void Loop();
	void Draw();
	void Toggle();

public:
	void size(int size); //in pixel
	void active(bool Active);
	bool active();

private:
	sf::RenderWindow* window_;
	sf::RectangleShape mouse_rect_;
	bool active_;
};
#endif