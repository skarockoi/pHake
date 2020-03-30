#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string>
#include <iostream>
#include <filesystem>
#include <Dwmapi.h>
#include <thread>
#include <vector>
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
	pNotification    notification;

	pWindow(){}


	void createWindow()
	{
		Font.loadFromFile("Settings/font.ttf");

		Window.create(sf::VideoMode(208, 148), "pHake 4.0");
		Window.setFramerateLimit(60);

		notification.create(&Window);
		list.create(&Window);
		list.setPostion(0, 0);
	}


	void loop()
	{
		while (Window.isOpen())
		{
			sf::Vector2f newSizef = list.getSize();
			sf::Vector2u newSizeU;
			newSizeU.x = list.getSize().x + 1;
			newSizeU.y = list.getSize().y - 1;
			Window.setSize(newSizeU);

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

			Window.clear(sf::Color::Color(255, 255, 255, 255));

			list.draw();
			notification.draw();

			Window.display();
		}
	}
};