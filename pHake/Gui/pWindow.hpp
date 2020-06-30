#pragma once
#include <SFML/Graphics.hpp>
#include "lib/pButton.hpp"
#include "lib/pItem.hpp"
#include "lib/pList.hpp"
#include "lib/pMouse.hpp"
#pragma comment (lib, "Dwmapi.lib")

class pWindow
{
private:
	sf::RenderWindow window;
	sf::Font		 font;
	pMouse			 mouse;

public:
	pList			 list;
	pList			 list_settings;

	void create()
	{
		font.loadFromFile("Settings/font.ttf");

		window.create(sf::VideoMode(208, 148), "pHake");
		window.setFramerateLimit(60);

		list.create(&window);
		list.setPosition(0, 0);
		list.toggle();

		list_settings.create(&window);
		list_settings.setPosition(list.getPosition().x + list_settings.getSize().x + 5, list.getPosition().y);
		list_settings.toggle();
	}

	void loop()
	{
		while (window.isOpen())
		{
			this->fixSize();
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::Resized)
				{
					sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
					window.setView(sf::View(visibleArea));
				}
			}

			list.loop();
			list_settings.loop();

			window.clear(sf::Color::Color(255, 255, 255, 255));

			list.draw();
			list_settings.draw();

			window.display();
		}
	}
private:
	void fixSize()
	{
		sf::Vector2f size_list = list.getSize();
		sf::Vector2f size_list_settings = list_settings.getSize();

		sf::Vector2u new_size;
		new_size.x = size_list.x + size_list_settings.x;

		if (size_list.y > size_list_settings.y)
			new_size.y = size_list.y;

		else
			new_size.y = size_list_settings.y;

		window.setSize(new_size);
	}
};