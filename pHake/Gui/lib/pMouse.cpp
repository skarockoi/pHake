#include "pMouse.hpp"

void pMouse::create(sf::RenderWindow* const& Window)
{
	if (window == 0)
	{
		window = Window;

		mouse_rect.setSize(sf::Vector2f(10, 10));
		mouse_rect.setFillColor(sf::Color::Color(255, 255, 255, 255));
		mouse_rect.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
		mouse_rect.setOutlineThickness(1);
	}
}

void pMouse::loop()
{
	if (this->active)
	{
		mouse_rect.setPosition(sf::Mouse::getPosition().x - window->getPosition().x, sf::Mouse::getPosition().y - window->getPosition().y);
	}
}

void pMouse::draw()
{
	if (this->active)
	{
		window->draw(mouse_rect);
	}
}

void pMouse::toggle()
{
	this->active = not this->active;
}

void pMouse::setSize(int size)
{
	mouse_rect.setSize(sf::Vector2f(size, size));
}