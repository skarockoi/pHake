#ifndef _PBUTTON_HPP_
#define _PBUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <thread>

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

	sf::RectangleShape rMain;
	sf::Text		   wMain;

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

			rMain.setSize(sf::Vector2f(80, 28));
			rMain.setPosition(Pos.x, Pos.y);
			rMain.setFillColor(sf::Color::Color(0, 0, 0, 150));
			rMain.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
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
			Window->draw(rMain);
			Window->draw(wMain);
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
	bool isActive()
	{
		return this->active;
	}

	void setText(std::string text)
	{
		wMain.setString(" " + text);
		updateLength();
	}

	void setPostion(int x, int y)
	{
		rMain.setPosition(x, y + 1);
		wMain.setPosition(x, y + (rMain.getSize().y / 4) - 5);
	}

	void setFixedSize(int x, int y)
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

	void setHighlight(bool value)
	{
		if (value)
			rMain.setOutlineColor(sf::Color::Color(255, 255, 255, 255));
		else
			rMain.setOutlineColor(sf::Color::Color(0, 0, 0, 0));
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