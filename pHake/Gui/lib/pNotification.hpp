#ifndef _PNOTIFICATION_HPP_
#define _PNOTIFICATION_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <vector>

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
		tempBone.back.setFillColor(sf::Color::Color(0, 0, 0, 200));
		tempBone.back.setOutlineColor(sf::Color::Color(0, 0, 0, 200));
		tempBone.back.setOutlineThickness(1);

		tempBone.text.setFont(Font);
		tempBone.text.setCharacterSize(16);
		tempBone.text.setFillColor(sf::Color::Color(255, 255, 255, 200));
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

					for (int b = 200; b > 0; b--)
					{
						notifications[i].back.setFillColor(sf::Color(0, 0, 0, b));
						notifications[i].back.setOutlineColor(sf::Color(0, 0, 0, b));
						notifications[i].text.setFillColor(sf::Color(255, 255, 255, b));

						sf::sleep(sf::milliseconds(4));
					}
					notifications[i].finished = true;
				}
			}
		}
	}
};


#endif

