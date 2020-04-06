#include "pButton.hpp"

void pButton::create(sf::RenderWindow* const& window)
{
	if (Window == 0)
	{
		Window = window;
		Font.loadFromFile("Settings/font.ttf");

		this->buttonBack.setSize(sf::Vector2f(80, 28));
		this->buttonBack.setPosition(0, 0);
		this->buttonBack.setFillColor(sf::Color::Color(0, 0, 0, 150));
		this->buttonBack.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
		this->buttonBack.setOutlineThickness(1);

		this->buttonName.setFont(Font);
		this->buttonName.setCharacterSize(16);
		this->buttonName.setFillColor(sf::Color::Color(0, 0, 0, 255));
		this->buttonName.setPosition(0, 0);

		this->setActive(true);
	}
}

void pButton::loop()
{
	if (this->active && !this->isExecuting)
	{
		sf::Vector2i mouse = sf::Mouse::getPosition(*Window);
		if (!this->isExecuting)
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
		Window->draw(buttonBack);
		Window->draw(buttonName);
	}
}

void pButton::connect(void(&functionP)())
{
	this->function = &functionP;
}

void pButton::setTimeout(int sleep)
{
	this->sleepTime = sleep;
}

sf::Vector2f pButton::getSize()
{
	return buttonBack.getSize();
}

void pButton::setActive(bool act)
{
	this->active = act;
}

void pButton::setHighlight(bool value)
{
	if (value)
		buttonBack.setOutlineColor(sf::Color::Color(255, 255, 255, 255));
	else
		buttonBack.setOutlineColor(sf::Color::Color(0, 0, 0, 0));
}

void pButton::updateLength()
{
	if (this->resize)
	{
		sf::Vector2f rSize;
		rSize.x = ((float)std::string(buttonName.getString()).length() * 10) - (((std::string)buttonName.getString()).length() * 2);
		rSize.y = buttonBack.getSize().y;
		buttonBack.setSize(rSize);
	}
}

bool pButton::isOnBox()
{
	sf::Vector2i mouse = sf::Mouse::getPosition(*Window);
	if (mouse.x >= buttonBack.getPosition().x &&
		mouse.x <= buttonBack.getPosition().x + buttonBack.getSize().x &&
		mouse.y >= buttonBack.getPosition().y &&
		mouse.y <= buttonBack.getPosition().y + buttonBack.getSize().y)
		return true;
	else
		return false;
}

void pButton::execFunction()
{
	this->isExecuting = true;
	((void(*)(void))function)();
	std::this_thread::sleep_for(std::chrono::milliseconds(150));
	this->isExecuting = false;
}

void pButton::setPosition(int x, int y)
{
	buttonBack.setPosition(x, y + 1);
	buttonName.setPosition(x, y + (buttonBack.getSize().y / 4) - 5);
}

void pButton::setText(const std::string& text)
{
	buttonName.setString(" " + text);
	updateLength();
}

void pButton::setFixedSize(int x, int y)
{
	if (!resize)
		resize = false;

	buttonBack.setSize(sf::Vector2f(x, y));
}

void pButton::setFont(sf::Font& font)
{
	buttonName.setFont(font);
}

bool pButton::isActive()
{
	return this->active;
}
