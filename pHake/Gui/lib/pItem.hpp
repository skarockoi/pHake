#ifndef _PITEM_HPP_
#define _PITEM_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>  
#include <iomanip>

template <typename T> class pItem
{
protected:
	uint16_t sleepTime = 125;
	bool resize = false;
	bool active = false;

	T* Value;
	T dec;
	T inc;

	sf::RenderWindow* Window;
	sf::Font		  Font;
	sf::Vector2i	  Pos;
	sf::Vector2i	  Display;

	sf::RectangleShape rMain;
	sf::Text		   wMain;

public:
	void create(sf::RenderWindow* const& window)
	{
		if (Window == 0)
		{
			Window = window;
			Font.loadFromFile("Settings/font.ttf");

			Pos.x = 0;
			Pos.y = 0;

			rMain.setSize(sf::Vector2f(80, 28));
			rMain.setPosition(Pos.x, Pos.y);
			rMain.setFillColor(sf::Color::Color(0, 0, 0, 0));
			rMain.setOutlineColor(sf::Color::Color(0, 0, 0, 0));
			rMain.setOutlineThickness(1);

			wMain.setFont(Font);
			wMain.setCharacterSize(16);
			wMain.setFillColor(sf::Color::Color(255, 255, 255, 255));
			wMain.setPosition(Pos.x, Pos.y);

			this->setActive(true);
		}
	}

	virtual void loop() = 0;

	void draw()
	{
		if (this->isActive())
		{
			Window->draw(rMain);
			Window->draw(wMain);
		}
	}

	bool isActive()
	{
		return this->active;
	}

	void addPtr(T& value, T Inc, T Dec)
	{
		Value = &value;
		inc = Inc;
		dec = Dec;
	}

	void addPtr(T& value)
	{
		Value = &value;
	}

	std::string getText()
	{
		return wMain.getString();
	}

	sf::Vector2f getSize()
	{
		return rMain.getSize();
	}

	void setFont(sf::Font &font)
	{
		wMain.setFont(font);
	}

	sf::Font getFont()
	{
		return wMain.getFont();
	}

	void setText(const std::string &text)
	{
		wMain.setString(text);
		updateLength();
	}

	void setFillColor(sf::Color color)
	{
		wMain.setFillColor(color);
	}

	void setPosition(uint16_t x, uint16_t y)
	{
		rMain.setPosition(x, y);
		wMain.setPosition(x, y + (rMain.getSize().y / 4) - 5);
	}

	void setFixedSize(uint16_t x, uint16_t y)
	{
		if (!resize)
			resize = false;

		rMain.setSize(sf::Vector2f(x, y));
	}
protected:
	void setActive(bool act)
	{
		active = act;
	}

	bool isOnBox()
	{
		sf::Vector2i mouse = sf::Mouse::getPosition(*Window);
		if (mouse.x >= rMain.getPosition().x &&
			mouse.x <= rMain.getPosition().x + rMain.getSize().x &&
			mouse.y >= rMain.getPosition().y &&
			mouse.y <= rMain.getPosition().y + rMain.getSize().y)
			return true;
		else
			return false;
	}

	void setHighlight(bool value)
	{
		if (value)
			rMain.setOutlineColor(sf::Color::Color(255, 255, 255, 255));
		else
			rMain.setOutlineColor(sf::Color::Color(0, 0, 0, 0));
	}

	void updateLength()
	{
		if (this->resize)
		{
			sf::Vector2f rSize;
			rSize.x = ((float)std::string(wMain.getString()).length() * 10) - (((std::string)wMain.getString()).length() * 2);
			rSize.y = rMain.getSize().y;
			rMain.setSize(rSize);
		}
	}
};


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

			if (isOnBox())
			{
				setHighlight(true);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					*Value -= dec;
					sf::sleep(sf::milliseconds(sleepTime));
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
				{
					*Value += inc;
					sf::sleep(sf::milliseconds(sleepTime));
				}
			}
			else
			{
				setHighlight(false);
			}
		}
	}

	void draw()
	{
		if (this->isActive())
		{
			Window->draw(rMain);
			Window->draw(wMain);
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

			if (isOnBox())
			{
				setHighlight(true);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					*Value -= dec;
					sf::sleep(sf::milliseconds(sleepTime));
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
				{
					*Value += inc;
					sf::sleep(sf::milliseconds(sleepTime));
				}
			}
			else
			{
				setHighlight(false);
			}
		}
	}
};

class pItemBool : public pItem<bool>
{
public:
	pItemBool() {}

	void loop()
	{
		if (this->isActive())
		{
			if (*Value)
				this->setText("ON");

			else
				this->setText("OFF");

			if (isOnBox())
			{
				this->setHighlight(true);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					*Value = not *Value;
					sf::sleep(sf::milliseconds(sleepTime));

				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
				{
					*Value = not *Value;
					sf::sleep(sf::milliseconds(sleepTime));
				}
			}
			else
			{
				this->setHighlight(false);
			}
		}
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
