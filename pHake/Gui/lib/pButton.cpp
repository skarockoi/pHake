#include "pButton.hpp"

void pButton::create(sf::RenderWindow* const& Window)
{
	window = Window;
	font.loadFromFile("Settings/font.ttf");

	this->button_back.setSize(sf::Vector2f(80, 28));
	this->button_back.setPosition(0, 0);
	this->button_back.setFillColor(sf::Color::Color(0, 0, 0, 150));
	this->button_back.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
	this->button_back.setOutlineThickness(1);

	this->button_text.setFont(font);
	this->button_text.setCharacterSize(16);
	this->button_text.setFillColor(sf::Color::Color(0, 0, 0, 255));
	this->button_text.setPosition(0, 0);

	this->setActive(true);
}

void pButton::loop()
{
	if (this->active && !this->busy)
	{
		sf::Vector2i mouse = sf::Mouse::getPosition(*window);
		if (!this->busy)
		{
			if (this->isOnBox())
			{
				this->setHighlight(true);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					if (function != NULL)
					{
						std::thread(&pButton::execFunction, this).detach(); // Launches a new thread so the whole Gui wont freeze, tried using std::async but it doesnt work with sleep
					}
				}
			}
			else
			{
				this->setHighlight(false);
			}
		}

	}
}

void pButton::draw()
{
	if (this->isActive())
	{
		window->draw(button_back);
		window->draw(button_text);
	}
}

void pButton::connect(void(&functionP)())
{
	this->function = &functionP;
}

void pButton::setTimeout(int sleep)
{
	this->sleep_time = sleep;
}

sf::Vector2f pButton::getSize()
{
	return button_back.getSize();
}

void pButton::setActive(bool act)
{
	this->active = act;
}

void pButton::setHighlight(bool value)
{
	if (value)
		button_back.setOutlineColor(sf::Color::Color(255, 255, 255, 255));
	else
		button_back.setOutlineColor(sf::Color::Color(0, 0, 0, 0));
}

void pButton::updateLength()
{
	if (this->resize)
	{
		sf::Vector2f rSize;
		rSize.x = ((float)std::string(button_text.getString()).length() * 10) - (((std::string)button_text.getString()).length() * 2);
		rSize.y = button_back.getSize().y;
		button_back.setSize(rSize);
	}
}

bool pButton::isOnBox()
{
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	if (mouse.x > button_back.getPosition().x &&
		mouse.x < button_back.getPosition().x + button_back.getSize().x &&
		mouse.y > button_back.getPosition().y &&
		mouse.y < button_back.getPosition().y + button_back.getSize().y)
		return true;
	else
		return false;
}

void pButton::execFunction()
{
	this->busy = true;
	((void(*)(void))function)();
	std::this_thread::sleep_for(std::chrono::milliseconds(150));
	this->busy = false;
}

void pButton::setPosition(int x, int y)
{
	button_back.setPosition(x, y + 1);
	button_text.setPosition(x, y + (button_back.getSize().y / 4) - 5);
}

void pButton::setText(const std::string& text)
{
	button_text.setString(" " + text);
	updateLength();
}

void pButton::setFixedSize(int x, int y)
{
	if (!resize)
		resize = false;

	button_back.setSize(sf::Vector2f(x, y));
}

void pButton::setFont(sf::Font& font)
{
	button_text.setFont(font);
}

bool pButton::isActive()
{
	return this->active;
}
