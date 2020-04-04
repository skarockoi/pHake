#pragma once
#include <SFML/Graphics.hpp>
#include "lib/pButton.hpp"
#include "lib/pItem.hpp"
#include "lib/pList.hpp"
#include "lib/pMouse.hpp"
#include "lib/pNotification.hpp"
#pragma comment (lib, "Dwmapi.lib")

class pWindow
{
private:
	sf::RenderWindow Window;
	sf::Font		 Font;
	pMouse			 mouse;

public:
	pList			 list;
	pList			 listSettings;

	pWindow() {}


	void create()
	{
		Font.loadFromFile("Settings/font.ttf");

		Window.create(sf::VideoMode(208, 148), "pHake");
		Window.setFramerateLimit(60);

		list.create(&Window);
		list.setPostion(0, 0);
		list.toggle();

		listSettings.create(&Window);
		listSettings.setPostion(list.getPosition().x + listSettings.getSize().x + 5, list.getPosition().y);
		listSettings.toggle();
	}


	void loop()
	{
		while (Window.isOpen())
		{
			this->fixSize();
			sf::Event event;
			while (Window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					Window.close();

				if (event.type == sf::Event::Resized)
				{
					sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
					Window.setView(sf::View(visibleArea));
				}
			}

			list.loop();
			listSettings.loop();

			Window.clear(sf::Color::Color(255, 255, 255, 255));

			list.draw();
			listSettings.draw();

			Window.display();
		}
	}
private:
	void fixSize()
	{
		sf::Vector2f sizeList = list.getSize();
		sf::Vector2f sizeListSettings = listSettings.getSize();

		sf::Vector2u newSize;
		newSize.x = sizeList.x + sizeListSettings.x;

		if (sizeList.y > sizeListSettings.y)
			newSize.y = sizeList.y;

		else
			newSize.y = sizeListSettings.y;

		Window.setSize(newSize);
	}
};