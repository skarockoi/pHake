#ifndef _PNOTIFICATION_HPP_
#define _PNOTIFICATION_HPP_

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string>
#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>

class pNotification
{
public:
	sf::RenderWindow* Window;
	sf::Font		  Font;
	sf::Vector2i	  Pos;
	std::thread		  t;
	uint8_t			  count = 0;

	class Text : public sf::Text
	{
	public:
		Text() {}

		Text(std::string string, sf::Font* font, sf::Color color, int x, int y, int size)
		{
			setString(string);
			setFillColor(color);
			setCharacterSize(size);
			setPosition(x, y);
			setFont(*font);
		}
	};
	class Rectangle : public sf::RectangleShape
	{
	public:
		Rectangle() {}

		Rectangle(int x, int y, int pos_x, int pos_y, sf::Color color_in, sf::Color color_out)
		{
			setSize(sf::Vector2f(x, y));
			setPosition(pos_x, pos_y);
			setFillColor(color_in);
			setOutlineColor(color_out);
			setOutlineThickness(1);
		}
	};


	struct n
	{
		Text text;
		Rectangle rect;
		bool enabled;

	}n[128];

	pNotification(){}

	void create(sf::RenderWindow* const& window)
	{
		if (Window == 0)
		{
			Window = window;
			Font.loadFromFile("Settings/font.ttf");
			t = (std::thread(&pNotification::Loop, this));
		}
	}

	void add(std::string name)
	{
		Pos.x = 15;
		Pos.y = 20;

		n[count].enabled = true;

		n[count].rect = Rectangle(210, 20, Pos.x, Pos.y + (count * 25), sf::Color::Color(0, 0, 0, 150), sf::Color(0, 0, 0));
		n[count].text = Text(" " + name, &Font ,sf::Color::White, Pos.x, Pos.y + (count * 25) , 16);

		count++;
	}

	void draw()
	{
		for (int i = 0; i <= 127; i++)
		{
			if (n[i].enabled)
			{
				Window->draw(n[i].rect);
				Window->draw(n[i].text);
			}
		}
	}
	void Loop()
	{
		while (true)
		{
			Sleep(1);
			for (int i = 0; i < 127; i++)
			{
				if (n[i].enabled)
				{
					sf::sleep(sf::milliseconds(1000));
					n[i].enabled = false;
				}
				else if (count > 0)
				{
					count--;
				}
			}
		}
	}
};
#endif