#ifndef _PMOUSE_HPP_
#define _PMOUSE_HPP_

#include <SFML/Graphics.hpp>

class pMouse
{
private:
	bool active_ = false;
	sf::RenderWindow*  window_;
	sf::RectangleShape mouse_rect_;

public:
	void Create(sf::RenderWindow* const& window);
	void Loop();
	void Draw();
	void Toggle();

public:
	void size(int size); //in pixel
	void active(bool Active);
	bool active();
};
#endif