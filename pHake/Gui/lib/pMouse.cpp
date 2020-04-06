#include "pMouse.hpp"

void pMouse::create(sf::RenderWindow* const& window)
{
	if (Window == 0)
	{
		Window = window;

		rMain.setSize(sf::Vector2f(10, 10));
		rMain.setPosition(0, 0);
		rMain.setFillColor(sf::Color::Color(255, 255, 255, 255));
		rMain.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
		rMain.setOutlineThickness(1);

		active = false;
	}
}

void pMouse::loop()
{
	if (this->active)
	{
		rMain.setPosition(sf::Mouse::getPosition().x - Window->getPosition().x, sf::Mouse::getPosition().y - Window->getPosition().y);
	}
}

void pMouse::draw()
{
	if (this->active)
	{
		Window->draw(rMain);
	}
}

bool pMouse::isActive(bool act)
{
	return this->active;
}

void pMouse::setActive(bool act)
{
	this->active = act;
}

void pMouse::setSize(int size)
{
	rMain.setSize(sf::Vector2f(size, size));
}

void pMouse::toggle()
{
	this->active = not this->active;
}

sf::Vector2f pMouse::getPosition()
{
	return rMain.getPosition();
}
