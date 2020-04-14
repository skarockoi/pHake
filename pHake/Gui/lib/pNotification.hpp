#ifndef _PNOTIFICATION_HPP_
#define _PNOTIFICATION_HPP_

#include <SFML/Graphics.hpp>
#include <thread>
#include <vector>

class pNotification
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

