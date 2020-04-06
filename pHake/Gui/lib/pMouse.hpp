#ifndef _PMOUSE_HPP_
#define _PMOUSE_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>  

class pMouse
{
private:
	bool active = false;

	sf::RenderWindow*  Window;
	sf::Font		   Font;
	sf::Vector2i	   Display;
	sf::Vector2i       Mouse;
	sf::RectangleShape rMain;

public:
	pMouse() {}

	void create(sf::RenderWindow* const& window);
	void loop();
	void draw();
	void toggle();

	void setSize(int size); //in pixel
	sf::Vector2f getPosition();

private:
	bool isActive(bool act);
	void setActive(bool act);
};
#endif