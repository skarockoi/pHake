#ifndef _PBUTTON_HPP_
#define _PBUTTON_HPP_

#include <SFML/Graphics.hpp>

class pButton
{
private:
	int sleepTime = 150;
	bool resize = true;
	bool active = false;

	void* function;

	sf::RenderWindow   *Window;
	sf::Font		   Font;
	sf::Vector2i	   Pos;
	sf::Vector2i	   Display;

	sf::RectangleShape buttonBack;
	sf::Text		   buttonName;

public:
	pButton() {}

	void create(sf::RenderWindow* const& window)
	{
		if (Window == 0)
		{
			Window = window;
			Font.loadFromFile("Settings/font.ttf");

			Pos.x = 0;
			Pos.y = 0;

			buttonBack.setSize(sf::Vector2f(80, 28));
			buttonBack.setPosition(Pos.x, Pos.y);
			buttonBack.setFillColor(sf::Color::Color(0, 0, 0, 150));
			buttonBack.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
			buttonBack.setOutlineThickness(1);

			buttonName.setFont(Font);
			buttonName.setCharacterSize(16);
			buttonName.setFillColor(sf::Color::Color(0, 0, 0, 255));
			buttonName.setPosition(Pos.x, Pos.y);

			this->setActive(true);
		}
	}

	void Loop()
	{
		if (this->isActive())
		{
			sf::Vector2i mouse = sf::Mouse::getPosition(*Window);
			if (this->isOnBox())
			{
				this->setHighlight(true);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					if (function != NULL)
					{
						((void(*)(void))function)();
						sf::sleep(sf::milliseconds(sleepTime));
					}
				}
			}
			else
			{
				this->setHighlight(false);
			}
		}
	}

	void draw()
	{
		if (this->active)
		{
			Window->draw(buttonBack);
			Window->draw(buttonName);
		}
	}

	void connect(void(&functionP)())
	{
		function = &functionP;
	}

	void setTimeout(int sleep)
	{
		sleepTime = sleep;
	}

public:
	sf::Vector2f getSize()
	{
		return buttonBack.getSize();
	}

	void setFont(sf::Font& font)
	{
		buttonName.setFont(font);
	}

	bool isActive()
	{
		return this->active;
	}

	void setText(std::string text)
	{
		buttonName.setString(" " + text);
		updateLength();
	}

	void setPosition(int x, int y)
	{
		buttonBack.setPosition(x, y + 1);
		buttonName.setPosition(x, y + (buttonBack.getSize().y / 4) - 5);
	}

	void setFixedSize(int x, int y)
	{
		if (!resize)
			resize = false;

		buttonBack.setSize(sf::Vector2f(x, y));
	}

private:
	void setActive(bool act)
	{
		active = act;
	}

	void setHighlight(bool value)
	{
		if (value)
			buttonBack.setOutlineColor(sf::Color::Color(255, 255, 255, 255));
		else
			buttonBack.setOutlineColor(sf::Color::Color(0, 0, 0, 0));
	}

	bool isOnBox()
	{
		sf::Vector2i mouse = sf::Mouse::getPosition(*Window);
		if (mouse.x >= buttonBack.getPosition().x &&						
			mouse.x <= buttonBack.getPosition().x + buttonBack.getSize().x &&
			mouse.y >= buttonBack.getPosition().y &&
			mouse.y <= buttonBack.getPosition().y + buttonBack.getSize().y)
			return true;
		else
			return false;
	}

	void updateLength()
	{
		if (resize)
		{
			sf::Vector2f rSize;
			rSize.x = ((float)std::string(buttonName.getString()).length() * 10) - (((std::string)buttonName.getString()).length() * 2);
			rSize.y = buttonBack.getSize().y;
			buttonBack.setSize(rSize);
		}
	}
};
#endif