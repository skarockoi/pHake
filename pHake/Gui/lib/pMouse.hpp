#ifndef _PMOUSE_HPP_
#define _PMOUSE_HPP_

#include <SFML/Graphics.hpp>
#include <thread>
#include <string>
#include <sstream>  

class pMouse
{
private:
	bool active = false;

	sf::RenderWindow*  Window;
	sf::Font		   Font;
	sf::Vector2i	   Pos;
	sf::Vector2i	   Display;
	sf::Vector2i       Mouse;
	sf::RectangleShape rMain;

public:
	pMouse() {}

	void create(sf::RenderWindow* const& window)
	{
		if (Window == 0)
		{
			Window = window;

			Pos.x = 0;
			Pos.y = 0;

			rMain.setSize(sf::Vector2f(7, 7));
			rMain.setPosition(Pos.x, Pos.y);
			rMain.setFillColor(sf::Color::Color(255, 255, 255, 255));
			rMain.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
			rMain.setOutlineThickness(1);

			active = true;
		}
	}

	void Loop()
	{
		if (this->active)
		{
			rMain.setPosition(sf::Mouse::getPosition().x - Window->getPosition().x, sf::Mouse::getPosition().y - Window->getPosition().y);
		}
	}

	void draw()
	{
		if (this->active)
		{
			Window->draw(rMain);
		}
	}
public:
	void setSize(int size)
	{
		rMain.setSize(sf::Vector2f(size, size));
	}

	void toggle()
	{
		this->active = not this->active;
	}

	sf::Vector2f getPosition()
	{
		return rMain.getPosition();
	}
};
#endif