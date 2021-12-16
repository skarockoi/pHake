#include "pButton.hpp"

#include <thread>
#include <future>

#define TEXT_SIZE 16
#define TEXT_COLOR sf::Color::Color(0, 0, 0, 255)

#define BACK_WIDTH 80
#define BACK_HEIGHT 28
#define BACK_COLOR sf::Color::Color(0, 0, 0, 150)
#define BACK_COLOR_OUTLINE sf::Color::Color(0, 0, 0, 255)

#define HIGHLIGHT_COLOR sf::Color::Color(255, 255, 255, 255)

void pButton::Create(sf::RenderWindow* const& Window, sf::Font* Font)
{
	window_ = Window;
	this->font_ = Font;

	this->button_back_.setSize(sf::Vector2f(BACK_WIDTH - 1, BACK_HEIGHT - 1));
	this->button_back_.setFillColor(BACK_COLOR);
	this->button_back_.setOutlineColor(BACK_COLOR_OUTLINE);
	this->button_back_.setOutlineThickness(1);
	this->button_back_.setPosition(0, 0);

	this->button_text_.setFont(*font_);
	this->button_text_.setCharacterSize(TEXT_SIZE);
	this->button_text_.setFillColor(TEXT_COLOR);
	this->button_text_.setPosition(0, 0);

	this->active_ = true;
}

void pButton::Loop()
{
	if (this->active_ && !this->busy_)
	{
		if (this->IsOnBox())
		{
			this->Hightlight(true);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				if (this->function_ != NULL)
				{
					std::thread([=]() {

						this->busy_ = true;
						((void(*)(void))function_)();

						while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->IsOnBox())
							std::this_thread::sleep_for(std::chrono::milliseconds(10));
						

						this->busy_ = false;
					}).detach();
				}
			}
		}
		else
			this->Hightlight(false);
	}
}

void pButton::Draw()
{
	if (this->active_)
	{
		window_->draw(button_back_);
		window_->draw(button_text_);
	}
}

void pButton::Connect(void(&functionP)())
{
	this->function_ = &functionP;
}

sf::Vector2f pButton::size()
{
	return button_back_.getSize();
}

void pButton::Hightlight(bool value)
{
	if (value && this->button_back_.getOutlineColor() != HIGHLIGHT_COLOR)
		this->button_back_.setOutlineColor(HIGHLIGHT_COLOR);
	else if (!value && this->button_back_.getOutlineColor() == HIGHLIGHT_COLOR)
		button_back_.setOutlineColor(BACK_COLOR_OUTLINE);
}

bool pButton::IsOnBox()
{
	sf::Vector2i mouse = sf::Mouse::getPosition(*window_);
	if (mouse.x > button_back_.getPosition().x &&
		mouse.x < button_back_.getPosition().x + button_back_.getSize().x &&
		mouse.y > button_back_.getPosition().y &&
		mouse.y < button_back_.getPosition().y + button_back_.getSize().y)
		return true;
	else
		return false;
}

void pButton::position(int x, int y)
{
	button_back_.setPosition(x, y);
	button_text_.setPosition(x, y + (button_back_.getSize().y / 4) - 5);
}

void pButton::text(const std::string& text)
{
	button_text_.setString(" " + text);
}

void pButton::size(int x, int y)
{
	button_back_.setSize(sf::Vector2f(x - 1, y - 1));
}