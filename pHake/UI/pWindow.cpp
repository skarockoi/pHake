#include "pWindow.hpp"
#include "pFont.hpp"

void pWindow::Create()
{
	list = pList();
	mouse_ = pMouse();

	font_.loadFromMemory(&Pixellari, Pixellari.size());

	window_.create(sf::VideoMode(208, 148), "pWindow");
	window_.setFramerateLimit(60);

	list.Create(&window_);
	list.position(sf::Vector2f(0.f, 0.f));
	list.Toggle();
}

void pWindow::Loop()
{
	while (window_.isOpen())
	{
		FixSize();
		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_.close();

			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window_.setView(sf::View(visibleArea));
			}
		}

		list.Loop();

		window_.clear(sf::Color::Color(255, 255, 255, 255));

		list.Draw();
		window_.display();
	}
}

void pWindow::Close()
{
	window_.close();
}

void pWindow::FixSize()
{
	sf::Vector2f size_list = list.size();

	sf::Vector2u new_size;
	new_size.x = size_list.x;
	window_.setSize(new_size);
}