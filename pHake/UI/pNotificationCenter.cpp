#include "pNotificationCenter.hpp"
#include "pFont.hpp"

#include <thread>

#define TEXT_SIZE 16
#define TEXT_COLOR sf::Color::Color(255, 255, 255, 255)

#define BACK_HEIGHT 20
#define BACK_COLOR sf::Color::Color(0, 0, 0, 150)
#define BACK_COLOR_OUTLINE sf::Color::Color(0, 0, 0, 255)

#define DISTANCE_FROM_EDGE 20
#define DISTANCE_BETWEEN_NOTIFICATIONS 25


void pNotificationCenter::Create(sf::RenderWindow* const& Window)
{
	position_.x = DISTANCE_FROM_EDGE;
	position_.y = DISTANCE_FROM_EDGE;

	window_ = Window;
	font_.loadFromMemory(&Pixellari, Pixellari.size());
}

void pNotificationCenter::Add(const std::string& name)
{
	pNotification tmp;
	tmp.finished = false;
	tmp.started = false;
	tmp.ready = true;

	tmp.text.setFont(font_);
	tmp.text.setCharacterSize(TEXT_SIZE);
	tmp.text.setFillColor(TEXT_COLOR);
	tmp.text.setPosition(position_.x, position_.y + (notifications_.size() * DISTANCE_BETWEEN_NOTIFICATIONS));
	tmp.text.setString(" " + name + " ");

	tmp.back.setSize(sf::Vector2f(tmp.text.getGlobalBounds().width, BACK_HEIGHT));
	tmp.back.setPosition(tmp.text.getPosition());
	tmp.back.setFillColor(BACK_COLOR);
	tmp.back.setOutlineColor(BACK_COLOR_OUTLINE);
	tmp.back.setOutlineThickness(1);

	notifications_.push_back(tmp);
}

void pNotificationCenter::Draw()
{
	for (size_t i = 0; i < notifications_.size(); i++)
	{
		if (notifications_[i].started && !notifications_[i].finished)
		{
			window_->draw(notifications_[i].back);
			window_->draw(notifications_[i].text);
		}
	}
}

void pNotificationCenter::Loop()
{
	for (size_t i = 0; i < notifications_.size(); i++)
	{
		if (notifications_[i].ready && !notifications_[i].started)
		{
			std::thread execThread = std::thread([i, this]()
				{
					notifications_[i].ready = false;
					notifications_[i].started = true;

					for (int b = 127, c = 255; b > 0; b--, c -= 2) // Fade effect magic
					{
						notifications_[i].back.setFillColor(sf::Color(0, 0, 0, b));
						notifications_[i].back.setOutlineColor(sf::Color(0, 0, 0, c));
						notifications_[i].text.setFillColor(sf::Color(255, 255, 255, b * 2));

						std::this_thread::sleep_for(std::chrono::milliseconds(DecideSleep()));
					}
					notifications_[i].finished = true;
				});
			execThread.detach();
		}
	}

	if (notifications_.size() > 32 || IsEverythingFinished())
		notifications_.clear();
	
}

bool pNotificationCenter::IsEverythingFinished()
{
	for (int i = 0; i < notifications_.size(); i++)
	{
		if (!notifications_[i].finished)
			return false;
	}

	return true;
}

uint32_t pNotificationCenter::DecideSleep()
{
	if (notifications_.size() < 7) // check if there are more than 7 notifications
		return 15; // if no, then sleep sleep for 10 seconds
	else
		return 5; // if yes, then sleep sleep for 5 seconds
}