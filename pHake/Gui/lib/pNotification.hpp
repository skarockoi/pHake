#ifndef _PNOTIFICATION_HPP_
#define _PNOTIFICATION_HPP_

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string>
#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>

class plNotification
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

	plNotification(){}

	void create(sf::RenderWindow* const& window)
	{
		if (Window == 0)
		{
			Window = window;
			Font.loadFromFile("Settings/font.ttf");
			t = (std::thread(&plNotification::Loop, this));
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

class pNotification
{
private:
	struct Bone
	{
		sf::Text text;
		sf::RectangleShape back;
		bool finished;
	};

	sf::RenderWindow* Window;
	sf::Font		  Font;
	sf::Vector2i	  Pos;
	std::vector<Bone> notifications;

	std::thread       t;

public:
	void create(sf::RenderWindow* const& window)
	{
		Pos.x = 15;
		Pos.y = 20;
		if (Window == 0)
		{
			Window = window;
			Font.loadFromFile("Settings/font.ttf");
			t = (std::thread(&pNotification::Loop, this));
		}
	}

	void add(std::string name)
	{
		Bone tempBone;
		tempBone.finished = false;
		tempBone.back.setSize(sf::Vector2f(210, 20));
		tempBone.back.setPosition(Pos.x + 10, Pos.y + (notifications.size() * 25));
		tempBone.back.setFillColor(sf::Color::Color(0, 0, 0, 255));
		tempBone.back.setOutlineColor(sf::Color::Color(0, 0, 0));
		tempBone.back.setOutlineThickness(1);

		tempBone.text.setFont(Font);
		tempBone.text.setCharacterSize(16);
		tempBone.text.setFillColor(sf::Color::Color(255, 255, 255, 255));
		tempBone.text.setPosition(tempBone.back.getPosition().x, tempBone.back.getPosition().y);
		tempBone.text.setString(name);

		notifications.push_back(tempBone);
		
	}

	void draw()
	{
		for (int i = 0; i < notifications.size(); i++)
		{
			if (!notifications[i].finished)
			{
				Window->draw(notifications[i].back);
				Window->draw(notifications[i].text);
			}
		}
	}

	void Loop()
	{
		while (true)
		{
			Sleep(1);

			for (int i = 0; i < notifications.size(); i++)
			{
				if (notifications[i].finished)
				{
					notifications.erase(notifications.begin());

				}

				if (!notifications[i].finished)
				{
					for (int b = 255; b > 0; b--)
					{
						notifications[i].back.setFillColor(sf::Color(0, 0, 0, b));
						notifications[i].back.setOutlineColor(sf::Color(0, 0, 0, b));
						notifications[i].text.setFillColor(sf::Color(255, 255, 255, b));

						sf::sleep(sf::milliseconds(3));
					}

					notifications[i].finished = true;
				}
			}
		}
	}
};


#endif

