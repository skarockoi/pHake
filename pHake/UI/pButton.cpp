#include "pButton.hpp"

#include <thread>
#include <future>

void pButton::Create(sf::RenderWindow* const& Window)
{
	window_ = Window;
	font_.loadFromFile("Settings/font.ttf");

	this->button_back_.setSize(sf::Vector2f(80, 28));
	this->button_back_.setPosition(0, 0);
	this->button_back_.setFillColor(sf::Color::Color(0, 0, 0, 150));
	this->button_back_.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
	this->button_back_.setOutlineThickness(1);

	this->button_text_.setFont(font_);
	this->button_text_.setCharacterSize(16);
	this->button_text_.setFillColor(sf::Color::Color(0, 0, 0, 255));
	this->button_text_.setPosition(0, 0);

	this->active(true);
}

void pButton::Loop()
{
	if (this->active_ && !this->busy_)
	{
		sf::Vector2i mouse = sf::Mouse::getPosition(*window_);
		if (!this->busy_)
		{
			if (this->IsOnBox())
			{
				this->highlight(true);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					if (function_ != NULL)
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
			{
				this->highlight(false);
			}
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
	if (this->resize_)
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
	button_back_.setPosition(x, y + 1);
	button_text_.setPosition(x, y + (button_back_.getSize().y / 4) - 5);
}

void pButton::text(const std::string& text)
{
	button_text_.setString(" " + text);
	update_length();
}

void pButton::fixed_size(int x, int y)
{
	if (!resize_)
		resize_ = false;

	button_back_.setSize(sf::Vector2f(x, y));
}

void pButton::font(sf::Font& font)
{
	button_text_.setFont(font);
}

bool pButton::active()
{
	return this->active_;
}