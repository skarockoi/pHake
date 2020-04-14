#ifndef _PMOUSE_HPP_
#define _PMOUSE_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>  

class pMouse
{
private:
	bool active = false;
	sf::RenderWindow*  window;
	sf::RectangleShape mouse_rect;

public:
	void create(sf::RenderWindow* const& window);
	void loop();
	void draw();
	void toggle();

public:
	void setSize(int size); //in pixel
};
#endif