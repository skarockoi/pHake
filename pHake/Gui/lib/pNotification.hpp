#ifndef _PNOTIFICATION_HPP_
#define _PNOTIFICATION_HPP_

#include <SFML/Graphics.hpp>
#include <thread>
#include <vector>

class pNotification
{
private:
	struct Bone
	{
		sf::Text text;
		sf::RectangleShape back;
		bool finished;
		bool started;
		bool ready;
	};

	sf::RenderWindow* Window;
	sf::Font		  Font;
	sf::Vector2i	  Pos;
	std::vector<Bone> notifications;
public:
	void create(sf::RenderWindow* const& window);
	void add(std::string name);
	void draw();
	void loop();

private:
	void startNotification(int index);
	bool finishedShowing();
	uint32_t sleepTime();

};
#endif

