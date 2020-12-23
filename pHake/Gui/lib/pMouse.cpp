#include "pMouse.hpp"

void pMouse::Create(sf::RenderWindow* const& Window)
{
	if (window_ == 0)
	{
		this->window_ = Window;

		this->mouse_rect_.setSize(sf::Vector2f(10, 10));
		this->mouse_rect_.setFillColor(sf::Color::Color(255, 255, 255, 255));
		this->mouse_rect_.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
		this->mouse_rect_.setOutlineThickness(1);
	}
}

void pMouse::Loop()
{
	if (this->active_)
	{
		this->mouse_rect_.setPosition(sf::Mouse::getPosition().x - window_->getPosition().x, sf::Mouse::getPosition().y - window_->getPosition().y);
	}
}

void pMouse::Draw()
{
	if (this->active_)
	{
		this->window_->draw(mouse_rect_);
	}
}

void pMouse::Toggle()
{
	this->active_ = not this->active_;
}

void pMouse::size(int size)
{
	this->mouse_rect_.setSize(sf::Vector2f(size, size));
}

void pMouse::active(bool Active)
{
	this->active_ = Active;
}

bool pMouse::active()
{
	return this->active_;
}