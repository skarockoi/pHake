#ifndef _PNOTIFICATIONCENTER_HPP_
#define _PNOTIFICATIONCENTER_HPP_

#include <SFML/Graphics.hpp>
#include <vector>

class pNotification // Everything needed for a notification
{
public:
	sf::Text		   text{};
	sf::RectangleShape back{};
	bool finished = 0;
	bool started = 0;
	bool ready = 0;
};

class pNotificationCenter
{
public:
	pNotificationCenter () : window_(0), font_(), position_({0,0}), notifications_() {}
	void Create(sf::RenderWindow* const& window);
	void Draw();
	void Loop();

public:
	void Add(const std::string& name);

private:
	bool IsEverythingFinished();
	uint32_t DecideSleep();

private:
	sf::RenderWindow* window_;
	sf::Font		  font_;
	sf::Vector2i	  position_;
	std::vector<pNotification> notifications_;
};
#endif