#ifndef _PITEM_HPP_
#define _PITEM_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>  
#include <iomanip>
#include <thread>

template <typename T> class pItem
{
protected:
	uint16_t sleep_time_ = 125;
	bool	 resizeable_ = false;
	bool	 active_ = false;
	bool     busy_ = false;

	T* value_;
	T  dec_;
	T  inc_;

	sf::RenderWindow*  window_;
	sf::Font		   font_;

	sf::Text		   text_;
	sf::RectangleShape rect_back_;

public:
	void		 Create(sf::RenderWindow* const& window);
	void		 Draw();
	virtual void Loop() = 0;

	void		 AddPtr(T& value, T Inc, T Dec);
	void		 AddPtr(T& value);
	std::string  text();
	sf::Vector2f size();
	void		 font(sf::Font &font);
	void		 text(const std::string &text);
	void		 fill_color(sf::Color color);
	void		 position(uint32_t x, uint32_t y);
	void		 size(uint32_t x, uint32_t y);

protected:
	bool         active();
	void         active(bool act);
	bool         IsOnBox();
	void         highlight(bool value);
	void         length();
};

template<typename T>
inline void pItem<T>::Create(sf::RenderWindow* const& Window)
{
	this->window_ = Window;
	this->font_.loadFromFile("Settings/font.ttf");

	this->rect_back_.setSize(sf::Vector2f(80, 28));
	this->rect_back_.setPosition(0, 0);
	this->rect_back_.setFillColor(sf::Color::Color(0, 0, 0, 0));
	this->rect_back_.setOutlineColor(sf::Color::Color(0, 0, 0, 0));
	this->rect_back_.setOutlineThickness(1);

	this->text_.setFont(font_);
	this->text_.setCharacterSize(16);
	this->text_.setFillColor(sf::Color::Color(255, 255, 255, 255));
	this->text_.setPosition(0, 0);

	this->active(true);
}

template<typename T>
inline void pItem<T>::Draw()
{
	if (this->active())
	{
		this->window_->draw(rect_back_);
		this->window_->draw(text_);
	}
}

template<typename T>
inline void pItem<T>::AddPtr(T& value, T Inc, T Dec)
{
	value_ = &value;
	inc_ = Inc;
	dec_ = Dec;
}

template<typename T>
inline void pItem<T>::AddPtr(T& value)
{
	value_ = &value;
}

template<typename T>
inline std::string pItem<T>::text()
{
	return text_.getString();
}

template<typename T>
inline sf::Vector2f pItem<T>::size()
{
	return rect_back_.getSize();
}

template<typename T>
inline void pItem<T>::font(sf::Font& font)
{
	text_.setFont(font);
}


template<typename T>
inline void pItem<T>::text(const std::string& Text)
{
	text_.setString(Text);
	length();
}

template<typename T>
inline void pItem<T>::fill_color(sf::Color color)
{
	text_.setFillColor(color);
}

template<typename T>
inline void pItem<T>::position(uint32_t x, uint32_t y)
{
	rect_back_.setPosition(x, y);
	text_.setPosition(x, y + (rect_back_.getSize().y / 4) - 5);
}

template<typename T>
inline void pItem<T>::size(uint32_t x, uint32_t y)
{
	if (!resizeable_)
		resizeable_ = false;

	rect_back_.setSize(sf::Vector2f(x, y));
}

template<typename T>
inline bool pItem<T>::active()
{
	return this->active_;
}

template<typename T>
inline void pItem<T>::active(bool act)
{
	active_ = act;
}

template<typename T>
inline bool pItem<T>::IsOnBox()
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

template<typename T>
inline void pItem<T>::highlight(bool value)
{
	if (value)
		rect_back_.setOutlineColor(sf::Color::Color(255, 255, 255, 255));
	else
		rect_back_.setOutlineColor(sf::Color::Color(0, 0, 0, 0));
}

template<typename T>
inline void pItem<T>::length()
{
	if (this->resizeable_)
	{
		sf::Vector2f rSize;
		rSize.x = ((float)std::string(text_.getString()).length() * 10) - (((std::string)text_.getString()).length() * 2);
		rSize.y = rect_back_.getSize().y;
		rect_back_.setSize(rSize);
	}
}

#endif

#ifndef _PITEMTYPES_HPP_
#define _PITEMTYPES_HPP_

class pItemFloat : public pItem<float>
{
private:
	uint8_t  precision_ = 1;

public:
	pItemFloat() {}

	void Loop()
	{
		if (this->active())
		{
			std::stringstream stream;
			stream << std::fixed << std::setprecision(this->precision_) << std::stof(std::to_string(*value_));  // Convert string to std and remove obsolete zero's
			text(stream.str());

			if (!this->busy_)
			{ 
				if (IsOnBox())
				{
					highlight(true);

					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						std::thread([=]() {
							this->busy_ = true;

							*value_ -= dec_;
							std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_time_));

							this->busy_ = false;
							}).detach();

					}
					else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
					{
						std::thread([=]() {
							this->busy_ = true;

							*value_ += inc_;
							std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_time_));

							this->busy_ = false;
							}).detach();
					}
				}
				else
				{
					highlight(false);
				}
			}
		}
	}
public:
	void precision(uint8_t value)
	{
		this->precision_ = value;
	}
};

class pItemInt : public pItem<int32_t>
{
public:
	pItemInt() {}

	void Loop()
	{
		if (this->active())
		{
			text(std::to_string(*value_));

			if (!this->busy_)
			{
				if (IsOnBox())
				{
					highlight(true);

					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						std::thread(&pItemInt::DecToValue, this).detach();
					}
					else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
					{
						std::thread(&pItemInt::AddToValue, this).detach();
					}
				}
				else
				{
					highlight(false);
				}
			}
		}
	}
private:
	void AddToValue()
	{
		this->busy_ = true;
		*value_ += inc_;
		std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_time_));
		this->busy_ = false;
	}
	void DecToValue()
	{
		this->busy_ = true;
		*value_ -= dec_;
		std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_time_));
		this->busy_ = false;
	}
};

class pItemBool : public pItem<bool>
{
public:
	pItemBool() {
		this->sleep_time_ = 250;
	}

	void Loop()
	{
		if (this->active())
		{
			if (*value_)
				this->text("ON");

			else
				this->text("OFF");

			if (!this->busy_)
			{
				if (IsOnBox())
				{
					this->highlight(true);

					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
					{
						 std::thread(&pItemBool::flip_bool, this).detach(); 
					}
				}
				else
				{
					this->highlight(false);
				}
			}

		}
	}
private:
	void flip_bool()
	{
		this->busy_ = true;
		*value_ = not *value_;
		std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_time_));
		this->busy_ = false;
	}
};

class pItemString : public pItem<std::string>
{
public:
	pItemString() {}

	void Loop()
	{
		if (this->active())
		{
			this->text(*value_);

			if (IsOnBox())
			{
				this->highlight(true);

			}
			else
			{
				this->highlight(false);
			}
		}
	}
};
#endif