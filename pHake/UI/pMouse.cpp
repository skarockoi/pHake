#include "pMouse.hpp"

#include <string>
#include <sstream>  

#define MOUSE_SIZE 10
#define MOUSE_COLOR sf::Color::Color(255, 255, 255, 255)
#define MOUSE_COLOR_OUTLINE sf::Color::Color(0, 0, 0, 255)

void pMouse::Create(sf::RenderWindow* const& Window)
{
	if (window_ == 0)
	{
		window_ = Window;

		mouse_rect_.setSize(sf::Vector2f(MOUSE_SIZE, MOUSE_SIZE));
		mouse_rect_.setFillColor(MOUSE_COLOR);
		mouse_rect_.setOutlineColor(MOUSE_COLOR_OUTLINE);
		mouse_rect_.setOutlineThickness(1);
	}
}

void pMouse::Loop()
{
	if (active_)
		mouse_rect_.setPosition(sf::Mouse::getPosition().x - window_->getPosition().x, sf::Mouse::getPosition().y - window_->getPosition().y);
}

void pMouse::Draw()
{
	if (active_)
		window_->draw(mouse_rect_);
}

void pMouse::Toggle()
{
	active_ = not active_;
}

void pMouse::size(int size)
{
	mouse_rect_.setSize(sf::Vector2f(size, size));
}

void pMouse::active(bool Active)
{
	active_ = Active;
}

bool pMouse::active()
{
	return active_;
}