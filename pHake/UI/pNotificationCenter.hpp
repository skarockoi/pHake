#ifndef _PNOTIFICATIONCENTER_HPP_
#define _PNOTIFICATIONCENTER_HPP_

#include <SFML/Graphics.hpp>
#include <vector>

class pNotificationCenter
{
private:
	struct Notification // Everything needed for a notification
	{
		sf::Text		   text;
		sf::RectangleShape back;
		bool finished;
		bool started;
		bool ready;
	};

	sf::RenderWindow* window_;
	sf::Font		  font_;
	sf::Vector2i	  position_;
	std::vector<Notification> notifications_;

public:
	void Create(sf::RenderWindow* const& window);
	void Draw();
	void Loop();

public:
	void Add(const std::string& name);

private:
	bool IsEverythingFinished();
	uint32_t DecideSleep();
};
#endif