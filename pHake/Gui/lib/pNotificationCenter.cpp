#include "pNotificationCenter.hpp"

void pNotificationCenter::create(sf::RenderWindow* const& Window)
{
	pos.x = 15;
	pos.y = 20;

	window = Window;
	Font.loadFromFile("Settings/font.ttf");
}

void pNotificationCenter::add(const std::string& name)
{
	Bone tempBone;
	tempBone.finished = false;
	tempBone.started = false;
	tempBone.ready = true;

	tempBone.back.setSize(sf::Vector2f(210, 20));
	tempBone.back.setPosition(pos.x + 10, pos.y + (notifications.size() * 25));
	tempBone.back.setFillColor(sf::Color::Color(0, 0, 0, 150));
	tempBone.back.setOutlineColor(sf::Color::Color(0, 0, 0, 150));
	tempBone.back.setOutlineThickness(1);

	tempBone.text.setFont(Font);
	tempBone.text.setCharacterSize(16);
	tempBone.text.setFillColor(sf::Color::Color(255, 255, 255, 255));
	tempBone.text.setPosition(tempBone.back.getPosition().x, tempBone.back.getPosition().y);
	tempBone.text.setString(" " + name);

	notifications.push_back(tempBone);
}

void pNotificationCenter::draw()
{
	for (int i = 0; i < notifications.size(); i++)
	{
		if (notifications[i].started && !notifications[i].finished)
		{
			window->draw(notifications[i].back);
			window->draw(notifications[i].text);
		}
	}
}

void pNotificationCenter::loop()
{
	for (int i = 0; i < notifications.size(); i++)
	{
		if (notifications[i].ready && !notifications[i].started)
		{
			std::thread execThread = std::thread(&pNotificationCenter::startNotification, this, i); // Launches a new thread so the whole Gui wont freeze, tried using std::async but it doesnt work with sleep
			execThread.detach();
		}
	}

	if (notifications.size() > 32 || this->isListFinished())
	{
		notifications.clear();
	}
}

void pNotificationCenter::startNotification(int index)
{
	notifications[index].ready = false;
	notifications[index].started = true;

	for (int b = 125; b > 0; b--) // fade effect magic
	{
		notifications[index].back.setFillColor(sf::Color(0, 0, 0, b));
		notifications[index].back.setOutlineColor(sf::Color(0, 0, 0, b));
		notifications[index].text.setFillColor(sf::Color(255, 255, 255, b * 2));

		std::this_thread::sleep_for(std::chrono::milliseconds(this->sleepTime()));
	}

	notifications[index].finished = true;
}

bool pNotificationCenter::isListFinished()
{
	uint8_t count = 0;

	for (int i = 0; i < notifications.size(); i++)
	{
		if (notifications[i].finished && notifications.size() > 1)
			count++;
	}

	if (count == notifications.size())
		return true;
	else
		return false;
}

uint32_t pNotificationCenter::sleepTime()
{
	if (notifications.size() < 7)
		return 10;
	else if (notifications.size() >= 7)
		return 5;
}
