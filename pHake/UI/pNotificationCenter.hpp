#ifndef _PNOTIFICATIONCENTER_HPP_
#define _PNOTIFICATIONCENTER_HPP_

#include <SFML/Graphics.hpp>
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
	sf::Font		  font;
	sf::Vector2i	  pos;
	std::vector<Bone> notifications;

public:
	void Create(sf::RenderWindow* const& window);
	void Draw();
	void Loop();

public:
	void Add(const std::string& name);

private:
	bool IsListFinished();
	uint32_t DecideSleep();
};
#endif

