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
	uint16_t sleepTime = 125;
	bool	 resize = false;
	bool	 active = false;
	bool     isExecuting = false;

	T* Value;
	T dec;
	T inc;

	sf::RenderWindow*  Window;
	sf::Font		   Font;
	sf::Vector2i	   Display;

	sf::RectangleShape rMain;
	sf::Text		   wMain;

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
inline void pItem<T>::create(sf::RenderWindow* const& window)
{
	if (Window == 0)
	{
		this->Window = window;
		this->Font.loadFromFile("Settings/font.ttf");

		this->rMain.setSize(sf::Vector2f(80, 28));
		this->rMain.setPosition(0, 0);
		this->rMain.setFillColor(sf::Color::Color(0, 0, 0, 0));
		this->rMain.setOutlineColor(sf::Color::Color(0, 0, 0, 0));
		this->rMain.setOutlineThickness(1);

		this->wMain.setFont(Font);
		this->wMain.setCharacterSize(16);
		this->wMain.setFillColor(sf::Color::Color(255, 255, 255, 255));
		this->wMain.setPosition(0, 0);

		this->setActive(true);
	}
}

template<typename T>
inline void pItem<T>::draw()
{
	if (this->isActive())
	{
		this->Window->draw(rMain);
		this->Window->draw(wMain);
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
	return wMain.getString();
}

template<typename T>
inline sf::Vector2f pItem<T>::getSize()
{
	return rMain.getSize();
}

template<typename T>
inline void pItem<T>::setFont(sf::Font& font)
{
	wMain.setFont(font);
}


template<typename T>
inline void pItem<T>::setText(const std::string& text)
{
	wMain.setString(text);
	updateLength();
}

template<typename T>
inline void pItem<T>::setFillColor(sf::Color color)
{
	wMain.setFillColor(color);
}

template<typename T>
inline void pItem<T>::setPosition(uint32_t x, uint32_t y)
{
	rMain.setPosition(x, y);
	wMain.setPosition(x, y + (rMain.getSize().y / 4) - 5);
}

template<typename T>
inline void pItem<T>::setFixedSize(uint32_t x, uint32_t y)
{
	if (!resize)
		resize = false;

	rMain.setSize(sf::Vector2f(x, y));
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
	sf::Vector2i mouse = sf::Mouse::getPosition(*Window);
	if (mouse.x > rMain.getPosition().x &&
		mouse.x < rMain.getPosition().x + rMain.getSize().x &&
		mouse.y > rMain.getPosition().y &&
		mouse.y < rMain.getPosition().y + rMain.getSize().y)
		return true;
	else
		return false;
}

template<typename T>
inline void pItem<T>::setHighlight(bool value)
{
	if (value)
		rMain.setOutlineColor(sf::Color::Color(255, 255, 255, 255));
	else
		rMain.setOutlineColor(sf::Color::Color(0, 0, 0, 0));
}

template<typename T>
inline void pItem<T>::updateLength()
{
	if (this->resize)
	{
		sf::Vector2f rSize;
		rSize.x = ((float)std::string(wMain.getString()).length() * 10) - (((std::string)wMain.getString()).length() * 2);
		rSize.y = rMain.getSize().y;
		rMain.setSize(rSize);
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

			if (!this->isExecuting)
			{ 
				if (isOnBox())
				{
					setHighlight(true);

					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						std::thread(&pItemFloat::decToValue, this).detach();

					}
					else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
					{
						std::thread(&pItemFloat::addToValue, this).detach();
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
		this->isExecuting = true;
		*Value += inc;
		std::this_thread::sleep_for(std::chrono::milliseconds(this->sleepTime));
		this->isExecuting = false;
	}
	void decToValue()
	{
		this->isExecuting = true;
		*Value -= dec;
		std::this_thread::sleep_for(std::chrono::milliseconds(this->sleepTime));
		this->isExecuting = false;
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

			if (!this->isExecuting)
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
		this->isExecuting = true;
		*Value += inc;
		std::this_thread::sleep_for(std::chrono::milliseconds(this->sleepTime));
		this->isExecuting = false;
	}
	void decToValue()
	{
		this->isExecuting = true;
		*Value -= dec;
		std::this_thread::sleep_for(std::chrono::milliseconds(this->sleepTime));
		this->isExecuting = false;
	}
};

class pItemBool : public pItem<bool>
{
public:
	pItemBool() {
		this->sleepTime = 250;
	}

	void loop()
	{
		if (this->isActive())
		{
			if (*Value)
				this->setText("ON");

			else
				this->setText("OFF");

			if (!this->isExecuting)
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
		this->isExecuting = true;
		*Value = not *Value;
		std::this_thread::sleep_for(std::chrono::milliseconds(this->sleepTime));
		this->isExecuting = false;
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
