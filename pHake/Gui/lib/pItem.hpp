#ifndef _PITEM_HPP_
#define _PITEM_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>  

template <typename T> class pItem
{
private:
	uint16_t sleepTime = 125;
	bool resize = false;
	bool active = false;

	T* tValue;
	T tInc;
	T tDec;

	sf::RenderWindow* Window;
	sf::Font		  Font;
	sf::Vector2i	  Pos;
	sf::Vector2i	  Display;

	sf::RectangleShape rMain;
	sf::Text		   wMain;

public:
	pItem() {}

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
			wMain.setFillColor(sf::Color::Color(0, 0, 0, 255));
			wMain.setPosition(Pos.x, Pos.y);

			this->setActive(true);
		}
	}

	void Loop()
	{
		if (this->isActive())
		{
			if (typeid(T) == typeid(float)) // String check
			{
				std::stringstream stream;
				stream << std::fixed << std::setprecision(1) << std::stof(std::to_string(*tValue));  // Convert string to std and remove obsolete zero's

				setText(stream.str());
			}
			else if (typeid(T) == typeid(bool))
			{
				if (*tValue)
					setText("ON");

				else
					setText("OFF");
			}
			else
				setText(std::to_string(*tValue));


			if (isOnBox())
			{
				setHighlight(true);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					if (typeid(T) == typeid(bool))
						*tValue = not *tValue;

					else
						*tValue -= tDec;

					sf::sleep(sf::milliseconds(sleepTime));

				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
				{
					if (typeid(T) == typeid(bool))
						*tValue = not *tValue;

					else
					{
						*tValue += tInc;
					}
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
	bool isActive()
	{
		return this->active;
	}

	void addPtr(T& value, T inc, T dec)
	{
		tValue = &value;
		tInc = inc;
		tDec = dec;
	}

	void setText(std::string text)
	{
		wMain.setString(text);
		updateLength();
	}

	void setFillColor(sf::Color color)
	{
		wMain.setFillColor(color);
	}

	void setPostion(uint16_t x, uint16_t y)
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

private:
	void setActive(bool act)
	{
		active = act;
	}

	bool isOnBox()
	{
		sf::Vector2i mouse = sf::Mouse::getPosition(*Window);
		if (mouse.x >= rMain.getPosition().x &&						// Check if Mouse is on button
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
		if (resize)
		{
			sf::Vector2f rSize;
			rSize.x = ((float)std::string(wMain.getString()).length() * 10) - (((std::string)wMain.getString()).length() * 2);
			rSize.y = rMain.getSize().y;
			rMain.setSize(rSize);
		}
	}
};
#endif