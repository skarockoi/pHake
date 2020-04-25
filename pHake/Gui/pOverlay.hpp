#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <Dwmapi.h>
#include <vector>
#include "lib/pButton.hpp"
#include "lib/pItem.hpp"
#include "lib/pList.hpp"
#include "lib/pMouse.hpp"
#include "lib/pNotificationCenter.hpp"
#pragma comment (lib, "Dwmapi.lib")

struct GameInfo
{
private:
	HWND hwnd;
	RECT rect;
	LPCSTR game;
	sf::Vector2i pos;
	sf::Vector2u size;

public:
	GameInfo() {}

	GameInfo(LPCSTR Game)
	{
		game = Game;
		hwnd = FindWindowA(0, Game);
		GetWindowRect(hwnd, &rect);

		pos = this->getPosition();
		size = this->getSize();
	}

	void update()
	{
		hwnd = FindWindowA(0, game);
		GetWindowRect(hwnd, &rect);
		pos = this->getPosition();
		size = this->getSize();
	}

	bool isActive()
	{
		if (this->hwnd != 0)
			return true;
		else
			return false;
	}

	sf::Vector2i getPosition()
	{
		sf::Vector2i value;

		value.x = rect.left;
		value.y = rect.top;

		return value;
	}

	sf::Vector2u getSize()
	{
		sf::Vector2u value;

		value.x = rect.right - rect.left;
		value.y = rect.bottom - rect.top;

		return value;
	}
};

class pOverlay
{
private:
	sf::RenderWindow window;
	sf::Font		 font;
	GameInfo		 game_info;
	pMouse			 mouse;

public:
	pList			 list;
	pList			 list_settings;
	pNotificationCenter notification;

	void create(LPCSTR Name)
	{
		game_info = GameInfo(Name); // Getting game Info
		font.loadFromFile("Settings/font.ttf");

		window.create(sf::VideoMode(game_info.getSize().x , game_info.getSize().y), "pOverlay", sf::Style::None); // creating a window in the game's size
		window.setFramerateLimit(60);
		this->setTransparent(window.getSystemHandle()); // making the window transparent & not clickable

		notification.create(&window);

		mouse.create(&window);
		mouse.toggle();

		list.create(&window);
		list.setPosition(window.getSize().x / 2, window.getSize().y / 4);
		list.toggle();

		list_settings.create(&window);
		list_settings.setPosition(list.getPosition().x + list_settings.getSize().x + 5, list.getPosition().y);
		list_settings.toggle();
	}

	void toggle()
	{
		list.toggle();
		list_settings.toggle();
		mouse.toggle();

		if (list.isActive())
			sf::Mouse::setPosition(sf::Vector2i(list.getPosition().x + window.getPosition().x, list.getPosition().y + window.getPosition().y));
	}

	void loop()
	{
		while (window.isOpen() && game_info.isActive())
		{
			this->fixPosition();

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
			mouse.loop();
			notification.loop();

			window.clear(sf::Color::Color(0, 0, 0, 0));

			list.draw();
			list_settings.draw();
			mouse.draw();
			notification.draw();

			window.display();
		}
	}

private:
	void setTransparent(HWND handle)
	{
		MARGINS margins;
		margins.cxLeftWidth = -1;
		LONG cur_style = GetWindowLong(handle, GWL_EXSTYLE);

		DwmExtendFrameIntoClientArea(handle, &margins);
		SetWindowPos(handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowLong(handle, GWL_EXSTYLE, cur_style | WS_EX_TRANSPARENT | WS_EX_LAYERED);
	}

	void fixPosition()
	{
		game_info.update();
		sf::Vector2i gamePos = game_info.getPosition();
		sf::Vector2i windowPos = window.getPosition();

		if (gamePos.x != windowPos.x + 1 || gamePos.y != windowPos.y - 1)
		{
			window.setPosition(sf::Vector2i(gamePos.x - 1, gamePos.y + 1));
		}
	}
};