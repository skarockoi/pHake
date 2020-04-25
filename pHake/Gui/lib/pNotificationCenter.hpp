#ifndef _PNOTIFICATIONCENTER_HPP_
#define _PNOTIFICATIONCENTER_HPP_

#include <SFML/Graphics.hpp>
#include <thread>
#include <vector>

class pNotificationCenter
{
private:
	struct Bone // Everything needed for a notification
	{
		sf::Text		   text;
		sf::RectangleShape back;
		bool finished;
		bool started;
		bool ready;
	};

	sf::RenderWindow* window;
	sf::Font		  Font;
	sf::Vector2i	  pos;
	std::vector<Bone> notifications;

public:
	void create(sf::RenderWindow* const& window);
	void draw();
	void loop();

public:
	void add(const std::string& name);

private:
	void startNotification(int index);
	bool isListFinished();
	uint32_t sleepTime();
};
#endif

