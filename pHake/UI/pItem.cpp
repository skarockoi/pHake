#include "pItem.hpp"

#include <string>
#include <sstream>  
#include <iomanip>
#include <thread>

#define TEXT_SIZE 16
#define TEXT_COLOR sf::Color::Color(255, 255, 255, 255)

#define BACK_WIDTH 80
#define BACK_HEIGHT 28
#define BACK_COLOR sf::Color::Color(0, 0, 0, 0)
#define BACK_COLOR_OUTLINE sf::Color::Color(0, 0, 0, 0)

#define HIGHLIGHT_COLOR sf::Color::Color(255, 255, 255, 255)
#define SLEEP_DURATION 100
#define FLOAT_PRECISION 1

void pItemBone::Create(sf::RenderWindow* const& Window, sf::Font* Font)
{
	this->window_ = Window;
	this->font_ = Font;

	this->rect_back_.setSize(sf::Vector2f(BACK_WIDTH - 1, BACK_HEIGHT - 1));
	this->rect_back_.setPosition(0, 0);
	this->rect_back_.setFillColor(BACK_COLOR);
	this->rect_back_.setOutlineColor(BACK_COLOR_OUTLINE);
	this->rect_back_.setOutlineThickness(1);

	this->text_.setFont(*font_);
	this->text_.setCharacterSize(TEXT_SIZE);
	this->text_.setFillColor(TEXT_COLOR);
	this->text_.setPosition(0, 0);

	this->sleep_duration_ = SLEEP_DURATION;
	this->active_ = true;
}

void pItemBone::Draw()
{
	if (this->active_)
	{
		this->window_->draw(rect_back_);
		this->window_->draw(text_);
	}
}

void pItemBone::Hightlight(bool value)
{
	if (value && this->rect_back_.getOutlineColor() != HIGHLIGHT_COLOR)
		rect_back_.setOutlineColor(HIGHLIGHT_COLOR);
	else if (!value && this->rect_back_.getOutlineColor() == HIGHLIGHT_COLOR)
		rect_back_.setOutlineColor(BACK_COLOR_OUTLINE);
}

void pItemBone::position(uint32_t x, uint32_t y)
{
	this->rect_back_.setPosition(x, y);
	this->text_.setPosition(x, y + (this->rect_back_.getSize().y / 4) - 5);
}

void pItemBone::size(uint32_t x, uint32_t y)
{
	if (!resizeable_)
		resizeable_ = false;

	rect_back_.setSize(sf::Vector2f(x, y));
}

bool pItemBone::IsOnBox()
{
	sf::Vector2i mouse = sf::Mouse::getPosition(*window_);
	if (mouse.x > rect_back_.getPosition().x &&
		mouse.x < rect_back_.getPosition().x + rect_back_.getSize().x &&
		mouse.y > rect_back_.getPosition().y &&
		mouse.y < rect_back_.getPosition().y + rect_back_.getSize().y)
		return true;
	else
		return false;
}

sf::Vector2f pItemBone::size()
{
	return rect_back_.getSize();
}

void pItemInt::AddValue(uint32_t& Value, uint32_t Inc, uint32_t Dec)
{
	this->value_ = &Value;
	this->inc_ = Inc;
	this->dec_ = Dec;
}

void pItemInt::Loop()
{
	if (this->active_)
	{
		this->text_.setString(std::to_string(*this->value_));

		if (!this->busy_)
		{
			if (this->IsOnBox())
			{
				this->Hightlight(true);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					std::thread([this] {

						this->busy_ = true;

						*value_ -= dec_;
						std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_duration_));

						this->busy_ = false;

						}).detach();
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
				{
					std::thread([this] {

						this->busy_ = true;

						*this->value_ += this->inc_;
						std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_duration_));

						this->busy_ = false;

						}).detach();
				}
			}
			else
				this->Hightlight(false);
		}
	}
}

void pItemFloat::AddValue(float& Value, float Inc, float Dec)
{
	this->value_ = &Value;
	this->inc_ = Inc;
	this->dec_ = Dec;
}

void pItemFloat::Loop()
{
	if (this->active_)
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(FLOAT_PRECISION) << std::stof(std::to_string(*value_));  // Convert string to std and remove obsolete zero's
		this->text_.setString(stream.str());

		if (!this->busy_)
		{
			if (IsOnBox())
			{
				this->Hightlight(true);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					std::thread([=]() {
						this->busy_ = true;

						*this->value_ -= this->dec_;
						std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_duration_));

						this->busy_ = false;

						}).detach();

				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
				{
					std::thread([=]() {
						this->busy_ = true;

						*this->value_ += this->inc_;
						std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_duration_));

						this->busy_ = false;

						}).detach();
				}
			}
			else
				this->Hightlight(false);
		}
	}
}

void pItemBool::AddValue(bool& Value)
{
	this->value_ = &Value;
	this->sleep_duration_ = 250;
}

void pItemBool::Loop()
{
	if (this->active_)
	{
		if (*value_)
			this->text_.setString("ON");
		else
			this->text_.setString("OFF");

		if (!this->busy_)
		{
			if (IsOnBox())
			{
				this->Hightlight(true);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
					std::thread([this] { 

						this->busy_ = true;

						*value_ = not *value_;
						std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_duration_));

						this->busy_ = false;

						}).detach();
					
			}
			else
				this->Hightlight(false);
		}
	}
}

void pItemString::AddValue(const std::string Value)
{
	this->value_ = Value;
}

void pItemString::Loop()
{
	if (this->active_)
	{
		this->text_.setString(this->value_);

		if (IsOnBox())
			this->Hightlight(true);
		else
			this->Hightlight(false);
	}
}