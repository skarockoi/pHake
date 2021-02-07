#include "pWindow.hpp"

void pWindow::Create()
{
	this->list = std::make_unique<pList>();
	this->mouse_ = std::make_unique<pMouse>();

	font_.loadFromFile("Settings/font.ttf");

	window_.create(sf::VideoMode(208, 148), "pWindow");
	window_.setFramerateLimit(60);

	list->Create(&window_);
	list->position(0, 0);
	list->Toggle();
}

void pWindow::Loop()
{
	while (window_.isOpen())
	{
		this->FixSize();
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

		list->Loop();

		window_.clear(sf::Color::Color(255, 255, 255, 255));

		list->Draw();
		window_.display();
	}
}

void pWindow::FixSize()
{
	sf::Vector2f size_list = list->size();

	sf::Vector2u new_size;
	new_size.x = size_list.x;
	window_.setSize(new_size);
}