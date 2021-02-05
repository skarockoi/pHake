#include "pButton.hpp"

#include <thread>
#include <future>

#define TEXT_SIZE 16
#define TEXT_COLOR sf::Color::Color(0, 0, 0, 255)

#define BACK_WIDTH 80
#define BACK_HEIGHT 28
#define BACK_COLOR sf::Color::Color(0, 0, 0, 150)
#define BACK_COLOR_OUTLINE sf::Color::Color(0, 0, 0, 255)

#define DISTANCE_FROM_EDGE 20
#define DISTANCE_BETWEEN_NOTIFICATIONS 25

void pButton::Create(sf::RenderWindow* const& Window)
{
	window_ = Window;
	font_.loadFromFile("Settings/font.ttf");

	this->button_back_.setSize(sf::Vector2f(BACK_WIDTH - 1, BACK_HEIGHT - 1));
	this->button_back_.setFillColor(BACK_COLOR);
	this->button_back_.setOutlineColor(BACK_COLOR_OUTLINE);
	this->button_back_.setOutlineThickness(1);
	this->button_back_.setPosition(0, 0);

	this->button_text_.setFont(font_);
	this->button_text_.setCharacterSize(TEXT_SIZE);
	this->button_text_.setFillColor(TEXT_COLOR);
	this->button_text_.setPosition(0, 0);

	this->active(true);
}

void pButton::Loop()
{
	if (this->active_ && !this->busy_)
	{
		if (!this->busy_)
		{
			if (this->IsOnBox())
			{
				this->highlight(true);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					if (this->function_ != NULL)
					{
						std::thread([=]() {
							this->busy_ = true;

							((void(*)(void))function_)();
							std::this_thread::sleep_for(std::chrono::milliseconds(150));

							this->busy_ = false;
							}).detach();
					}

				}
			}
			else
				this->highlight(false);
		}
	}
}

void pButton::Draw()
{
	if (this->active())
	{
		window_->draw(button_back_);
		window_->draw(button_text_);
	}
}

void pButton::Connect(void(&functionP)())
{
	this->function_ = &functionP;
}

void pButton::timeout(int sleep)
{
	this->sleep_time_ = sleep;
}

sf::Vector2f pButton::size()
{
	return button_back_.getSize();
}

void pButton::active(bool act)
{
	this->active_ = act;
}

void pButton::highlight(bool value)
{
	if (value)
		button_back_.setOutlineColor(sf::Color::Color(255, 255, 255, 255));
	else
		button_back_.setOutlineColor(sf::Color::Color(0, 0, 0, 0));
}

void pButton::update_length()
{
	if (this->resizeable_)
	{
		sf::Vector2f rSize;
		rSize.x = ((float)std::string(button_text_.getString()).length() * 10) - (((std::string)button_text_.getString()).length() * 2);
		rSize.y = button_back_.getSize().y;
		button_back_.setSize(rSize);
	}
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
	update_length();
}

void pButton::fixed_size(int x, int y)
{
	if (!resizeable_)
		resizeable_ = false;

	button_back_.setSize(sf::Vector2f(x - 1, y - 1));
}

void pButton::font(sf::Font& font)
{
	button_text_.setFont(font);
}

bool pButton::active()
{
	return this->active_;
}