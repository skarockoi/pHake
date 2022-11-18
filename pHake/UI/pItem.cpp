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

pItemBone::pItemBone() : 
	window_(0),
	font_(),
	text_(),
	rect_back_({0,0}),
	sleep_duration_(0),
	resizeable_(false),
	active_(false),
	busy_(false)
{ }

void pItemBone::Create(sf::RenderWindow* const& Window, sf::Font* Font)
{
	window_ = Window;
	font_ = Font;

	rect_back_.setSize(sf::Vector2f(BACK_WIDTH - 1, BACK_HEIGHT - 1));
	rect_back_.setPosition(0, 0);
	rect_back_.setFillColor(BACK_COLOR);
	rect_back_.setOutlineColor(BACK_COLOR_OUTLINE);
	rect_back_.setOutlineThickness(1);

	text_.setFont(*font_);
	text_.setCharacterSize(TEXT_SIZE);
	text_.setFillColor(TEXT_COLOR);
	text_.setPosition(0, 0);

	sleep_duration_ = SLEEP_DURATION;
	active_ = true;
}

void pItemBone::Draw()
{
	if (active_)
	{
		window_->draw(rect_back_);
		window_->draw(text_);
	}
}

void pItemBone::Hightlight(bool value)
{
	if (value && rect_back_.getOutlineColor() != HIGHLIGHT_COLOR)
		rect_back_.setOutlineColor(HIGHLIGHT_COLOR);
	else if (!value && rect_back_.getOutlineColor() == HIGHLIGHT_COLOR)
		rect_back_.setOutlineColor(BACK_COLOR_OUTLINE);
}

void pItemBone::position(sf::Vector2f xy)
{
	rect_back_.setPosition(xy.x, xy.y);
	text_.setPosition(xy.x, xy.y + (rect_back_.getSize().y / 4) - 5);
}

void pItemBone::size(sf::Vector2f xy)
{
	if (!resizeable_)
		resizeable_ = false;

	rect_back_.setSize(sf::Vector2f(xy.x, xy.y));
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
	value_ = &Value;
	inc_ = Inc;
	dec_ = Dec;
}

void pItemInt::Loop()
{
	if (!active_) 
		return;
	
	text_.setString(std::to_string(*value_));

	if (busy_) 
		return;
	
	if (!IsOnBox())
	{
		Hightlight(false);
		return;
	}

	Hightlight(true);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		std::thread([this] {

			busy_ = true;

			*value_ -= dec_;
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration_));

			busy_ = false; }).detach();
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		std::thread([this] {

			busy_ = true;

			*value_ += inc_;
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration_));

			busy_ = false; }).detach();
	}
}

void pItemFloat::AddValue(float& Value, float Inc, float Dec)
{
	value_ = &Value;
	inc_ = Inc;
	dec_ = Dec;
}

void pItemFloat::Loop()
{
	if (!active_)
		return;

	std::stringstream stream;
	stream << std::fixed << std::setprecision(FLOAT_PRECISION) << std::stof(std::to_string(*value_));  // Convert string to std and remove obsolete zero's
	text_.setString(stream.str());

	if (busy_)
		return;

	if (!IsOnBox())
	{
		Hightlight(false);
		return;
	}

	Hightlight(true);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		std::thread([=]() {
			busy_ = true;

			*value_ -= dec_;
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration_));

			busy_ = false; }).detach();

	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		std::thread([=]() {
			busy_ = true;

			*value_ += inc_;
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration_));

			busy_ = false; }).detach();
	}
}

void pItemBool::AddValue(bool& Value)
{
	value_ = &Value;
	sleep_duration_ = 250;
}

void pItemBool::Loop()
{
	if (!active_)
		return;

	if (*value_)
		text_.setString("ON");
	else
		text_.setString("OFF");

	if (busy_)
		return;

	if (!IsOnBox())
	{
		Hightlight(false);
		return;
	}

	Hightlight(true);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		std::thread([this] {

		busy_ = true;

		*value_ = not *value_;
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration_));

		busy_ = false; }).detach();
}

void pItemString::AddValue(const std::string Value)
{
	value_ = Value;
}

void pItemString::Loop()
{
	if (!active_)
		return;

	text_.setString(value_);

	if (IsOnBox())
		Hightlight(true);
	else
		Hightlight(false);
}