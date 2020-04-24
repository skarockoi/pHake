#ifndef _PITEM_HPP_
#define _PITEM_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>  
#include <iomanip>
#include <thread>

template <typename T> class pItem // No.1 reason why templates arent the best choice sometimes
{
protected:
	uint16_t sleep_time = 125;
	bool	 resize = false;
	bool	 active = false;
	bool     busy = false;

	T* Value;
	T  dec;
	T  inc;

	sf::RenderWindow*  window;
	sf::Font		   font;

	sf::Text		   text;
	sf::RectangleShape rect_back;

public:
	void		 create(sf::RenderWindow* const& window);
	void		 draw();
	virtual void loop() = 0;

	void		 addPtr(T& value, T Inc, T Dec);
	void		 addPtr(T& value);
	std::string  getText();
	sf::Vector2f getSize();
	void		 setFont(sf::Font &font);
	void		 setText(const std::string &text);
	void		 setFillColor(sf::Color color);
	void		 setPosition(uint32_t x, uint32_t y);
	void		 setFixedSize(uint32_t x, uint32_t y);

protected:
	bool         isActive();
	void         setActive(bool act);
	bool         isOnBox();
	void         setHighlight(bool value);
	void         updateLength();
};

template<typename T>
inline void pItem<T>::create(sf::RenderWindow* const& Window)
{
	this->window = Window;
	this->font.loadFromFile("Settings/font.ttf");

	this->rect_back.setSize(sf::Vector2f(80, 28));
	this->rect_back.setPosition(0, 0);
	this->rect_back.setFillColor(sf::Color::Color(0, 0, 0, 0));
	this->rect_back.setOutlineColor(sf::Color::Color(0, 0, 0, 0));
	this->rect_back.setOutlineThickness(1);

	this->text.setFont(font);
	this->text.setCharacterSize(16);
	this->text.setFillColor(sf::Color::Color(255, 255, 255, 255));
	this->text.setPosition(0, 0);

	this->setActive(true);
}

template<typename T>
inline void pItem<T>::draw()
{
	if (this->isActive())
	{
		this->window->draw(rect_back);
		this->window->draw(text);
	}
}

template<typename T>
inline void pItem<T>::addPtr(T& value, T Inc, T Dec)
{
	Value = &value;
	inc = Inc;
	dec = Dec;
}

template<typename T>
inline void pItem<T>::addPtr(T& value)
{
	Value = &value;
}

template<typename T>
inline std::string pItem<T>::getText()
{
	return text.getString();
}

template<typename T>
inline sf::Vector2f pItem<T>::getSize()
{
	return rect_back.getSize();
}

template<typename T>
inline void pItem<T>::setFont(sf::Font& font)
{
	text.setFont(font);
}


template<typename T>
inline void pItem<T>::setText(const std::string& Text)
{
	text.setString(Text);
	updateLength();
}

template<typename T>
inline void pItem<T>::setFillColor(sf::Color color)
{
	text.setFillColor(color);
}

template<typename T>
inline void pItem<T>::setPosition(uint32_t x, uint32_t y)
{
	rect_back.setPosition(x, y);
	text.setPosition(x, y + (rect_back.getSize().y / 4) - 5);
}

template<typename T>
inline void pItem<T>::setFixedSize(uint32_t x, uint32_t y)
{
	if (!resize)
		resize = false;

	rect_back.setSize(sf::Vector2f(x, y));
}

template<typename T>
inline bool pItem<T>::isActive()
{
	return this->active;
}

template<typename T>
inline void pItem<T>::setActive(bool act)
{
	active = act;
}

template<typename T>
inline bool pItem<T>::isOnBox()
{
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	if (mouse.x > rect_back.getPosition().x &&
		mouse.x < rect_back.getPosition().x + rect_back.getSize().x &&
		mouse.y > rect_back.getPosition().y &&
		mouse.y < rect_back.getPosition().y + rect_back.getSize().y)
		return true;
	else
		return false;
}

template<typename T>
inline void pItem<T>::setHighlight(bool value)
{
	if (value)
		rect_back.setOutlineColor(sf::Color::Color(255, 255, 255, 255));
	else
		rect_back.setOutlineColor(sf::Color::Color(0, 0, 0, 0));
}

template<typename T>
inline void pItem<T>::updateLength()
{
	if (this->resize)
	{
		sf::Vector2f rSize;
		rSize.x = ((float)std::string(text.getString()).length() * 10) - (((std::string)text.getString()).length() * 2);
		rSize.y = rect_back.getSize().y;
		rect_back.setSize(rSize);
	}
}

#endif

#ifndef _PITEMTYPES_HPP_
#define _PITEMTYPES_HPP_

class pItemFloat : public pItem<float>
{
private:
	uint8_t  precision = 1;

public:
	pItemFloat() {}

	void loop()
	{
		if (this->isActive())
		{
			std::stringstream stream;
			stream << std::fixed << std::setprecision(this->precision) << std::stof(std::to_string(*Value));  // Convert string to std and remove obsolete zero's
			setText(stream.str());

			if (!this->busy)
			{ 
				if (isOnBox())
				{
					setHighlight(true);

					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						std::thread([=]() {
							this->busy = true;

							*Value -= dec;
							std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_time));

							this->busy = false;
							}).detach();

					}
					else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
					{
						std::thread([=]() {
							this->busy = true;

							*Value += inc;
							std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_time));

							this->busy = false;
							}).detach();
					}
				}
				else
				{
					setHighlight(false);
				}
			}
		}
	}
public:
	void setPrecision(uint8_t value)
	{
		this->precision = value;
	}
};

class pItemInt : public pItem<int32_t>
{
public:
	pItemInt() {}

	void loop()
	{
		if (this->isActive())
		{
			setText(std::to_string(*Value));

			if (!this->busy)
			{
				if (isOnBox())
				{
					setHighlight(true);

					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						std::thread(&pItemInt::decToValue, this).detach();
					}
					else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
					{
						std::thread(&pItemInt::addToValue, this).detach();
					}
				}
				else
				{
					setHighlight(false);
				}
			}
		}
	}
private:
	void addToValue()
	{
		this->busy = true;
		*Value += inc;
		std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_time));
		this->busy = false;
	}
	void decToValue()
	{
		this->busy = true;
		*Value -= dec;
		std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_time));
		this->busy = false;
	}
};

class pItemBool : public pItem<bool>
{
public:
	pItemBool() {
		this->sleep_time = 250;
	}

	void loop()
	{
		if (this->isActive())
		{
			if (*Value)
				this->setText("ON");

			else
				this->setText("OFF");

			if (!this->busy)
			{
				if (isOnBox())
				{
					this->setHighlight(true);

					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
					{
						 std::thread(&pItemBool::flipBool, this).detach(); 
					}
				}
				else
				{
					this->setHighlight(false);
				}
			}

		}
	}
private:
	void flipBool()
	{
		this->busy = true;
		*Value = not *Value;
		std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_time));
		this->busy = false;
	}
};

class pItemString : public pItem<std::string>
{
public:
	pItemString() {}

	void loop()
	{
		if (this->isActive())
		{
			this->setText(*Value);

			if (isOnBox())
			{
				this->setHighlight(true);

			}
			else
			{
				this->setHighlight(false);
			}
		}
	}
};
#endif
